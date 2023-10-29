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

# ifdef BONUS

t_v3d	reflect_ray(t_v3d ray, t_v3d normal)
{
	return (ft_minus_v3d(ft_scalar_v3d(2
				* ft_dot_v3d(normal, ray), normal), ray));
}

void	get_inter(t_inter *inter, t_obj *obj, t_mrt *mrt)
{
	double		dist;
	t_obj		*node;

	inter->dist = INFINITY;
	inter->obj = NULL;
	node = obj;
	while (node)
	{
		pthread_mutex_lock(&mrt->getsolver);
		dist = get_solver(inter->ray.from, inter->ray.to, node);
		pthread_mutex_unlock(&mrt->getsolver);
		if (dist > EPSILON && dist < inter->dist)
		{
			inter->obj = node;
			inter->dist = dist;
		}
		node = node->next;
	}
}

#else

void	get_inter(t_inter *inter, t_obj *obj, t_mrt *mrt)
{
	double		dist;
	t_obj		*node;

	inter->dist = INFINITY;
	inter->obj = NULL;
	node = obj;
	while (node)
	{
		dist = get_solver(inter->ray.from, inter->ray.to, node);
		if (dist > EPSILON && dist < inter->dist)
		{
			inter->obj = node;
			inter->dist = dist;
		}
		node = node->next;
	}
}

#endif