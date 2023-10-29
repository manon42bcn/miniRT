/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 00:10:58 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/27 00:11:02 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Compute the normal vector at the point of intersection for common
 * geometric objects.
 *
 * This function calculates the normal vector for objects with a common
 * orientation, such as planes. Depending on the direction of the incoming ray,
 * it either returns the orientation of the object or its opposite.
 *
 * @param dir The direction of the incoming ray.
 * @param hit The point of intersection (currently unused, but may be required
 * for other shapes).
 * @param inter Pointer to the intersection structure containing details about
 * the intersection.
 *
 * @return The normal vector at the point of intersection.
 */
t_v3d	common_normal(t_v3d dir, t_v3d hit, t_inter *inter)
{
	(void)hit;
	if (ft_cos_v3d(dir, inter->obj->elm.fig.orient) > 0)
		return (ft_scalar_v3d(-1, inter->obj->elm.fig.orient));
	else
		return (inter->obj->elm.fig.orient);
}

#ifdef BONUS

/**
 * @brief Retrieve the normal vector at the intersection point for a given
 * shape.
 *
 * This function uses a table of function pointers to fetch the appropriate
 * normal calculation function based on the type of the shape. Depending on
 * the shape's geometry, different methods are required to determine the
 * correct normal vector at the point of intersection.
 *
 * For instance, the method to determine the normal for a sphere differs
 * significantly from that for a cone or a cylinder. Instead of having a
 * large conditional block to choose the appropriate function, this approach
 * allows for a clean, table-driven method to fetch the correct normal
 * calculation function.
 *
 * @param inter Pointer to the intersection structure containing details
 * about the intersection.
 * @param dir The direction of the incoming ray.
 * @param hit The point of intersection on the shape.
 *
 * @return The normalized normal vector at the point of intersection.
 */
t_v3d	get_normal(t_inter *inter, t_v3d dir, t_v3d hit)
{
	if (inter->obj->type == SPHERE)
		return (sphere_normal(dir, hit, inter));
	if (inter->obj->type == CYLINDER)
		return (cylinder_normal(dir, hit, inter));
	if (inter->obj->type == BOX)
		return (box_normal(dir, hit, inter));
	if (inter->obj->type == CONE)
		return (cone_normal(dir, hit, inter));
	if (inter->obj->type == ELLIPS)
		return (ellipsoid_normal(dir, hit, inter));
	else
		return (common_normal(dir, hit, inter));
}

#else

/**
 * @brief Retrieve the appropriate normal vector computation function
 * based on the object type. -MANDATORY VERSION-
 *
 * This function maps an object type to its corresponding function to compute
 * the normal vector at the point of intersection. It uses an array of function
 * pointers to efficiently select the correct normal vector computation method.
 *
 * @param obj Pointer to the object data.
 * @param dir The direction vector of the ray.
 * @param hit The point of intersection on the object.
 *
 * @return t_v3d The normal vector at the point of intersection on the object.
 */
t_v3d	get_normal(t_obj *obj, t_v3d dir, t_v3d hit)
{
	static t_normal	normal[] = {&sphere_normal, &common_normal,
		&cylinder_normal};

	return (normal[obj->type](dir, hit, obj));
}

#endif