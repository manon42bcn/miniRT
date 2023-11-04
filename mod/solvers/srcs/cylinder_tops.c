/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_tops.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 17:40:01 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/04 17:40:03 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Calculate the normal vector for a hit point on a cylinder's surface.
 *
 * This function calculates the normal vector for a point of intersection on a
 * cylinder's surface based on the incoming ray direction and the cylinder's
 * properties.
 *
 * @param dir The direction vector of the incoming ray.
 * @param hit The point of intersection on the cylinder's surface.
 * @param inter Pointer to the intersection data structure.
 *
 * @return The normal vector at the point of intersection.
 */
t_v3d	cylinder_normal(t_v3d dir, t_v3d hit, t_inter *inter)
{
	t_v3d	local_hit;
	double	dot;

	local_hit = ft_minus_v3d(hit, inter->obj->elm.cyl.centre);
	dot = ft_dot_v3d(local_hit, inter->obj->elm.cyl.dir);
	if (dot < EPSILON || fabs(dot - inter->obj->elm.cyl.height) < EPSILON)
	{
		if (ft_cos_v3d(dir, inter->obj->elm.cyl.dir) > 0)
			return (ft_scalar_v3d(-1, inter->obj->elm.cyl.dir));
		else
			return (inter->normal);
	}
	return (ft_normal_v3d(ft_minus_v3d(local_hit,
				ft_scalar_v3d(dot, inter->obj->elm.cyl.dir))));
}

/**
 * @brief Check if a point is within a specified range from another point.
 *
 * This function checks if a given point is within a specified range (radius)
 * from another point (center).
 *
 * @param id The distance from the given point to the center.
 * @param point The point being tested.
 * @param centre The center point.
 * @param radius The specified range (radius).
 *
 * @return 1 if the point is within the specified range, 0 otherwise.
 */
static inline int	is_within_range(double id, t_v3d point,
			t_v3d centre, double radius)
{
	return (id < INFINITY && ft_distance_v3d(point, centre) <= radius);
}

/**
 * @brief Handle the intersection with the top and bottom caps of a cylinder.
 *
 * This function handles the intersection with the top and bottom caps of a
 * cylinder. It checks if the intersection points are within the caps and returns
 * the closest intersection point if any.
 *
 * @param id1 The intersection distance for the first cap.
 * @param id2 The intersection distance for the second cap.
 * @param p An array containing intersection points.
 * @param cyl The cylinder structure representing the cylinder.
 *
 * @return The closest intersection distance or INFINITY if there is no
 * intersection.
 */
static inline double	handle_intersection(double id1, double id2,
											t_v3d p[], t_cylinder cyl)
{
	if (is_within_range(id1, p[IP1], cyl.centre, cyl.radius)
		&& is_within_range(id2, p[IP2], p[C_DIST], cyl.radius))
	{
		if (id1 < id2)
			return (id1);
		else
			return (id2);
	}
	if (is_within_range(id1, p[IP1], cyl.centre, cyl.radius))
		return (id1);
	if (is_within_range(id2, p[IP2], p[C_DIST], cyl.radius))
		return (id2);
	return (INFINITY);
}

/**
 * @brief Find the intersection point of a ray with a cylinder's top cap.
 *
 * This function calculates the intersection point of a ray with a cylinder's
 * top cap. It returns the distance from the ray's origin to the intersection
 * point.
 *
 * @param o The origin point of the ray.
 * @param d The direction vector of the ray.
 * @param cyl The cylinder structure representing the cylinder.
 *
 * @return The distance from the ray origin to the intersection point or
 * INFINITY if there is no intersection with the top cap.
 */
double	top_intersect(t_v3d o, t_v3d d, t_cylinder cyl)
{
	double	id1;
	double	id2;
	t_v3d	p[3];
	t_v3d	o_d[2];

	p[C_DIST] = ft_plus_v3d(cyl.centre,
			ft_scalar_v3d(cyl.height, cyl.dir));
	o_d[0] = o;
	o_d[1] = d;
	id1 = plane_hit(o, d, cyl.centre, cyl.dir);
	id2 = plane_hit(o, d, p[C_DIST], cyl.dir);
	if (id1 < INFINITY || id2 < INFINITY)
	{
		p[IP1] = ft_plus_v3d(o_d[0], ft_scalar_v3d(id1, o_d[1]));
		p[IP2] = ft_plus_v3d(o_d[0], ft_scalar_v3d(id2, o_d[1]));
		return (handle_intersection(id1, id2, p, cyl));
	}
	return (INFINITY);
}
