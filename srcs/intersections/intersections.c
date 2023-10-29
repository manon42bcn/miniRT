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
# ifdef BONUS

t_obj	*get_inter(t_inter *inter, t_obj *obj, t_mrt *mrt)
{
	double		dist;
	t_solver	solve;
	t_obj		*node;

	inter->dist = INFINITY;
	inter->obj = NULL;
	node = obj;
	while (node)
	{
		pthread_mutex_lock(&mrt->gethits);
		solve = get_solver(node->type);
		dist = solve(inter->ray.from, inter->ray.to, node);
		pthread_mutex_unlock(&mrt->gethits);
		if (dist > EPSILON && dist < inter->dist)
		{
			inter->obj = node;
			inter->dist = dist;
		}
		node = node->next;
	}
	return (inter->obj);
}

#else

t_obj	*get_inter(t_inter *inter, t_obj *obj)
{
	double		dist;
	t_solver	solve;
	t_obj		*node;

	inter->dist = INFINITY;
	inter->obj = NULL;
	node = obj;
	while (node)
	{
		solve = get_solver(node->type);
		dist = solve(inter->ray.from, inter->ray.to, node);
		if (dist > EPSILON && dist < inter->dist)
		{
			inter->obj = node;
			inter->dist = dist;
		}
		node = node->next;
	}
	return (inter->obj);
}

#endif