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

t_v3d	reflect_ray(t_v3d ray, t_v3d normal)
{
	return (ft_minus_v3d(ft_scalar_v3d(2
				* ft_dot_v3d(normal, ray), normal), ray));
}

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
}
