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

# define NO_SHADOW -1

static inline t_bool lighted(t_v3d dir, t_inter inter, t_mrt *mrt)
{
	t_inter		new_inter;

	new_inter.ray.from = inter.hit;
	new_inter.ray.to = dir;
	get_hits(&new_inter, mrt->obj, mrt);
	if (!new_inter.obj)
		return (TRUE);
	if (new_inter.dist > EPSILON && new_inter.dist < 1)
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

static inline double	is_lighted(t_inter inter, t_v3d dir, t_mrt *mrt)
{
//	double	dist;
	return (lighted(dir, inter, mrt) && ft_dot_v3d(inter.normal, dir) > 0);
//	dist = lighted(dir, inter, mrt);
//	if (dist > 0.0 && ft_dot_v3d(inter.normal, dir) > 0)
//		return (1.0 / (1.0 + 0.1 * dist + 0.01 * dist * dist));
//	return (0.0);
}

#ifdef BONUS

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

#else

t_rgb	light_hit(t_ray ray, t_inter inter, t_mrt *mrt)
{
	t_light			*node;
	double			light;
	double			rgb[3];
	t_v3d			dir;
//	double			shadow;

	light = 0.0;
	(void)ray;
	ft_memset(rgb, 0, 3 * sizeof(double));
	brightness(&rgb, mrt->scn.bright, mrt->scn.amb_rgb);
	node = mrt->scn.light;
	dir = ft_minus_v3d(node->origin, inter.hit);
//		shadow = is_lighted(inter, dir, mrt);
	if (is_lighted(inter, dir, mrt))
	{
		light = node->bright * ft_cos_v3d(inter.normal, dir);
		brightness(&rgb, light, node->color);
	}
	return (ft_rgb_light(inter.color, rgb));
}

#endif