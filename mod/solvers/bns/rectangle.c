/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:03:22 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/27 19:03:25 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Check if a given point is inside a rectangle.
 *
 * Determines whether the specified point lies inside the bounds of the given
 * rectangle object.
 *
 * @param point 3D point to be checked.
 * @param obj Pointer to the object structure, which contains details about
 * the rectangle.
 *
 * @return TRUE if the point is inside the rectangle, FALSE otherwise.
 */
t_bool	is_point_inside_rect(t_v3d point, t_obj *obj)
{
	t_v3d	oc;
	t_v3d	disc;
	t_v3d	uv[2];
	double	proy[2];

	oc = ft_minus_v3d(point, obj->elm.rc.centre);
	disc = ft_perp_v3d(obj->elm.rc.orient);
	uv[E_U] = ft_cross_v3d(obj->elm.rc.orient, disc);
	uv[E_V] = ft_cross_v3d(obj->elm.rc.orient, uv[E_U]);
	proy[E_U] = ft_dot_v3d(oc, uv[E_U]);
	proy[E_V] = ft_dot_v3d(oc, uv[E_V]);
	if (fabs(proy[E_U]) <= obj->elm.rc.width * 0.5
		&& fabs(proy[E_V]) <= obj->elm.rc.height * 0.5)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Calculate the hit distance for a ray with a rectangle.
 *
 * Computes the intersection distance of a ray with a given rectangle. If the ray
 * doesn't hit the rectangle, INFINITY is returned.
 *
 * @param origin The starting point of the ray.
 * @param dir The direction of the ray.
 * @param obj Pointer to the object structure, which contains details about the
 * rectangle.
 *
 * @return The intersection distance if the ray hits the rectangle,
 * INFINITY otherwise.
 */
double	rectangle_solver(t_v3d origin, t_v3d dir, t_obj *obj)
{
	double	dist;
	t_v3d	hit;

	dist = plane_hit(origin, dir,
			obj->elm.rc.centre, obj->elm.rc.orient);
	hit = ft_plus_v3d(origin, ft_scalar_v3d(dist, dir));
	if (!is_point_inside_rect(hit, obj))
		return (INFINITY);
	return (dist);
}
