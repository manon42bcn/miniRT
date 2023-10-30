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
t_bool	is_point_inside_rect(t_v3d point, t_rectangle rc)
{
	t_v3d	oc;
	t_v3d	disc;
	t_v3d	uv[2];
	double	proy[2];

	oc = ft_minus_v3d(point, rc.centre);
	disc = ft_perp_v3d(rc.orient);
	uv[E_U] = ft_cross_v3d(rc.orient, disc);
	uv[E_V] = ft_cross_v3d(rc.orient, uv[E_U]);
	proy[E_U] = ft_dot_v3d(oc, uv[E_U]);
	proy[E_V] = ft_dot_v3d(oc, uv[E_V]);
	if (fabs(proy[E_U]) <= rc.width * 0.5
		&& fabs(proy[E_V]) <= rc.height * 0.5)
		return (TRUE);
	return (FALSE);
}

double	rectangle_solver(t_v3d origin, t_v3d dir, t_rectangle rc)
{
	double	dist;
	t_v3d	hit;

	dist = plane_hit(origin, dir, rc.centre, rc.orient);
	hit = ft_plus_v3d(origin, ft_scalar_v3d(dist, dir));
	if (!is_point_inside_rect(hit, rc))
		return (INFINITY);
	return (dist);
}
