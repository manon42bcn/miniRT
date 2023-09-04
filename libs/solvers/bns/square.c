/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 21:56:04 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/04 21:56:07 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @fn double square_solver(t_v3d origin, t_v3d dir, t_obj *sqr)
 * @brief Determines the intersection between a ray and a square.
 *
 * This function first checks if the ray intersects the plane on
 * which the square lies. Then, it verifies whether the intersection
 * point is inside the boundaries of the square. The geometry and
 * orientation of the square, along with the ray's direction, are used to
 * compute the intersection.
 *
 * @param origin Origin of the ray.
 * @param dir Direction of the ray.
 * @param sqr The square object.
 * @return Distance from the ray's origin to the intersection point.
 *         Returns INFINITY if the ray doesn't intersect with the square.
 */
double	square_solver(t_v3d origin, t_v3d dir, t_obj *sqr)
{
	t_v3d	inter_point;
	t_sq	square;
	double	inter_distance;
	double	cos_sqr;
	double	max_limit;

	inter_distance = plane_hit(origin, dir, sqr->elm.sq.centre, sqr->normal);
	inter_point = ft_plus_v3d(origin, ft_scalar_v3d(inter_distance, dir));
	if (fabs(sqr->normal.y) == 1)
		square.floor = (t_v3d){1, 0, 0};
	else
		square.floor = (t_v3d){0, 1, 0};
	square.half_size = ft_cross_v3d(sqr->normal, square.floor);
	square.center_to_ip = ft_minus_v3d(inter_point, sqr->elm.sq.centre);
	cos_sqr = fabs(ft_cos_v3d(square.half_size, square.center_to_ip));
	if (cos_sqr < SQRT2_2)
		cos_sqr = cos(M_PI_2 - acos(cos_sqr));
	max_limit = (sqr->elm.sq.side / 2) / cos_sqr;
	if (ft_mag_v3d(square.center_to_ip) <= max_limit)
		return (inter_distance);
	return (INFINITY);
}
