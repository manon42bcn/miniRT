/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solvers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:00:58 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/04 13:01:00 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

#ifdef BONUS

/**
 * @brief Returns a pointer to the appropriate solver function for a
 * specified geometric object type (Bonus version).
 *
 * Maps an index representing the type of an object to its corresponding
 * solver function. This solver function is used to determine if and
 * how a ray intersects the object. Includes solvers for advanced
 * geometric shapes.
 *
 * @param index Integer representing the object type.
 * @return A pointer to the solver function corresponding to the given
 * object type.
 */
double	get_solver(t_v3d origin, t_v3d dir, t_obj *obj, t_inter *inter)
{
	int	type;

	type = obj->type;
	if (type == SPHERE)
		return (sphere_solver(origin, dir, obj->elm.sph));
	if (type == PLANE)
		return (plane_solver(origin, dir, obj->elm.pl));
	if (type == CYLINDER)
		return (cylinder_solver(origin, dir, obj->elm.cyl));
	if (type == RECTANGLE)
		return (rectangle_solver(origin, dir, obj->elm.rc));
	if (type == TRIANGLE)
		return (triangle_solver(origin, dir, obj->elm.trg));
	if (type == BOX)
		return (box_solver(origin, dir, obj->elm.box, inter));
	if (type == CONE)
		return (cone_solver(origin, dir, obj->elm.con));
	if (type == ELLIPS)
		return (ellipsoid_solver(origin, dir, obj->elm.elp));
	return (INFINITY);
}

#else

/**
 * @brief Returns a pointer to the appropriate solver function for a
 * specified geometric object type (Standard version).
 *
 * Similar to the Bonus version, but limited to basic geometric shapes.
 *
 * @param index Integer representing the object type.
 * @return A pointer to the solver function corresponding to the
 * given object type.
 */
double	get_solver(t_v3d origin, t_v3d dir, int type, t_obj *obj)
{
	if (type == SPHERE)
		return (sphere_solver(origin, dir, obj->elm.sph));
	if (type == CYLINDER)
		return (cylinder_solver(origin, dir, obj->elm.cyl));
	else
		return (plane_solver(origin, dir, obj->elm.pl));
}

#endif
