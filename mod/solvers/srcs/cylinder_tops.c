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
 * @brief Compute the intersection points given the intersection distances.
 *
 * @param p[] Array to store computed intersection points.
 * @param o_d[] Array containing starting point of the ray (o_d[0])
 * and its direction (o_d[1]).
 * @param id1 Intersection distance for the first intersection.
 * @param id2 Intersection distance for the second intersection.
 */
static inline void	compute_p_values(t_v3d p[], t_v3d o_d[],
	double id1, double id2)
{
	p[IP1] = ft_plus_v3d(o_d[0], ft_scalar_v3d(id1, o_d[1]));
	p[IP2] = ft_plus_v3d(o_d[0], ft_scalar_v3d(id2, o_d[1]));
}

/**
 * @brief Check if a point is within a given distance from the cylinder center.
 *
 * @param id Intersection distance.
 * @param point Intersection point.
 * @param centre Center of the cylinder.
 * @param radius Radius of the cylinder.
 * @return Returns 1 if within range, 0 otherwise.
 */
static inline int	is_within_range(double id, t_v3d point,
	t_v3d centre, double radius)
{
	return (id < INFINITY && ft_distance_v3d(point, centre) <= radius);
}

/**
 * @brief Determine the appropriate intersection distance.
 *
 * Given two potential intersections, determine which is the correct one.
 * The function will also ensure the intersection is within the
 * cylinder's bounds.
 *
 * @param id1 Intersection distance for the first intersection.
 * @param id2 Intersection distance for the second intersection.
 * @param p[] Intersection points.
 * @param lst The list of objects in the scene.
 * @return The correct intersection distance, or INFINITY if
 * no valid intersection.
 */
static inline double	handle_intersection(double id1, double id2,
	t_v3d p[], t_obj *lst)
{
	if (is_within_range(id1, p[IP1], lst->elm.cyl.centre, lst->elm.cyl.radius)
		&& is_within_range(id2, p[IP2], p[C_DIST], lst->elm.cyl.radius))
	{
		if (id1 < id2)
			return (id1);
		else
			return (id2);
	}
	if (is_within_range(id1, p[IP1], lst->elm.cyl.centre, lst->elm.cyl.radius))
		return (id1);
	if (is_within_range(id2, p[IP2], p[C_DIST], lst->elm.cyl.radius))
		return (id2);
	return (INFINITY);
}

/**
 * @brief Main solver function for intersections with the top of the cylinder.
 *
 * Computes intersections against the top cap of the cylinder.
 * Uses helper functions to calculate and validate intersection points.
 *
 * @param o Starting point of the ray.
 * @param d Direction of the ray.
 * @param lst The list of objects in the scene.
 * @return The distance from the ray's origin to the intersection point,
 * or INFINITY if no intersection.
 */
double	top_intersect(t_v3d o, t_v3d d, t_obj *lst)
{
	double	id1;
	double	id2;
	t_v3d	p[3];
	t_v3d	o_d[2];

	p[C_DIST] = ft_plus_v3d(lst->elm.cyl.centre,
			ft_scalar_v3d(lst->elm.cyl.height, lst->elm.cyl.dir));
	o_d[0] = o;
	o_d[1] = d;
	id1 = plane_hit(o, d, lst->elm.cyl.centre, lst->elm.cyl.dir);
	id2 = plane_hit(o, d, p[C_DIST], lst->elm.cyl.dir);
	if (id1 < INFINITY || id2 < INFINITY)
	{
		compute_p_values(p, o_d, id1, id2);
		return (handle_intersection(id1, id2, p, lst));
	}
	return (INFINITY);
}
