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
 * @brief Calculate the normal vector for a hit point on a cone surface.
 *
 * This function computes the normal vector for a point of intersection on a cone
 * surface based on the incoming ray direction and the cone's properties.
 *
 * @param dir The direction vector of the incoming ray (unused in this version).
 * @param hit The point of intersection on the cone surface.
 * @param inter Pointer to the intersection data structure.
 *
 * @return The normal vector at the point of intersection.
 */
t_v3d	cone_normal(t_v3d dir, t_v3d hit, t_inter *inter)
{
	t_v3d	v_apex;
	t_v3d	parallel;
	t_v3d	normal;

	(void)dir;
	v_apex = ft_minus_v3d(hit, inter->obj->elm.con.centre);
	parallel = ft_scalar_v3d(ft_dot_v3d(v_apex, inter->obj->elm.con.dir),
			inter->obj->elm.con.dir);
	normal = ft_minus_v3d(v_apex, ft_scalar_v3d(1 + inter->obj->elm.con.alpha
				* inter->obj->elm.con.alpha, parallel));
	normal = ft_normal_v3d(normal);
	return (normal);
}

/**
 * @brief Calculate the bounds of intersection with a cone.
 *
 * This function calculates the bounds of intersection of a ray with a cone
 * based on the ray's origin, direction, and the cone's properties.
 *
 * @param origin The origin point of the ray.
 * @param dir The direction vector of the ray.
 * @param t The calculated intersection distance with the cone.
 * @param con The cone structure representing the cone.
 *
 * @return The intersection distance or INFINITY if there is no intersection.
 */
static inline double	bounds(t_v3d origin, t_v3d dir,
		double t, t_cone con)
{
	t_v3d	pnt;
	t_v3d	vec_vertex;
	double	d_p;
	double	height_axs;

	pnt = ft_plus_v3d(origin, ft_scalar_v3d(t, dir));
	vec_vertex = ft_minus_v3d(pnt, con.centre);
	d_p = ft_dot_v3d(vec_vertex, con.dir);
	if (d_p < 0)
		return (INFINITY);
	height_axs = ft_dot_v3d(vec_vertex, con.dir);
	if (height_axs < 0 || height_axs > con.height)
		return (INFINITY);
	return (t);
}

/**
 * @brief Calculate the intersection point of a ray with a cone.
 *
 * This function finds the intersection point of a ray with a cone and returns
 * the distance from the ray origin to the intersection point. It utilizes
 * quadratic equations to solve for the intersection.
 *
 * @param origin The origin point of the ray.
 * @param dir The direction vector of the ray.
 * @param con The cone structure representing the cone.
 *
 * @return The distance from the ray origin to the intersection point or INFINITY
 * if there is no intersection with the cone.
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
