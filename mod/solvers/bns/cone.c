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
 * @brief Computes the normal at the intersection point of a ray with a cone.
 *
 * @param inter_point Point of intersection on the cone.
 * @param cone Cone object.
 * @return t_v3d Normal vector at the intersection point.
 */
t_v3d	cone_normal(t_v3d inter_point, t_obj *obj)
{
	t_v3d	vec_from_apex;
	t_v3d	projected;
	t_v3d	normal;

	vec_from_apex = ft_minus_v3d(inter_point, obj->elm.con.centre);
	projected = ft_scalar_v3d(ft_dot_v3d(vec_from_apex, obj->normal),
			obj->normal);
	normal = ft_normal_v3d(ft_minus_v3d(vec_from_apex, projected));
	if (ft_dot_v3d(normal, obj->normal) < 0)
		normal = ft_scalar_v3d(-1, normal);
	return (normal);
}

/**
 * @brief Checks if a given intersection point t is within the bounds of
 * the cone.
 *
 * @param origin Origin of the ray.
 * @param dir Direction of the ray.
 * @param t Distance from the ray origin to the intersection point.
 * @param cone Cone object.
 * @return double Adjusted t value or INFINITY if out of bounds.
 */
static inline double	check_cone_bounds(t_v3d origin, t_v3d dir,
	double t, t_obj *cone)
{
	t_v3d	point;
	t_v3d	base_to_point;
	double	height_axs;

	point = ft_plus_v3d(origin, ft_scalar_v3d(t, dir));
	base_to_point = ft_minus_v3d(point, cone->elm.con.centre);
	height_axs = ft_dot_v3d(base_to_point, cone->normal);
	if (height_axs < 0 || height_axs > cone->elm.con.height)
		return (INFINITY);
	return (t);
}

/**
 * @brief Computes the quadratic coefficients for a ray-cone intersection.
 *
 * @param coef Array to store the computed coefficients A, B, and C.
 * @param obj Cone object.
 * @param origin Origin of the ray.
 * @param dir Direction of the ray.
 */
static inline void	cone_quad(double *coef, t_obj *obj, t_v3d origin, t_v3d dir)
{
	t_v3d	oc;

	oc = ft_minus_v3d(origin, obj->elm.con.centre);
	coef[E_A] = ft_dot_v3d(dir, dir)
		- (1 + obj->elm.con.alpha * obj->elm.con.alpha)
		* ft_dot_v3d(dir, obj->normal) * ft_dot_v3d(dir, obj->normal);
	coef[E_B] = 2 * (ft_dot_v3d(dir, oc)
			- (1 + obj->elm.con.alpha * obj->elm.con.alpha)
			* ft_dot_v3d(dir, obj->normal) * ft_dot_v3d(oc, obj->normal));
	coef[E_C] = ft_dot_v3d(oc, oc)
		- (1 + obj->elm.con.alpha * obj->elm.con.alpha)
		* ft_dot_v3d(oc, obj->normal) * ft_dot_v3d(oc, obj->normal);
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
	double	disc;

	cone_quad(coef, obj, origin, dir);
	disc = coef[E_B] * coef[E_B] - 4 * coef[E_A] * coef[E_C];
	if (disc < 0)
		return (INFINITY);
	t[0] = (-coef[E_B] - sqrt(disc)) / (2 * coef[E_A]);
	t[1] = (-coef[E_B] + sqrt(disc)) / (2 * coef[E_A]);
	t_c[0] = check_cone_bounds(origin, dir, t[0], obj);
	t_c[1] = check_cone_bounds(origin, dir, t[1], obj);
	if (t_c[0] == INFINITY && t[1] == INFINITY)
		return (INFINITY);
	if (t_c[0] < t[1])
		return (t_c[0]);
	return (t[1]);
}
