/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 14:24:09 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/22 00:43:22 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_rgb texture_checkboard(t_inter *inter)
{
	t_rgb	black;
	t_rgb	white;
	t_v3d	coords;
	t_v3d	val;
	int		mix;

	black = 0x000000;
	white = 0xffffff;
	coords.x = abs((int)floor(inter->hit.x));
	coords.y = abs((int)floor(inter->hit.y));
	coords.z = abs((int)floor(inter->hit.z));
	val.x = (int)coords.x % 2;
	val.y = (int)coords.y % 2;
	val.z = (int)coords.z % 2;
	mix = ((int)val.x ^ (int)val.y) ^ (int)val.z;
	if (mix)
		return (black);
	return (white);
}

static inline t_v3d	texture_waves(t_inter *inter, t_obj *lst)
{
	double	wl_value;
	double	wl_factor;

	wl_factor = lst->wavelength;
	wl_value = sin(inter->hit.z * wl_factor) + sin(inter->hit.y * wl_factor);
	return (ft_rotate_v3d(inter->normal, wl_value));
}

static inline void  fill_rgb(double r, double g, double b, double color[3])
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

static inline t_rgb   texture_rainbow(t_inter *inter)
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

void		texturize(int texture, t_inter *inter, t_obj *obj)
{
	if (texture == CHECKBOARD)
		inter->color = texture_checkboard(inter);
	else if (texture == WAVES)
		inter->normal = texture_waves(inter, obj);
	else if (texture == RAINBOW)
		inter->color = texture_rainbow(inter);
}
