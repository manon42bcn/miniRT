/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:10:04 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/04 13:10:06 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Checks if a ray intersects with the cylinder.
 *
 * @param x[2] Array storing intersection points.
 * @param origin Starting point of the ray.
 * @param dir Direction of the ray.
 * @param cyl The cylinder object.
 * @return TRUE if there's an intersection, FALSE otherwise.
 */
static inline t_bool	cyl_is_hit(double x[2], t_v3d origin,
	t_v3d dir, t_cylinder cyl)
{
	t_v3d	v;
	t_v3d	u;
	double	qr[3];

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
 * @brief Computes the correct distance and intersection point from
 * the two potential intersections.
 *
 * @param cyl The cylinder object.
 * @param x2[2] Intersection points.
 * @param dist Pointer to store the chosen distance.
 * @param x Pointer to store the chosen intersection point.
 */
static inline void	compute_dist_x(t_cylinder cyl, double x2[2],
	double *dist, double *x)
{
	*x = x2[1];
	if ((cyl.d1 >= 0 && cyl.d1 <= cyl.height && x2[0] > EPSILON)
		&& (cyl.d2 >= 0 && cyl.d2 <= cyl.height && x2[1] > EPSILON))
	{
		if (x2[0] < x2[1])
		{
			*dist = cyl.d1;
			*x = x2[0];
		}
		else
			*dist = cyl.d2;
	}
	else if (cyl.d1 >= 0 && cyl.d1 <= cyl.height && x2[0] > EPSILON)
	{
		*dist = cyl.d1;
		*x = x2[0];
	}
	else
		*dist = cyl.d2;
}

/**
 * @brief Determines the orientation of the cylinder at the
 * point of intersection.
 *
 * @param x2[2] Intersection points.
 * @param from Starting point of the ray.
 * @param to Direction of the ray.
 * @param cyl The cylinder object.
 * @return A normalized vector representing the orientation.
 */
static inline t_v3d	cyl_orientation(double x2[2], t_v3d from,
	t_v3d to, t_cylinder cyl)
{
	double	dist;
	double	x;

	compute_dist_x(cyl, x2, &dist, &x);
	x2[0] = x;
	return (ft_normal_v3d(ft_minus_v3d(ft_minus_v3d
				(ft_scalar_v3d(x, to),
					ft_scalar_v3d(dist, cyl.dir)),
				ft_minus_v3d(cyl.centre, from))));
}

/**
 * @brief Computes the intersection of the ray with the body of the cylinder.
 *
 * @param o Starting point of the ray.
 * @param d Direction of the ray.
 * @param normal Vector to store the normal at the intersection point.
 * @param lst The list of objects in the scene.
 * @return The distance from the ray's origin to the intersection point,
 * or INFINITY if no intersection.
 */
static inline double	body_intersect(t_v3d o, t_v3d d,
		t_v3d *normal, t_cylinder cyl)
{
	double	x2[2];

	if (cyl_is_hit(x2, o, d, cyl) == FALSE)
		return (INFINITY);
	cyl.d1 = ft_dot_v3d(cyl.dir,
			ft_minus_v3d(ft_scalar_v3d(x2[0], d),
				ft_minus_v3d(cyl.centre, o)));
	cyl.d2 = ft_dot_v3d(cyl.dir,
			ft_minus_v3d(ft_scalar_v3d(x2[1], d),
				ft_minus_v3d(cyl.centre, o)));
	if (!((cyl.d1 >= 0 && cyl.d1 <= cyl.height
				&& x2[0] > EPSILON) || (cyl.d2 >= 0
				&& cyl.d2 <= cyl.height && x2[0] > EPSILON)))
		return (INFINITY);
	*normal = cyl_orientation(x2, o, d, cyl);
	return (x2[0]);
}

/**
 * @brief Main solver function for the cylinder object.
 *
 * Computes intersections against the body of the cylinder.
 * If the texture is not equal to 4, it also checks intersections with the
 * top of the cylinder.
 * It will return the closest intersection point.
 *
 * @param from Starting point of the ray.
 * @param dir Direction of the ray.
 * @param cyl The cylinder object.
 * @return The distance from the ray's origin to the closest intersection point,
 * or INFINITY if no intersection.
 */
double	cylinder_solver(t_v3d from, t_v3d dir, t_cylinder cyl)
{
	double	cylinder_inter;
	double	caps_inter;
	t_v3d	cy_normal;

	cylinder_inter = body_intersect(from, dir, &cy_normal, cyl);
	if (cyl.texture == 4)
		caps_inter = INFINITY;
	else
		caps_inter = top_intersect(from, dir, cyl);
	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
	{
		if (cylinder_inter < caps_inter)
			return (cylinder_inter);
		return (caps_inter);
	}
	return (INFINITY);
}
