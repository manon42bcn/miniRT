/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:43:11 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/26 01:55:35 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Checks if a point in the scene is illuminated or in shadow.
 *
 * This function determines whether a point in the scene is illuminated or in
 * shadow by checking if any other objects in the scene block the light between
 * the point and the light source.
 *
 * @param dir The direction of the light source.
 * @param inter The information about the intersection (e.g., the hit surface).
 * @param mrt The main ray tracing data structure.
 * @return TRUE if the point is illuminated, FALSE if it's in shadow.
 */
static inline t_bool	on_shadow(t_v3d dir, t_inter inter, t_mrt *mrt)
{
	t_inter		new_inter;
	double		discriminant;

	new_inter.ray.from = inter.hit;
	new_inter.ray.to = dir;
	get_hits(&new_inter, mrt->obj, mrt);
	if (!new_inter.obj)
		return (FALSE);
	discriminant = (dir.x * dir.x)
				   + (dir.y * dir.y)
				   + (dir.z * dir.z)
				   - 2 * ((dir.x * inter.hit.x)
						  + (dir.y * inter.hit.y)
						  + (dir.z * inter.hit.z));
	if (discriminant < EPSILON)
		return (FALSE);
	if (new_inter.dist > EPSILON && new_inter.dist < 1)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Adjusts the brightness of a color.
 *
 * This function adjusts the brightness of a color based on a coefficient
 * and a color value.
 *
 * @param rgb The RGB color array to modify.
 * @param coef The brightness coefficient.
 * @param color The color value.
 */
static inline void	brightness(double *rgb, double coef, int color)
{
	unsigned int	mask;

	mask = 255 << 16;
	rgb[0] += coef * ((color & mask) >> 16) / 255;
	mask >>= 8;
	rgb[1] += coef * ((color & mask) >> 8) / 255;
	mask >>= 8;
	rgb[2] += coef * (color & mask) / 255;
}

/**
 * @brief Checks if a point is illuminated by a light source.
 *
 * This function calculates how a light source affects a point in the scene.
 * It checks if the point is illuminated and, if so, computes the amount of light
 * it receives.
 *
 * @param inter The information about the intersection (e.g., the hit surface).
 * @param mrt The main ray tracing data structure.
 * @param node The light source.
 * @param rgb The RGB color array to accumulate lighting effects.
 */
static inline void	is_lighted(t_inter inter, t_mrt *mrt,
							t_light node, double *rgb)
{
	t_bool	shadowed;
	t_v3d	dir;
	double	light;

	dir = ft_normal_v3d(ft_minus_v3d(node.origin, inter.hit));
	shadowed = on_shadow(dir, inter, mrt);
	if (!shadowed)
	{
		if (ft_dot_v3d(inter.normal, dir) <= 0)
			return ;
		light = node.bright * ft_cos_v3d(inter.normal, dir);
		brightness(rgb, light, node.color);
	}
}

#ifdef BONUS

/**
 * @brief Calculate the lighting at an intersection point. -BONUS-
 *
 * This function calculates the lighting at an intersection point, taking
 * into account ambient light, direct lighting, and specular reflections.
 * It iterates through the light sources in the scene to compute the
 * overall color.
 *
 * @param ray The ray being traced.
 * @param inter The information about the intersection.
 * @param mrt The main ray tracing data structure.
 * @return The RGB color at the intersection point.
 */
t_rgb	light_hit(t_ray ray, t_inter inter, t_mrt *mrt)
{
	t_light			*node;
	double			light;
	double			rgb[3];

	light = 0.0;
	ft_memset(rgb, 0, 3 * sizeof(double));
	brightness(&rgb[0], mrt->scn.bright, mrt->scn.amb_rgb);
	node = mrt->scn.light;
	while (node)
	{
		is_lighted(inter, mrt, *node, &rgb[0]);
		if (inter.specular)
		{
			light = specular_transform(ray, inter, node);
			brightness(&rgb[0], light, node->color);
		}
		node = node->next;
	}
	return (ft_rgb_light(inter.color, rgb));
}

#else

/**
 * @brief Calculate the lighting at an intersection point -MANDATORY-
 *
 * This function calculates the lighting at an intersection point,
 * taking into account ambient light and direct lighting.
 * It considers only one light source in the scene.
 *
 * @param ray The ray being traced.
 * @param inter The information about the intersection.
 * @param mrt The main ray tracing data structure.
 * @return The RGB color at the intersection point.
 */
t_rgb	light_hit(t_ray ray, t_inter inter, t_mrt *mrt)
{
	double			rgb[3];

	(void)ray;
	ft_memset(rgb, 0, 3 * sizeof(double));
	brightness(&rgb[0], mrt->scn.bright, mrt->scn.amb_rgb);
	is_lighted(inter, mrt, *mrt->scn.light, &rgb[0]);
	return (ft_rgb_light(inter.color, rgb));
}

#endif