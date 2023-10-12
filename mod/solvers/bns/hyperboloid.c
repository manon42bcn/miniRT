/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 01:09:05 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/24 01:09:07 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Compute the normal vector of a hyperboloid at a given hit point.
 *
 * @param dir Unused. To make normal functions standard
 * @param hit The 3D point on the hyperboloid where the normal is to be
 * computed.
 * @param obj Pointer to the object structure containing details about the
 * hyperboloid.
 *
 * @return The computed normal vector at the given hit point on the hyperboloid.
 */
t_v3d	hyper_normal(t_v3d dir, t_v3d hit, t_obj *obj)
{
	t_v3d	normal;

	(void)dir;
	normal.x = 2 * hit.x / (obj->elm.hy.a * obj->elm.hy.a);
	normal.y = 2 * hit.y / (obj->elm.hy.b * obj->elm.hy.b);
	normal.z = -2 * hit.z / (obj->elm.hy.c * obj->elm.hy.c);
	return (ft_normal_v3d(normal));
}

/**
 * @brief Determine the quadratic coefficients for intersection with a
 * hyperboloid.
 *
 * The function calculates the coefficients needed to determine ray
 * hyperboloid intersections using the quadratic formula.
 *
 * @param coef Array to store the quadratic coefficients A, B, and C.
 * @param obj Pointer to the object structure containing details about
 * the hyperboloid.
 * @param origin The ray's origin point.
 * @param dir The ray's direction vector.
 */
void	hyper_quad(double *coef, t_obj *obj, t_v3d origin, t_v3d dir)
{
	t_hyper	hyper;

	hyper = obj->elm.hy;
	coef[E_A] = (dir.x * dir.x / (hyper.a * hyper.a))
		+ (dir.y * dir.y / (hyper.b * hyper.b))
		- (dir.z * dir.z / (hyper.c * hyper.c));
	coef[E_B] = 2 * (dir.x * (origin.x - hyper.centre.x) / (hyper.a * hyper.a)
			+ dir.y * (origin.y - hyper.centre.y) / (hyper.b * hyper.b)
			- dir.z * (origin.z - hyper.centre.z) / (hyper.c * hyper.c));
	coef[E_C] = ((origin.x - hyper.centre.x)
			* (origin.x - hyper.centre.x) / (hyper.a * hyper.a))
		+ ((origin.y - hyper.centre.y) * (origin.y - hyper.centre.y)
			/ (hyper.b * hyper.b))
		- ((origin.z - hyper.centre.z) * (origin.z - hyper.centre.z)
			/ (hyper.c * hyper.c)) - 1.0;
}

/**
 * @brief Solve for the intersection point of a ray with a
 * hyperboloid.
 *
 * Utilizes the quadratic coefficients to determine if and where a
 * ray intersects the hyperboloid.
 *
 * @param origin The ray's origin point.
 * @param dir The ray's direction vector.
 * @param obj Pointer to the object structure containing details about the
 * hyperboloid.
 *
 * @return The distance from the ray's origin to the intersection point,
 * or INFINITY if no intersection.
 */
double	hyper_solver(t_v3d origin, t_v3d dir, t_obj *obj)
{
	double	coef[3];
	double	t[2];

	hyper_quad(&coef[0], obj, origin, dir);
	if (!quadratic(&coef[0], &t[0]))
		return (INFINITY);
	return (t[0]);
}
