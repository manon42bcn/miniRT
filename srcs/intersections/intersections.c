/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 18:35:15 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/03 18:35:18 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Find the closest intersection point with objects in the scene.
 *
 * This function iterates through the objects in the scene to find the closest
 * intersection point between a ray and the objects. It updates the `inter`
 * structure with information about the closest intersection, including the
 * distance, object, and other properties.
 *
 * @param inter The intersection structure to update with the closest
 * intersection data.
 * @param obj The linked list of objects in the scene.
 */
static inline void	get_inter(t_inter *inter, t_obj *obj)
{
	double		dist;
	t_obj		*node;

	inter->dist = INFINITY;
	inter->obj = NULL;
	node = obj;
	while (node)
	{
		dist = get_solver(inter->ray.from, inter->ray.to, node, inter);
		if (dist > EPSILON && dist < inter->dist)
		{
			inter->obj = node;
			inter->dist = dist;
		}
		node = node->next;
	}
}

/**
 * @brief Find the intersections of a ray with objects in the scene.
 *
 * This function finds the intersections of a ray with the objects in the scene
 * using the `get_inter` function. It updates the `inter` structure with
 * information about the closest intersection, including color, hit point,
 * material properties, and more.
 *
 * @param inter The intersection structure to update with the intersection data.
 * @param obj The linked list of objects in the scene.
 * @param mrt The main ray tracing data structure.
 */
void	get_hits(t_inter *inter, t_obj *obj, t_mrt *mrt)
{
	get_inter(inter, obj);
	if (inter->obj)
	{
		inter->color = inter->obj->color;
		inter->hit = ft_plus_v3d(inter->ray.from,
				ft_scalar_v3d(inter->dist, inter->ray.to));
		inter->reflex = inter->obj->reflex;
		inter->refract = inter->obj->refract;
		inter->specular = inter->obj->specular;
	}
	else
	{
		inter->color = mrt->scn.bgr;
		inter->reflex = 0.0;
		inter->refract = 0.0;
		inter->specular = FALSE;
	}
}
