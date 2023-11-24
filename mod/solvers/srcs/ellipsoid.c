/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:30:53 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/24 23:44:06 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Calculate the normal vector for a hit point on an ellipsoid surface.
 *
 * This function computes the normal vector for a point of intersection on an
 * ellipsoid surface based on the incoming ray direction and the ellipsoid's
 * properties.
 *
 * @param dir The direction vector of the incoming ray (unused in this version).
 * @param hit The point of intersection on the ellipsoid surface.
 * @param inter Pointer to the intersection data structure.
 *
 * @return The normal vector at the point of intersection.
 */

t_v3d	ft_div_v3d_by_vec(t_v3d vec, t_v3d vec2)
{
	return ((t_v3d){vec.x / (vec2.x * vec2.x), vec.y / (vec2.y * vec2.y), vec.z / (vec2.z * vec2.z)});
}

t_v3d	ellipsoid_normal(t_v3d dir, t_v3d hit, t_inter *inter)
{
	t_v3d hit_to_centre;
	t_v3d	normal;
	t_v3d	rad;

	(void)dir;
	rad = (t_v3d){inter->obj->elm.elp.rx, inter->obj->elm.elp.ry, inter->obj->elm.elp.rz};
	hit_to_centre = ft_minus_v3d(hit, inter->obj->elm.elp.centre);
	normal = ft_div_v3d_by_vec(hit_to_centre, rad);
	return (ft_normal_v3d(normal));
}

static void	ellipsoid_quad(double *coef, t_ellip elp, t_v3d origin, t_v3d dir)
{
	t_v3d	oc;
	t_v3d	loc_dir;
	t_v3d	loc_oc;

	oc = ft_minus_v3d(origin, elp.centre);
	loc_dir = (t_v3d){ft_dot_v3d(dir, elp.dir) / elp.rx,
		ft_dot_v3d(dir, elp.dirx) / elp.ry,
		ft_dot_v3d(dir, elp.diry) / elp.rz};
	coef[E_A] = (loc_dir.x * loc_dir.x) + (loc_dir.y * loc_dir.y)
		+ (loc_dir.z * loc_dir.z);
	loc_oc = (t_v3d){ft_dot_v3d(oc, elp.dir) / elp.rx,
		ft_dot_v3d(oc, elp.dirx) / elp.ry,
		ft_dot_v3d(oc, elp.diry) / elp.rz};
	coef[E_B] = 2 * ((loc_oc.x * loc_dir.x) + (loc_oc.y * loc_dir.y)
			+ (loc_oc.z * loc_dir.z));
	coef[E_C] = (loc_oc.x * loc_oc.x) + (loc_oc.y * loc_oc.y)
		+ (loc_oc.z * loc_oc.z) - 1;
}

/**
 * @brief Calculate the intersection point of a ray with an ellipsoid.
 *
 * This function finds the intersection point of a ray with an ellipsoid and
 * returns the distance from the ray origin to the intersection point. It uses
 * quadratic equations to solve for the intersection.
 *
 * @param origin The origin point of the ray.
 * @param dir The direction vector of the ray.
 * @param elp The ellipsoid structure representing the ellipsoid.
 *
 * @return The distance from the ray origin to the intersection point or INFINITY
 * if there is no intersection with the ellipsoid.
 */
double	ellipsoid_solver(t_v3d origin, t_v3d dir, t_ellip elp)
{
	double	coef[3];
	double	t[2];

	ellipsoid_quad(&coef[0], elp, origin, dir);
	if (!quadratic(&coef[0], &t[0]))
		return (INFINITY);
	if (t[0] > 0)
		return (t[0]);
	if (t[1] > 0)
		return (t[1]);
	return (INFINITY);
}
