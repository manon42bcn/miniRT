/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 19:24:39 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/25 22:59:41 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Calculate the normal vector on the surface of a cone.
 *
 * This function calculates the normal vector at a given point on the surface
 * of a cone. It checks if the intersection point is inside or outside the
 * cone and computes the normal accordingly.
 *
 * @param dir The direction of the ray.
 * @param hit The intersection point.
 * @param inter The intersection information.
 * @return The normal vector at the intersection point.
 */
t_v3d	cone_normal(t_v3d dir, t_v3d hit, t_inter *inter)
{
	t_v3d	v_apex;
	t_v3d	parallel;
	t_v3d	normal;
	double	height_axs;

	v_apex = ft_minus_v3d(hit, inter->obj->elm.con.centre);
	height_axs = ft_dot_v3d(v_apex, inter->obj->elm.con.dir);
	if (height_axs < 0 || height_axs > inter->obj->elm.con.height)
		return (common_normal(dir, hit, inter));
	parallel = ft_scalar_v3d(
			ft_dot_v3d(v_apex, inter->obj->elm.con.dir),
			inter->obj->elm.con.dir);
	normal = ft_minus_v3d(v_apex,
			ft_scalar_v3d(1 + inter->obj->elm.con.alpha
				* inter->obj->elm.con.alpha, parallel));
	normal = ft_normal_v3d(normal);
	return (normal);
}

/**
 * @brief Check if a point is within the bounds of a cone.
 *
 * This function checks if a point is within the bounds of a cone defined by its
 * apex, direction, height, and alpha angle.
 *
 * @param origin The origin of the ray.
 * @param dir The direction of the ray.
 * @param t The distance to the intersection point.
 * @param con The cone parameters (apex, direction, height, and alpha).
 * @return The corrected distance to the intersection point or `INFINITY`
 * if outside the bounds.
 */
static inline double	bounds(t_v3d origin, t_v3d dir,
		double t, t_cone con)
{
	t_v3d	pnt;
	t_v3d	vec_vertex;
	double	evl;
	double	height_axs;

	pnt = ft_plus_v3d(origin, ft_scalar_v3d(t, dir));
	vec_vertex = ft_minus_v3d(pnt, con.centre);
	evl = ft_dot_v3d(vec_vertex, con.dir);
	if (evl < 0)
		return (INFINITY);
	height_axs = ft_dot_v3d(vec_vertex, con.dir);
	if (height_axs < 0 || height_axs > con.height)
		return (INFINITY);
	evl = height_axs * tan(con.alpha);
	if (ft_dot_v3d(ft_minus_v3d(vec_vertex,
				ft_scalar_v3d(height_axs, con.dir)),
			ft_minus_v3d(vec_vertex, ft_scalar_v3d(height_axs, con.dir)))
		> (evl * evl))
		return (INFINITY);
	return (t);
}

/**
 * @brief Calculate the coefficients for the quadratic equation of a cone.
 *
 * This function calculates the coefficients (A, B, C) for the quadratic
 * equation of a cone, which is used to find the intersection points
 * of a ray with the cone.
 *
 * @param coef Array to store the coefficients (A, B, C).
 * @param con The cone parameters (apex, direction, height, and alpha).
 * @param origin The origin of the ray.
 * @param dir The direction of the ray.
 */
static inline void	cone_quad(double *coef, t_cone con, t_v3d origin, t_v3d dir)
{
	t_v3d	oc;
	double	dot_d;
	double	dot_oc;

	oc = ft_minus_v3d(origin, con.centre);
	dot_d = ft_dot_v3d(dir, con.dir);
	dot_oc = ft_dot_v3d(oc, con.dir);
	coef[E_A] = ft_dot_v3d(dir, dir)
		- (1 + (con.alpha * con.alpha))
		* (dot_d * dot_d);
	coef[E_B] = 2 * (ft_dot_v3d(dir, oc)
			- (1 + (con.alpha * con.alpha))
			* (dot_d * dot_oc));
	coef[E_C] = ft_dot_v3d(oc, oc)
		- (1 + (con.alpha * con.alpha))
		* (dot_oc * dot_oc);
}

/**
 * @brief Calculate the intersection of a ray with a cone.
 *
 * This function computes the intersection of a ray with a cone.
 * If there is no intersection, it returns `INFINITY`.
 *
 * @param origin The origin of the ray.
 * @param dir The direction of the ray.
 * @param con The cone parameters (apex, direction, height, and alpha).
 * @return The distance to the intersection point or `INFINITY`
 * if no intersection.
 */
double	cone_solver(t_v3d origin, t_v3d dir, t_cone con)
{
	double	coef[3];
	double	t[2];
	double	t_c[2];

	cone_quad(&coef[0], con, origin, dir);
	if (!quadratic(&coef[0], &t[0]))
		return (INFINITY);
	t_c[0] = bounds(origin, dir, t[0], con);
	t_c[1] = bounds(origin, dir, t[1], con);
	if (t_c[0] == INFINITY && t_c[1] == INFINITY)
		return (INFINITY);
	if (t_c[0] < t[1])
		return (t_c[0]);
	return (t[1]);
}
