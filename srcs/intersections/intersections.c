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
 * @brief Compute the reflection of a ray given its normal.
 *
 * The function calculates the reflection of an incoming ray with respect
 * to the given normal.
 *
 * @param ray The incoming ray direction.
 * @param normal The normal direction at the reflection point.
 * @return The reflected ray direction.
 */
t_v3d	reflect_ray(t_v3d ray, t_v3d normal)
{
	return (ft_minus_v3d(ft_scalar_v3d(2
				* ft_dot_v3d(normal, ray), normal), ray));
}

/**
 * @brief Iterates through all objects in the scene and identifies the
 * closest object that the ray intersects.
 *
 * Uses the solver specific to each object type to determine the intersection
 * distance. If the intersection distance is closer than the current closest
 * intersection, the function updates the closest intersection and object
 * references.
 *
 * @param ray The casted ray.
 * @param obj Pointer to the list of objects in the scene.
 * @param closest_figure Reference to the closest intersected object.
 * @param closest_intersection Reference to the distance to the closest
 * intersected object.
 */
void	try_all_intersections(t_ray ray, t_obj *obj,
					t_obj *closest_figure, double *closest_intersection)
{
	double		dist;
	t_solver	solve;

	while (obj)
	{
		solve = get_solver(obj->type);
		dist = solve(ray.from, ray.to, obj);
		if (dist > EPSILON && dist < *closest_intersection)
		{
			*closest_figure = *obj;
			*closest_intersection = dist;
		}
		obj = obj->next;
	}
	rayer++;
}
