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
 * @brief Compute the normal vector for common figures.
 *
 * This function is a generic method to determine the normal vector on the
 * surface of various geometric figures, especially for figures where the
 * normal direction is directly based on the object's orientation.
 *
 * @param dir The direction vector of the ray.
 * @param hit Unused. To make normal functions standard
 * @param obj Pointer to the object data which contains figure's orientation
 * information.
 *
 * @return t_v3d The normal vector at the figure, based on its orientation.
 */
t_v3d	common_normal(t_v3d dir, t_v3d hit, t_obj *obj)
{
	(void)hit;
	if (ft_cos_v3d(dir, obj->elm.fig.orient) > 0)
		return (ft_scalar_v3d(-1, obj->elm.fig.orient));
	else
		return (obj->elm.fig.orient);
}

#ifdef BONUS

/**
 * @brief Retrieve the appropriate normal vector computation function
 * based on the object type. -BONUS VERSION-
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
		&cylinder_normal, &common_normal, &common_normal,
		&box_normal, &common_normal, &cone_normal};

	return (normal[obj->type](dir, hit, obj));
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