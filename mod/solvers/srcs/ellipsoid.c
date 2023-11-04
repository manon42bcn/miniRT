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
 * @brief Calculate the normal vector for a hit point on an ellipsoid surface.
 *
 * This function computes the normal vector for a point of intersection on an
 * ellipsoid surface based on the incoming ray direction and the ellipsoid's
 * properties.
 *
 * @param dir The direction vector of the incoming ray (unused in this version).
 * @param hit The point of intersection on the ellipsoid surface.
 * @param inter Pointer to the intersection data structure.
 *
 * @return The normal vector at the point of intersection.
 */
t_v3d	ellipsoid_normal(t_v3d dir, t_v3d hit, t_inter *inter)
{
	t_v3d	normal;
	t_v3d	local;

	(void)dir;
	local = ft_minus_v3d(hit, inter->obj->elm.elp.centre);
	normal.x = 2.0 * local.x / (inter->obj->elm.elp.rx
			* inter->obj->elm.elp.rx);
	normal.y = 2.0 * local.y / (inter->obj->elm.elp.ry
			* inter->obj->elm.elp.ry);
	normal.z = 2.0 * local.z / (inter->obj->elm.elp.rz
			* inter->obj->elm.elp.rz);
	return (ft_normal_v3d(normal));
}

/**
 * @brief Calculate the coefficients for the quadratic equation representing an
 * ellipsoid.
 *
 * This function computes the coefficients of the quadratic equation that
 * represents the intersection of a ray with an ellipsoid. The equation is used
 * to solve for the intersection points.
 *
 * @param coef An array to store the coefficients (E_A, E_B, E_C) of the
 * quadratic equation.
 * @param elp The ellipsoid structure representing the ellipsoid.
 * @param origin The origin point of the ray.
 * @param dir The direction vector of the ray.
 */
static void	ellipsoid_quad(double *coef, t_ellip elp, t_v3d origin, t_v3d dir)
{
	t_v3d	oc;

	oc = ft_minus_v3d(origin, elp.centre);
	coef[E_A] = (dir.x * dir.x / (elp.rx * elp.rx))
		+ (dir.y * dir.y / (elp.ry * elp.ry))
		+ (dir.z * dir.z / (elp.rz * elp.rz));
	coef[E_B] = 2 * (oc.x * dir.x / (elp.rx * elp.rx))
		+ 2 * (oc.y * dir.y / (elp.ry * elp.ry))
		+ 2 * (oc.z * dir.z / (elp.rz * elp.rz));
	coef[E_C] = (oc.x * oc.x / (elp.rx * elp.rx))
		+ (oc.y * oc.y / (elp.ry * elp.ry))
		+ (oc.z * oc.z / (elp.rz * elp.rz)) - 1;
}

/**
 * @brief Calculate the intersection point of a ray with an ellipsoid.
 *
 * This function finds the intersection point of a ray with an ellipsoid and
 * returns the distance from the ray origin to the intersection point. It uses
 * quadratic equations to solve for the intersection.
 *
 * @param origin The origin point of the ray.
 * @param dir The direction vector of the ray.
 * @param elp The ellipsoid structure representing the ellipsoid.
 *
 * @return The distance from the ray origin to the intersection point or INFINITY
 * if there is no intersection with the ellipsoid.
 */
double	ellipsoid_solver(t_v3d origin, t_v3d dir, t_ellip elp)
{
	double	coef[3];
	double	t[2];

	ellipsoid_quad(&coef[0], elp, origin, dir);
	if (!quadratic(&coef[0], &t[0]))
		return (INFINITY);
	if (t[0] > 0)
		return (t[0]);
	if (t[1] > 0)
		return (t[1]);
	return (INFINITY);
}
