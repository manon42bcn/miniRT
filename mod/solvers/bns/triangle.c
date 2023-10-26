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
 * @brief Checks if a given intersection point is inside a triangle.
 *
 * This function uses the barycentric technique to determine if the
 * intersection point is within the triangle boundaries. The barycentric
 * technique leverages vector cross products to check the location of the
 * intersection point relative to the triangle's vertices.
 *
 * @param v1 First vertex of the triangle.
 * @param v2 Second vertex of the triangle.
 * @param v3 Third vertex of the triangle.
 * @param inter_point The point to be checked if it lies within the
 * triangle.
 * @return TRUE if the intersection point is outside the triangle,
 * FALSE otherwise.
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
 * @brief Determines the intersection between a ray and a triangle.
 *
 * This function checks if the ray intersects the plane on which the
 * triangle lies. After finding the intersection point with the plane,
 * the function verifies whether the point is within the triangle's boundaries.
 *
 * @param origin Origin of the ray.
 * @param dir Direction of the ray.
 * @param trg The triangle object.
 * @return Distance from the ray's origin to the intersection point.
 *         Returns INFINITY if the ray doesn't intersect with the triangle.
 */
double	triangle_solver(t_v3d origin, t_v3d dir, t_obj *trg)
{
	double	inter_dist;
	t_v3d	inter_point;

	inter_dist = plane_hit(origin, dir, trg->elm.trg.v1, trg->elm.trg.dir);
	inter_point = ft_plus_v3d(origin, ft_scalar_v3d(inter_dist, dir));
	if (triangle_hit(trg->elm.trg.v1, trg->elm.trg.v2,
			trg->elm.trg.v3, inter_point))
		return (INFINITY);
	if (triangle_hit(trg->elm.trg.v2, trg->elm.trg.v3,
			trg->elm.trg.v1, inter_point))
		return (INFINITY);
	if (triangle_hit(trg->elm.trg.v3, trg->elm.trg.v1,
			trg->elm.trg.v2, inter_point))
		return (INFINITY);
	return (inter_dist);
}
