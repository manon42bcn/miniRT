/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:30:53 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/25 19:30:55 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Calculate the normal vector of an ellipsoid at a given point.
 *
 * Computes the surface normal of an ellipsoid at the specified point. The
 * normal is essential for shading calculations in computer graphics.
 *
 * @param dir Unused. To make normal functions standard
 * @param hit The 3D point on the ellipsoid's surface where the normal is to
 * be computed.
 * @param obj Pointer to the object structure, which contains details about the
 * ellipsoid.
 *
 * @return The normal vector at the specified point on the ellipsoid.
 */
t_v3d	ellipsoid_normal(t_v3d dir, t_v3d hit, t_obj *obj)
{
	t_v3d	normal;
	t_v3d	local;

	(void)dir;
	local = ft_minus_v3d(hit, obj->elm.elp.centre);
	normal.x = 2.0 * local.x / (obj->elm.elp.rx * obj->elm.elp.rx);
	normal.y = 2.0 * local.y / (obj->elm.elp.ry * obj->elm.elp.ry);
	normal.z = 2.0 * local.z / (obj->elm.elp.rz * obj->elm.elp.rz);
	return (ft_normal_v3d(normal));
}

/**
 * @brief Calculate the coefficients for a quadratic equation representing an
 *        ellipsoid intersection.
 *
 * Given an ellipsoid object and a ray defined by its origin and direction, this
 * function computes the coefficients for the quadratic equation that
 * represents the intersection of the ray with the ellipsoid, and store them
 * at coef array.
 *
 * @param coef   An array to store the coefficients [A, B, C] of the
 *               quadratic equation.
 * @param obj    A pointer to the ellipsoid object.
 * @param origin The origin point of the ray.
 * @param dir    The direction vector of the ray.
 */
static void	ellipsoid_quad(double *coef, t_obj *obj, t_v3d origin, t_v3d dir)
{
	t_v3d	oc;

	oc = ft_minus_v3d(origin, obj->elm.elp.centre);
	coef[E_A] = (dir.x * dir.x / (obj->elm.elp.rx * obj->elm.elp.rx))
		+ (dir.y * dir.y / (obj->elm.elp.ry * obj->elm.elp.ry))
		+ (dir.z * dir.z / (obj->elm.elp.rz * obj->elm.elp.rz));
	coef[E_B] = 2 * (oc.x * dir.x / (obj->elm.elp.rx * obj->elm.elp.rx))
		+ 2 * (oc.y * dir.y / (obj->elm.elp.ry * obj->elm.elp.ry))
		+ 2 * (oc.z * dir.z / (obj->elm.elp.rz * obj->elm.elp.rz));
	coef[E_C] = (oc.x * oc.x / (obj->elm.elp.rx * obj->elm.elp.rx))
		+ (oc.y * oc.y / (obj->elm.elp.ry * obj->elm.elp.ry))
		+ (oc.z * oc.z / (obj->elm.elp.rz * obj->elm.elp.rz)) - 1;
}

/**
 * @brief Solve for the intersection between a ray and an ellipsoid.
 *
 * Given a ray defined by its origin and direction, this function calculates the
 * intersection points between the ray and an ellipsoid object. It returns the
 * minimum non-negative solution or INFINITY if no intersection occurs.
 *
 * @param origin A point representing the origin of the ray.
 * @param dir    The direction vector of the ray.
 * @param obj    A pointer to the ellipsoid object.
 *
 * @return The minimum non-negative intersection distance or INFINITY if there
 *         is no intersection.
 */
double	ellipsoid_solver(t_v3d origin, t_v3d dir, t_obj *obj)
{
	double	coef[3];
	double	t[2];

	ellipsoid_quad(&coef[0], obj, origin, dir);
	if (!quadratic(&coef[0], &t[0]))
		return (INFINITY);
	if (t[0] > 0)
		return (t[0]);
	if (t[1] > 0)
		return (t[1]);
	return (INFINITY);
}
