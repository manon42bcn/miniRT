/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:43:11 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/23 17:27:12 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_bool	lighted(t_v3d dir, t_inter inter, t_mrt *mrt)
{
	double		evl;
	double		to_light;

	to_light = ft_length_v3d(dir);
	pthread_mutex_lock(&mrt->getsolver);
	evl = get_solver(inter.hit, dir, inter.obj);
	pthread_mutex_unlock(&mrt->getsolver);
	if (evl > EPSILON && evl < to_light)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Adjusts the RGB components based on brightness coefficient.
 *
 * @param rgb Triple of RGB components to be adjusted.
 * @param coef Brightness coefficient.
 * @param color Color value to be added to rgb.
 */
static inline void	brightness(double (*rgb)[3], double coef, int color)
{
	unsigned int	mask;

	mask = 255 << 16;
	(*rgb)[0] += coef * ((color & mask) >> 16) / 255;
	mask >>= 8;
	(*rgb)[1] += coef * ((color & mask) >> 8) / 255;
	mask >>= 8;
	(*rgb)[2] += coef * (color & mask) / 255;
}

static inline double	specular_transform(t_ray ray, t_inter inter, t_light *scn_light)
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

static inline t_bool	is_lighted(t_inter inter, t_v3d dir, t_mrt *mrt)
{
	return (lighted(dir, inter, mrt)
		&& ft_dot_v3d(inter.normal, dir) > 0);
}

t_rgb	light_hit(t_ray ray, t_inter inter, t_mrt *mrt)
{
	t_light			*node;
	double			light;
	double			rgb[3];
	t_v3d			direction;

	light = 0.0;
	ft_memset(rgb, 0, 3 * sizeof(double));
	brightness(&rgb, mrt->scn.bright, mrt->scn.amb_rgb);
	node = mrt->scn.light;
	while (node)
	{
		direction = ft_minus_v3d(node->origin, inter.hit);
		if (is_lighted(inter, direction, mrt))
		{
			light = node->bright * ft_cos_v3d(inter.normal, direction);
			brightness(&rgb, light, node->color);
		}
		if (inter.specular)
		{
			light = specular_transform(ray, inter, node);
			brightness(&rgb, light, node->color);
		}
		node = node->next;
	}
	return (ft_rgb_light(inter.color, rgb));
}
