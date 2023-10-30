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
 * @brief Calculates the intersection between a ray and a plane.
 *
 * @param origin Origin of the ray.
 * @param dir Direction of the ray.
 * @param plane_centre A point on the plane.
 * @param plane_dir Normal vector of the plane.
 * @return The distance from the ray's origin to the intersection point,
 * or INFINITY if no intersection.
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
 * @brief Solver function for the intersection between a ray and a plane object.
 *
 * @param origin Origin of the ray.
 * @param dir Direction of the ray.
 * @param obj The plane object in the scene.
 * @return The distance from the ray's origin to the intersection point,
 * or INFINITY if no intersection.
 */
double	plane_solver(t_v3d origin, t_v3d dir, t_plane pl)
{
	return (plane_hit(origin, dir, pl.centre, pl.orient));
}
