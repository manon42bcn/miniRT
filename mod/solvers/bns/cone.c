/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:24:39 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/21 19:24:56 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Computes the normal vector at a given intersection point on the cone.
 *
 * This function determines the normal vector of a cone at a given point of
 * intersection. The normal is calculated based on the cone's center (apex),
 * orientation, and the tangent of its angle (alpha). The resulting normal
 * is essential for shading and reflection calculations in a ray tracing
 * context.
 *
 * @param dir Unused. To make normal functions standard
 * @param hit Point on the cone where the normal vector is to be
 * calculated.
 * @param obj Pointer to the cone object containing its geometric and
 * material properties.
 * @return t_v3d The computed normal vector at the intersection point.
 */
t_v3d	cone_normal(t_v3d dir, t_v3d hit, t_obj *obj)
{
	t_v3d	v_apex;
	t_v3d	parallel;
	t_v3d	normal;

	(void)dir;
	v_apex = ft_minus_v3d(hit, obj->elm.con.centre);
	parallel = ft_scalar_v3d(ft_dot_v3d(v_apex, obj->elm.con.dir),
			obj->elm.con.dir);
	normal = ft_minus_v3d(v_apex, ft_scalar_v3d(1 + obj->elm.con.alpha
				* obj->elm.con.alpha, parallel));
	normal = ft_normal_v3d(normal);
	return (normal);
}

/**
 * @brief Checks if the intersection point of a ray with a cone lies within
 * the bounds of the cone.
 *
 * This function checks whether the intersection point of a ray with a cone
 * is located between the base and the tip of the cone. If the intersection
 * is out of these bounds, it returns INFINITY. Otherwise, it returns the
 * distance `t` from the ray's origin to the intersection point.
 *
 * @param origin The origin of the ray.
 * @param dir The direction of the ray.
 * @param t The distance from the ray's origin to a potential intersection
 * point.
 * @param cone Pointer to the cone object.
 * @return double The distance `t` if the intersection is within the
 * cone's bounds, otherwise INFINITY.
 */
static inline double	bounds(t_v3d origin, t_v3d dir,
		double t, t_obj *cone)
{
	t_v3d	pnt;
	t_v3d	vec_vertex;
	double	d_p;
	double	height_axs;

	pnt = ft_plus_v3d(origin, ft_scalar_v3d(t, dir));
	vec_vertex = ft_minus_v3d(pnt, cone->elm.con.centre);
	d_p = ft_dot_v3d(vec_vertex, cone->elm.con.dir);
	if (d_p < 0)
		return (INFINITY);
	height_axs = ft_dot_v3d(vec_vertex, cone->elm.con.dir);
	if (height_axs < 0 || height_axs > cone->elm.con.height)
		return (INFINITY);
	return (t);
}

/**
 * @brief Computes the quadratic coefficients for ray-cone intersection.
 *
 * This function calculates the coefficients A, B, and C for the quadratic
 * equation that determines the intersections between a ray and a cone.
 * These coefficients are essential for solving the quadratic equation
 * and determining if and where the ray intersects the cone.
 *
 * @param coef Pointer to an array to store the computed coefficients
 * A, B, and C.
 * @param obj Pointer to the cone object.
 * @param origin The origin of the ray.
 * @param dir The direction of the ray.
 */
static inline void	cone_quad(double *coef, t_obj *obj, t_v3d origin, t_v3d dir)
{
	t_v3d	oc;
	double	dot_d;
	double	dot_oc;

	oc = ft_minus_v3d(origin, obj->elm.con.centre);
	dot_d = ft_dot_v3d(dir, obj->elm.con.dir);
	dot_oc = ft_dot_v3d(oc, obj->elm.con.dir);
	coef[E_A] = ft_dot_v3d(dir, dir)
		- (1 + (obj->elm.con.alpha * obj->elm.con.alpha))
		* (dot_d * dot_d);
	coef[E_B] = 2 * (ft_dot_v3d(dir, oc)
			- (1 + (obj->elm.con.alpha * obj->elm.con.alpha))
			* (dot_d * dot_oc));
	coef[E_C] = ft_dot_v3d(oc, oc)
		- (1 + (obj->elm.con.alpha * obj->elm.con.alpha))
		* (dot_oc * dot_oc);
}

/**
 * @brief Computes the intersection of a ray with a cone.
 *
 * @param origin Origin of the ray.
 * @param dir Direction of the ray.
 * @param obj Cone object.
 * @return double Distance from the ray origin to the closest intersection
 * point or INFINITY.
 */
double	cone_solver(t_v3d origin, t_v3d dir, t_obj *obj)
{
	double	coef[3];
	double	t[2];
	double	t_c[2];

	cone_quad(&coef[0], obj, origin, dir);
	if (!quadratic(&coef[0], &t[0]))
		return (INFINITY);
	t_c[0] = bounds(origin, dir, t[0], obj);
	t_c[1] = bounds(origin, dir, t[1], obj);
	if (t_c[0] == INFINITY && t_c[1] == INFINITY)
		return (INFINITY);
	if (t_c[0] < t[1])
		return (t_c[0]);
	return (t[1]);
}
