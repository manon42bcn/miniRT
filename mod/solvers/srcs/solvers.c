/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solvers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:00:58 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/15 00:53:11 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

#ifdef BONUS

/* @brief Get the solver for ray-object intersection.
* -BONUS VERSION-
* This function calculates the intersection point of a ray with a specific object
* and returns the distance from the ray origin to the intersection point.
*
* @param origin The origin point of the ray.
* @param dir The direction vector of the ray.
* @param obj Pointer to the object for which the intersection is calculated.
* @param inter Pointer to the intersection data structure to be updated.
*
* @return The distance from the ray origin to the intersection point or INFINITY
* if there is no intersection.
*/
t_dec	get_solver(t_v3d origin, t_v3d dir, t_obj *obj, t_inter *inter)
{
	int	type;

	type = obj->type;
	if (type == SPHERE)
		return (sphere_solver(origin, dir, obj->elm.sph));
	if (type == PLANE)
		return (plane_solver(origin, dir, obj->elm.pl));
	if (type == CYLINDER)
		return (cylinder_solver(origin, dir, obj->elm.cyl, inter));
	if (type == RECTANGLE)
		return (rectangle_solver(origin, dir, obj->elm.rc));
	if (type == TRIANGLE)
		return (triangle_solver(origin, dir, obj->elm.trg));
	if (type == BOX)
		return (box_solver(origin, dir, obj->elm.box, inter));
	if (type == CONE)
		return (cone_solver(origin, dir, obj->elm.con));
	return (INFINITY);
}

#else

/**
 * @brief Get the solver for ray-object intersection without the BONUS feature.
 *
 * This function calculates the intersection point of a ray with a specific
 * object and returns the distance from the ray origin to the intersection point.
 *
 * @param origin The origin point of the ray.
 * @param dir The direction vector of the ray.
 * @param obj Pointer to the object for which the intersection is calculated.
 * @param inter This parameter is unused in this version.
 *
 * @return The distance from the ray origin to the intersection point or INFINITY
 * if there is no intersection.
 */
t_dec	get_solver(t_v3d origin, t_v3d dir, t_obj *obj, t_inter *inter)
{
	int	type;

	type = obj->type;
	if (type == SPHERE)
		return (sphere_solver(origin, dir, obj->elm.sph));
	if (type == CYLINDER)
		return (cylinder_solver(origin, dir, obj->elm.cyl, inter));
	else
		return (plane_solver(origin, dir, obj->elm.pl));
}

#endif
