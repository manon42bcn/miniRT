/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:40:43 by mporras-          #+#    #+#             */
/*   Updated: 2023/10/30 10:40:45 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#ifdef BONUS

t_v3d	reflect_ray(t_v3d ray, t_v3d normal)
{
	return (ft_minus_v3d(ft_scalar_v3d(2
				* ft_dot_v3d(normal, ray), normal), ray));
}

double	specular_transform(t_ray ray, t_inter inter, t_light *scn_light)
{
	double	light;
	t_v3d	direction;
	t_v3d	p_to_cam;
	t_v3d	reflected;

	direction = ft_minus_v3d(scn_light->origin, inter.hit);
	p_to_cam = ft_minus_v3d(ray.from, inter.hit);
	reflected = reflect_ray(direction, inter.normal);
	if (ft_dot_v3d(reflected, p_to_cam) > 0)
		light = scn_light->bright
			* pow(ft_cos_v3d(reflected, p_to_cam), inter.specular);
	else
		light = 0;
	return (light);
}

#endif