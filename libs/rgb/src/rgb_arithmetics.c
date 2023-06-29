/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_arithmetics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:39:11 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/07 22:58:33 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rgb.h"

t_rgb	ft_rgb_dot(t_rgb color, double alpha)
{
	t_rgb	r;
	t_rgb	g;
	t_rgb	b;

	r = alpha * ((color & (RGB_MASK << 16)) >> 16);
	g = alpha * ((color & (RGB_MASK << 8)) >> 8);
	b = alpha * (color & RGB_MASK);
	if (r > RGB_MASK)
		r = RGB_MASK;
	if (g > RGB_MASK)
		g = RGB_MASK;
	if (b > RGB_MASK)
		b = RGB_MASK;
	return ((r << 16) | (g << 8) | b);
}

t_rgb	ft_rgb_add(t_rgb ca, t_rgb cb)
{
	t_rgb	r;
	t_rgb	g;
	t_rgb	b;

	r = ((ca & (RGB_MASK << 16)) + (cb & (RGB_MASK << 16))) & (RGB_MASK << 16);
	g = ((ca & (RGB_MASK << 8)) + (cb & (RGB_MASK << 8))) & (RGB_MASK << 8);
	b = ((ca & RGB_MASK) + (cb & RGB_MASK)) & RGB_MASK;
	return (r | g | b);
}

t_rgb	ft_rgb_light(t_rgb color, double rgb[3])
{	
	int				mask;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	mask = RGB_MASK << 16;
	r = rgb[0] * ((color & mask) >> 16);
	mask >>= 8;
	g = rgb[1] * ((color & mask) >> 8);
	mask >>= 8;
	b = rgb[2] * (color & mask);
	if (r > RGB_MASK)
		r = RGB_MASK;
	if (g > RGB_MASK)
		g = RGB_MASK;
	if (b > RGB_MASK)
		b = RGB_MASK;
	return ((r << 16) | (g << 8) | b);
}

t_rgb	ft_rgb_diff(t_rgb ca, t_rgb cb)
{
	t_rgb	r[2];
	t_rgb	g[2];
	t_rgb	b[2];
	t_rgb	test;

	r[0] = (ca & (RGB_MASK << 16)) >> 16;
	g[0] = (ca & (RGB_MASK << 8)) >> 8;
	b[0] = ca & RGB_MASK;
	r[1] = (cb & (RGB_MASK << 16)) >> 16;
	g[1] = (cb & (RGB_MASK << 8)) >> 8;
	b[1] = cb & RGB_MASK;
	test = ((r[1] - r[0]) * (r[1] - r[0]))
		+ ((r[1] - r[0]) * (r[1] - r[0]))
		+ ((r[1] - r[0]) * (r[1] - r[0]));
	return (test > 1000);
}
