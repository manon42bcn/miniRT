/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:40:59 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/23 15:59:08 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

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

static inline void	sphere_hit_area(double points[2], t_v3d origin,
		t_v3d dir, t_sphere sph)
{
	t_v3d	dist_from_centre;
	double	p[3];

	dist_from_centre = ft_minus_v3d(origin, sph.centre);
	p[0] = ft_length_v3d(dir);
	p[1] = 2 * ft_dot_v3d(dir, dist_from_centre);
	p[2] = ft_length_v3d(dist_from_centre) - sph.radius
		* sph.radius;
	quadratic(&p[0], &points[0]);
}


static inline double	hit_between_points(double points[2])
{
	if (points[0] < points[1])
		return (points[0]);
	else
		return (points[1]);
}

double	sphere_solver(t_v3d origin, t_v3d dir, t_sphere sph)
{
	double	distance;
	double	points[2];
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
	if (sph.texture != 4)
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
