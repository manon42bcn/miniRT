/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:24:09 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/19 23:27:09 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Apply a checkboard texture to an intersection point.
 *
 * Uses the hit point's coordinates to determine whether it's on a black or
 * white square in a checkerboard pattern.
 *
 * @param inter Intersection information, containing details like hit point.
 * @return Color of the checkerboard at the intersection point.
 */
static inline t_rgb	texture_checkboard(t_inter *inter)
{
	t_rgb	black;
	t_rgb	white;
	t_v3d	coords;
	t_v3d	val;
	int		mix;

	black = 0x000000;
	white = 0xffffff;
	coords.x = abs((int)floorl(inter->hit.x));
	coords.y = abs((int)floorl(inter->hit.y));
	coords.z = abs((int)floorl(inter->hit.z));
	val.x = (int)coords.x % 2;
	val.y = (int)coords.y % 2;
	val.z = (int)coords.z % 2;
	mix = ((int)val.x ^ (int)val.y) ^ (int)val.z;
	if (mix)
		return (black);
	return (white);
}

/**
 * @brief Generate a wave texture based on the intersection point
 * and object's wavelength factor.
 *
 * @param inter Intersection information, containing details like hit point.
 * @param lst The object to which the texture will be applied.
 * @return A vector representing the normal perturbation due to the wave texture.
 */
static inline t_v3d	texture_waves(t_inter *inter, t_obj *lst)
{
	t_dec	wl_value;
	t_dec	wl_factor;

	wl_factor = lst->wavelength;
	wl_value = sinl(inter->hit.z * wl_factor) + sinl(inter->hit.y * wl_factor);
	return (ft_rot_v3d(inter->normal, X_C, wl_value));
}

/**
 * @brief Fill a color array with specified RGB values.
 *
 * Utility function to fill a color array with RGB values.
 *
 * @param r Red component.
 * @param g Green component.
 * @param b Blue component.
 * @param color The array to be filled with color values.
 */
static inline void	fill_rgb(double r, double g, double b, double color[3])
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

/**
 * @brief Generate a rainbow texture based on the intersection point's normal.
 *
 * Uses the y-component of the normal to determine a wavelength, then converts
 * that wavelength into an RGB color.
 *
 * @param inter Intersection information, containing details like normal.
 * @return The color of the rainbow texture at the intersection point.
 */
static inline t_rgb	texture_rainbow(t_inter *inter)
{
	double	color[3];
	double	wave_lenght;

	wave_lenght = 540 - (inter->normal.y * 160);
	if (wave_lenght >= 380 && wave_lenght < 440)
		fill_rgb(-(wave_lenght - 440.) / (440. - 380.), 0.0, 1.0, color);
	else if (wave_lenght >= 440 && wave_lenght < 490)
		fill_rgb(0.0, (wave_lenght - 440.) / (490. - 440.), 1.0, color);
	else if (wave_lenght >= 490 && wave_lenght < 510)
		fill_rgb(0.0, 1.0, -(wave_lenght - 510.) / (510. - 490.), color);
	else if (wave_lenght >= 510 && wave_lenght < 580)
		fill_rgb((wave_lenght - 510.) / (580. - 510.), 1.0, 0.0, color);
	else if (wave_lenght >= 580 && wave_lenght < 645)
		fill_rgb(1.0, -(wave_lenght - 645.) / (645. - 580.), 0.0, color);
	else if (wave_lenght >= 645 && wave_lenght <= 780)
		fill_rgb(1.0, 0.0, 0.0, color);
	else
		fill_rgb(0.0, 0.0, 0.0, color);
	color[0] *= 255;
	color[1] *= 255;
	color[2] *= 255;
	return (((t_rgb)color[0] << 16) | ((t_rgb)color[1] << 8) | (t_rgb)color[2]);
}

void	texturize(t_inter *inter)
{
	if (inter->obj->texture == CHECKBOARD)
		inter->color = texture_checkboard(inter);
	else if (inter->obj->texture == WAVES)
		inter->normal = texture_waves(inter, inter->obj);
	else if (inter->obj->texture == RAINBOW)
		inter->color = texture_rainbow(inter);
}
