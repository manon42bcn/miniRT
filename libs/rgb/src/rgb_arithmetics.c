/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_arithmetics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:39:11 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/15 01:57:11 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rgb.h"

/**
 * @brief Multiply the components of an RGB color by a scalar.
 *
 * This function multiplies each component (R, G, B) of the given RGB color
 * by a scalar value, alpha.
 *
 * @param color RGB color to be multiplied.
 * @param alpha Scalar value.
 * @return t_rgb The resulting scaled RGB color.
 */
t_rgb	ft_rgb_dot(t_rgb color, t_dec alpha)
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

/**
 * @brief Add two RGB colors.
 *
 * This function adds the RGB components of two colors together.
 *
 * @param ca First RGB color.
 * @param cb Second RGB color.
 * @return t_rgb The resulting RGB color after addition.
 */
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

/**
 * @brief Adjust an RGB color based on a lighting array.
 *
 * This function multiplies the components of an RGB color by the values in
 * a lighting array.
 *
 * @param color RGB color to be adjusted.
 * @param rgb Lighting array with adjustments for each RGB component.
 * @return t_rgb The resulting adjusted RGB color.
 */
t_rgb	ft_rgb_light(t_rgb color, t_dec rgb[3])
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

/**
 * @brief Calculate the difference between two RGB colors.
 *
 * This function calculates the difference between the components of two
 * RGB colors. If the sum of squared differences exceeds a threshold,
 * the function returns true.
 *
 * @param ca First RGB color.
 * @param cb Second RGB color.
 * @return t_rgb TRUE if difference exceeds threshold, otherwise FALSE.
 */
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

/**
 * @brief Inverts the RGB color values of a given color.
 *
 * This function takes an original color in the format of an unsigned integer,
 * representing RGB channels, and returns its inverted color.
 *
 * @param original The RGB color to be inverted, stored as an unsigned integer.
 *
 * @return t_rgb The inverted RGB color as an unsigned integer.
 */
t_rgb	ft_invert_color(t_rgb original)
{
	unsigned char	rgb[3];

	rgb[R_I] = (original >> 16) & 0xFF;
	rgb[G_I] = (original >> 8) & 0xFF;
	rgb[B_I] = original & 0xFF;
	rgb[R_I] = RGB_MASK - rgb[R_I];
	rgb[G_I] = RGB_MASK - rgb[G_I];
	rgb[B_I] = RGB_MASK - rgb[B_I];
	return ((rgb[R_I] << 16) | (rgb[G_I] << 8) | rgb[B_I]);
}
