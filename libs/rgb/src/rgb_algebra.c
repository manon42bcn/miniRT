/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_algebra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 21:48:08 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/07 23:00:20 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rgb.h"

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
	return ((rst[0] << 16) | (rst[1] << 8) | rst[2]);
}

// free rgb?