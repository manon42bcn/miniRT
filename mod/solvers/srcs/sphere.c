/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:40:59 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/15 00:54:18 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Calculate the normal vector for a hit point on a sphere's surface.
 *
 * This function calculates the normal vector for a point of intersection on a
 * sphere's surface based on the incoming ray direction and the sphere's
 * properties. It also checks if the intersection is inside the sphere.
 *
 * @param dir The direction vector of the incoming ray.
 * @param hit The point of intersection on the sphere's surface.
 * @param inter Pointer to the intersection data structure.
 *
 * @return The normal vector at the point of intersection.
 */
t_v3d	sphere_normal(t_v3d dir, t_v3d hit, t_inter *inter)
{
	t_v3d		rst;

	rst = ft_normal_v3d(ft_minus_v3d(hit, inter->obj->elm.sph.centre));
	if (ft_cos_v3d(dir, rst) > 0)
	{
		rst = ft_scalar_v3d(-1, rst);
		inter->inside = TRUE;
	}
	else
		inter->inside = FALSE;
	return (rst);
}

/**
 * @brief Calculate the intersection points between a ray and a sphere.
 *
 * This function calculates the two intersection points of a ray with a
 * sphere defined by its center and radius. It stores the points in the
 * 'points' array.
 *
 * @param points An array to store the two intersection points.
 * @param origin The origin point of the ray.
 * @param dir The direction vector of the ray.
 * @param sph The sphere structure representing the sphere.
 */
static inline void	sphere_hit_area(t_dec points[2], t_v3d origin,
		t_v3d dir, t_sphere sph)
{
	t_v3d	dist_from_centre;
	t_dec	p[3];

	dist_from_centre = ft_minus_v3d(origin, sph.centre);
	p[0] = ft_length_v3d(dir);
	p[1] = 2 * ft_dot_v3d(dir, dist_from_centre);
	p[2] = ft_length_v3d(dist_from_centre) - sph.radius
		* sph.radius;
	quadratic(&p[0], &points[0]);
}

/**
 * @brief Determine the nearest valid intersection point.
 *
 * This function determines the nearest valid intersection point between two
 * calculated points based on the ray's direction and whether they are valid
 * and positive distances.
 *
 * @param points An array containing the two intersection points.
 *
 * @return The nearest valid intersection distance or INFINITY if no valid
 * intersection exists.
 */
static inline t_dec	hit_between_points(t_dec points[2])
{
	if (points[0] < points[1])
		return (points[0]);
	else
		return (points[1]);
}

/**
 * @brief Calculate the intersection point between a ray and a sphere.
 *
 * This function calculates the intersection point of a ray with a sphere
 * defined by its center and radius. It returns the distance from the ray's
 * origin to the intersection point or INFINITY if there is no intersection.
 *
 * @param origin The origin point of the ray.
 * @param dir The direction vector of the ray.
 * @param sph The sphere structure representing the sphere.
 *
 * @return The distance from the ray origin to the intersection point or
 * INFINITY if there is no intersection with the sphere.
 */
t_dec	sphere_solver(t_v3d origin, t_v3d dir, t_sphere sph)
{
	t_dec	distance;
	t_dec	points[2];
	t_v3d	p1;
	t_v3d	p2;

	distance = INFINITY;
	sphere_hit_area(points, origin, dir, sph);
	if (points[0] > EPSILON && points[0] < INFINITY)
		distance = points[0];
	if (points[1] > EPSILON && points[1] < INFINITY)
	{
		if (points[1] < points[0])
			distance = points[1];
	}
	if (sph.texture != HALF_SPHERE)
		return (distance);
	p1 = ft_plus_v3d(origin, ft_scalar_v3d(points[0], dir));
	p2 = ft_plus_v3d(origin, ft_scalar_v3d(points[1], dir));
	if (p1.y >= sph.centre.y && p2.y >= sph.centre.y)
		return (hit_between_points(points));
	else if (p1.y >= sph.centre.y)
		return (points[0]);
	else if (p2.y >= sph.centre.y)
		return (points[1]);
	return (INFINITY);
}
