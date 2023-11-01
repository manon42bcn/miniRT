/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 21:42:28 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/04 21:42:30 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Calculate the intersection point of a ray with a plane.
 *
 * This function computes the intersection point of a ray with a plane defined
 * by its center and normal direction. It returns the distance from the ray's
 * origin to the intersection point.
 *
 * @param origin The origin point of the ray.
 * @param dir The direction vector of the ray.
 * @param plane_centre The center point of the plane.
 * @param plane_dir The normal direction of the plane.
 *
 * @return The distance from the ray origin to the intersection point or
 * INFINITY if there is no intersection with the plane.
 */
double	plane_hit(t_v3d origin, t_v3d dir, t_v3d plane_centre, t_v3d plane_dir)
{
	double	point;
	double	base;

	base = ft_dot_v3d(plane_dir, dir);
	if (base == 0)
		return (INFINITY);
	point = (ft_dot_v3d(plane_dir, ft_minus_v3d(plane_centre, origin))) / base;
	if (point > EPSILON)
		return (point);
	return (INFINITY);
}

/**
 * @brief Find the intersection point of a ray with a plane.
 *
 * This function calculates the intersection point of a ray with a plane and
 * returns the distance from the ray's origin to the intersection point.
 *
 * @param origin The origin point of the ray.
 * @param dir The direction vector of the ray.
 * @param pl The plane structure representing the plane.
 *
 * @return The distance from the ray origin to the intersection point or
 * INFINITY if there is no intersection with the plane.
 */
double	plane_solver(t_v3d origin, t_v3d dir, t_plane pl)
{
	return (plane_hit(origin, dir, pl.centre, pl.orient));
}
