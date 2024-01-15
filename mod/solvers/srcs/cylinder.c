/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:10:04 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/15 00:40:15 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Check if a ray intersects with the side surface of a cylinder.
 *
 * This function checks if a ray intersects with the side surface of a cylinder.
 * If an intersection is found, it returns TRUE and stores the intersection
 * points in the array 'x'. If no intersection is found, it returns FALSE.
 *
 * @param x An array to store the intersection points.
 * @param o The origin point of the ray.
 * @param d The direction vector of the ray.
 * @param cyl The cylinder structure representing the cylinder.
 *
 * @return TRUE if an intersection is found, FALSE otherwise.
 */
static inline t_bool	cyl_is_hit(t_dec x[2], t_v3d origin,
					t_v3d dir, t_cylinder cyl)
{
	t_v3d	v;
	t_v3d	u;
	t_dec	qr[3];

	v = ft_scalar_v3d(ft_dot_v3d(dir, cyl.dir), cyl.dir);
	v = ft_minus_v3d(dir, v);
	u = ft_scalar_v3d(ft_dot_v3d(ft_minus_v3d(origin, cyl.centre),
				cyl.dir), cyl.dir);
	u = ft_minus_v3d(ft_minus_v3d(origin, cyl.centre), u);
	qr[0] = ft_length_v3d(v);
	qr[1] = 2 * ft_dot_v3d(v, u);
	qr[2] = ft_dot_v3d(u, u) - (cyl.radius * cyl.radius);
	if (!quadratic(&qr[0], &x[0]))
		return (FALSE);
	if (x[0] < EPSILON && x[1] < EPSILON)
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief Calculate the intersection points and distances for a cylinder's side
 * surface.
 *
 * This function calculates the intersection points and distances for a ray
 * intersecting with the side surface of a cylinder. It takes into account the
 * height of the cylinder and determines the closest intersection point and
 * distance.
 *
 * @param cyl The cylinder structure representing the cylinder.
 * @param x2 An array to store the two intersection points.
 * @param dist A pointer to store the calculated distance.
 * @param x A pointer to store the intersection point.
 */
static inline void	compute_dist_x(t_cylinder cyl, t_dec x2[2],
					t_dec *dist, t_dec *x)
{
	*x = x2[1];
	*dist = cyl.d2;
	if ((cyl.d1 >= 0 && cyl.d1 <= cyl.height && x2[0] > EPSILON)
		&& (cyl.d2 >= 0 && cyl.d2 <= cyl.height && x2[1] > EPSILON))
	{
		if (x2[0] < x2[1])
		{
			*dist = cyl.d1;
			*x = x2[0];
		}
	}
	else if (cyl.d1 >= 0 && cyl.d1 <= cyl.height && x2[0] > EPSILON)
	{
		*dist = cyl.d1;
		*x = x2[0];
	}
}

/**
 * @brief Calculate the normal vector for a point of intersection on a
 * cylinder's side surface.
 *
 * This function calculates the normal vector for a point of intersection on
 * a cylinder's side surface. It considers the orientation of the cylinder.
 *
 * @param x2 An array containing the intersection points.
 * @param from The starting point of the ray.
 * @param to The direction vector of the ray.
 * @param cyl The cylinder structure representing the cylinder.
 *
 * @return The normal vector at the point of intersection.
 */
static inline t_v3d	cyl_orientation(t_dec x2[2], t_v3d from,
					t_v3d to, t_cylinder cyl)
{
	t_dec	dist;
	t_dec	x;

	compute_dist_x(cyl, x2, &dist, &x);
	x2[0] = x;
	return (ft_normal_v3d(ft_minus_v3d(ft_minus_v3d
				(ft_scalar_v3d(x, to),
					ft_scalar_v3d(dist, cyl.dir)),
				ft_minus_v3d(cyl.centre, from))));
}

/**
 * @brief Find the intersection point of a ray with a cylinder's side surface.
 *
 * This function calculates the intersection point of a ray with the side surface
 * of a cylinder. It also computes the normal vector at the intersection point.
 *
 * @param o The origin point of the ray.
 * @param d The direction vector of the ray.
 * @param normal Pointer to store the calculated normal vector.
 * @param cyl The cylinder structure representing the cylinder.
 *
 * @return The distance from the ray's origin to the intersection point or
 * INFINITY if there is no intersection with the cylinder's side surface.
 */
static inline t_dec	body_intersect(t_v3d o, t_v3d d, t_v3d *normal,
	t_cylinder cyl)
{
	t_dec	x2[2];

	if (cyl_is_hit(x2, o, d, cyl) == FALSE)
		return (INFINITY);
	cyl.d1 = ft_dot_v3d(cyl.dir,
			ft_minus_v3d(ft_scalar_v3d(x2[0], d),
				ft_minus_v3d(cyl.centre, o)));
	cyl.d2 = ft_dot_v3d(cyl.dir,
			ft_minus_v3d(ft_scalar_v3d(x2[1], d),
				ft_minus_v3d(cyl.centre, o)));
	if (!((cyl.d1 >= 0 && cyl.d1 <= cyl.height && x2[0] > EPSILON)
			|| (cyl.d2 >= 0 && cyl.d2 <= cyl.height && x2[0] > EPSILON)))
		return (INFINITY);
	*normal = cyl_orientation(x2, o, d, cyl);
	return (x2[0]);
}

/**
 * @brief Find the intersection of a ray with a cylinder.
 *
 * This function calculates the intersection point of a ray with a cylinder,
 * including the side surface and the caps (if applicable). It returns the
 * distance from the ray's origin to the intersection point.
 *
 * @param from The origin point of the ray.
 * @param dir The direction vector of the ray.
 * @param cyl The cylinder structure representing the cylinder.
 * @param inter Pointer to the intersection data structure to be updated.
 *
 * @return The distance from the ray origin to the intersection point or INFINITY
 * if there is no intersection with the cylinder.
 */
t_dec	cylinder_solver(t_v3d from, t_v3d dir, t_cylinder cyl, t_inter *inter)
{
	t_dec	cylinder_inter;
	t_dec	caps_inter;

	cylinder_inter = body_intersect(from, dir, &inter->normal, cyl);
	if (cyl.texture == NO_CAPS)
		caps_inter = INFINITY;
	else
		caps_inter = top_intersect(from, dir, cyl);
	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
	{
		if (cylinder_inter < caps_inter)
			return (cylinder_inter);
		inter->normal = cyl.dir;
		return (caps_inter);
	}
	return (INFINITY);
}
