/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 21:59:08 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/04 21:59:10 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Check if a point is inside a triangle defined by its vertices.
 *
 * This function checks if a given point is inside a triangle defined by its
 * three vertices.
 *
 * @param v1 The first vertex of the triangle.
 * @param v2 The second vertex of the triangle.
 * @param v3 The third vertex of the triangle.
 * @param inter_point The point being tested for inclusion.
 *
 * @return TRUE if the point is inside the triangle, FALSE otherwise.
 */
static inline t_bool	triangle_hit(t_v3d v1, t_v3d v2,
	t_v3d v3, t_v3d inter_point)
{
	t_v3d	point1;
	t_v3d	point2;
	t_v3d	point3;

	point1 = ft_minus_v3d(v2, v1);
	point2 = ft_minus_v3d(v3, v1);
	point3 = ft_minus_v3d(inter_point, v1);
	if (ft_cos_v3d(ft_cross_v3d(point1, point2),
			ft_cross_v3d(point1, point3)) < 0)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Find the intersection of a ray with a triangle.
 *
 * This function calculates the intersection point of a ray with a triangle
 * defined by its vertices and normal direction. It returns the distance from
 * the ray's origin to the intersection point or INFINITY if there is no
 * intersection.
 *
 * @param origin The origin point of the ray.
 * @param dir The direction vector of the ray.
 * @param trg The triangle structure representing the triangle.
 *
 * @return The distance from the ray origin to the intersection point or
 * INFINITY if there is no intersection with the triangle.
 */
double	triangle_solver(t_v3d origin, t_v3d dir, t_triangle trg)
{
	double	inter_dist;
	t_v3d	inter_point;

	inter_dist = plane_hit(origin, dir, trg.v1, trg.dir);
	inter_point = ft_plus_v3d(origin, ft_scalar_v3d(inter_dist, dir));
	if (triangle_hit(trg.v1, trg.v2,
			trg.v3, inter_point))
		return (INFINITY);
	if (triangle_hit(trg.v2, trg.v3, trg.v1, inter_point))
		return (INFINITY);
	if (triangle_hit(trg.v3, trg.v1, trg.v2, inter_point))
		return (INFINITY);
	return (inter_dist);
}
