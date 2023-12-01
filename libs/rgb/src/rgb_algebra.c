/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_algebra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:48:08 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/09 21:55:31 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rgb.h"

/**
 * @brief Compute the average of two RGB colors.
 *
 * This function calculates the average of two given RGB colors by summing
 * each of their RGB components individually and then dividing by 2.
 *
 * @param ca First RGB color.
 * @param cb Second RGB color.
 * @return t_rgb The resulting averaged RGB color.
 */
t_rgb	ft_rgb_avg(t_rgb ca, t_rgb cb)
{
	t_rgb	rst[3];
	t_rgb	color[2];
	int		i;

	rst[0] = 0;
	rst[1] = 0;
	rst[2] = 0;
	color[0] = ca;
	color[1] = cb;
	i = 0;
	while (i < 2)
	{
		rst[0] += (color[i] & (RGB_MASK << 16)) >> 16;
		rst[1] += (color[i] & (RGB_MASK << 8)) >> 8;
		rst[2] += color[i] & RGB_MASK;
		i++;
	}
	rst[0] = rst[0] / 2;
	rst[1] = rst[1] / 2;
	rst[2] = rst[2] / 2;
	return ((rst[0] << 16) | (rst[1] << 8) | rst[2]);
}

/**
 * @brief Balance the RGB color from an array of RGB colors.
 *
 * This function computes a balanced RGB color from an array of four RGB colors.
 * It does this by summing each individual RGB component of the colors in the
 * array and then dividing by 4.
 *
 * @param rgb Pointer to an array of four RGB colors.
 * @return t_rgb The resulting balanced RGB color.
 */
t_rgb	ft_rgb_balance(t_rgb *rgb)
{
	t_rgb	rst[3];
	int		i;

	rst[0] = 0;
	rst[1] = 0;
	rst[2] = 0;
	i = 0;
	while (i < 4)
	{
		rst[0] += (rgb[i] & (RGB_MASK << 16)) >> 16;
		rst[1] += (rgb[i] & (RGB_MASK << 8)) >> 8;
		rst[2] += rgb[i] & RGB_MASK;
		i++;
	}
	rst[0] = rst[0] / 4;
	rst[1] = rst[1] / 4;
	rst[2] = rst[2] / 4;
	ft_sec_free(rgb);
	return ((rst[0] << 16) | (rst[1] << 8) | rst[2]);
}

/**
 * @brief Combine individual color components into a single RGB color value.
 *
 * This function takes an array of individual color components (Red, Green,
 * Blue) and combines them into a single 32-bit RGB color value. It performs
 * bitwise left shifts to position each color component in the appropriate bits
 * of the resulting RGB value.
 *
 * @param color An array containing the individual color components
 * (color[0] = Red, color[1] = Green, color[2] = Blue).
 * @return The combined RGB color value.
 */
t_rgb	ft_rgb_get(t_rgb color[3])
{
	color[R_I] <<= 16;
	color[G_I] <<= 8;
	return (color[R_I] | color[G_I] | color[B_I]);
}
