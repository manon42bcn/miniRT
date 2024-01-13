/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:03:22 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/05 21:59:47 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Check if a point is inside a rectangle.
 *
 * This function checks if a given point is inside a rectangle defined by
 * its center, orientation, width, and height.
 *
 * @param point The point being tested for inclusion.
 * @param rc The rectangle structure representing the rectangle.
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

/**
 * @brief Find the intersection of a ray with a rectangle.
 *
 * This function calculates the intersection point of a ray with a rectangle
 * defined by its center, orientation, width, and height. It returns the distance
 * from the ray's origin to the intersection point or INFINITY if there is no
 * intersection.
 *
 * @param origin The origin point of the ray.
 * @param dir The direction vector of the ray.
 * @param rc The rectangle structure representing the rectangle.
 *
 * @return The distance from the ray origin to the intersection point or INFINITY
 * if there is no intersection with the rectangle.
 */
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
