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

static inline void	get_inter(t_inter *inter, t_obj *obj, t_mrt *mrt)
{
	double		dist;
	t_obj		*node;

	inter->dist = INFINITY;
	inter->obj = NULL;
	node = obj;
	(void)mrt;
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

void	get_hits(t_inter *inter, t_obj *obj, t_mrt *mrt)
{
	get_inter(inter, obj, mrt);
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