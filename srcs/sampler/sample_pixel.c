/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:33:52 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/26 00:25:14 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_rgb	*first_pixel(int *edges, int sides[2],
						t_pix pix, t_mrt *mrt)
{
	int		*color;

	color = (int *)ft_sec_calloc(sizeof(int) * 4);
	if (mrt->y == mrt->scn.w_y)
	{
		color[0] = calc_ray(0, pix, mrt);
		color[1] = calc_ray(2, pix, mrt);
		color[2] = calc_ray(6, pix, mrt);
		color[3] = calc_ray(8, pix, mrt);
		sides[0] = color[3];
		sides[1] = color[1];
		edges[0] = color[2];
	}
	else
	{
		color[0] = edges[0];
		color[1] = edges[1];
		color[2] = calc_ray(6, pix, mrt);
		color[3] = calc_ray(8, pix, mrt);
		sides[0] = color[3];
		edges[0] = color[2];
	}
	return (color);
}

static inline t_rgb	*sides_pixel(int *edges, int sides[2],
														t_pix pix, t_mrt *mrt)
{
	int		*color;

	color = (int *)ft_sec_calloc(sizeof(int) * 4);
	if (mrt->y == mrt->scn.w_y)
	{
		color[0] = sides[1];
		color[1] = calc_ray(2, pix, mrt);
		color[2] = sides[0];
		color[3] = calc_ray(8, pix, mrt);
		edges[mrt->x] = color[2];
		edges[mrt->x + 1] = color[3];
	}
	else
	{
		color[0] = edges[mrt->x];
		color[1] = edges[mrt->x + 1];
		color[2] = sides[0];
		color[3] = calc_ray(3, pix, mrt);
		edges[mrt->x] = color[2];
		edges[mrt->x + 1] = color[3];
	}
	return (color);
}

static inline t_rgb	*centre_pixel(int *edges, int sides[2],
														t_pix pix, t_mrt *mrt)
{
	int		*color;

	color = (int *)ft_sec_calloc(sizeof(int) * 4);
	if (mrt->y == mrt->scn.w_y)
	{
		color[0] = sides[1];
		color[1] = calc_ray(2, pix, mrt);
		color[2] = sides[0];
		color[3] = calc_ray(8, pix, mrt);
		sides[0] = color[3];
		sides[1] = color[1];
		edges[mrt->x] = color[2];
	}
	else
	{
		color[0] = edges[mrt->x];
		color[1] = edges[mrt->x + 1];
		color[2] = sides[0];
		color[3] = calc_ray(4, pix, mrt);
		sides[0] = color[3];
		edges[mrt->x] = color[2];
	}
	return (color);
}

int	*sample_pixel(int *edges, int sides[2], t_pix pix, t_mrt *mrt)
{
	int		*color;

	if (mrt->x == 0)
		color = first_pixel(edges, sides, pix, mrt);
	else if (mrt->x == mrt->scn.w_x - 1)
		color = sides_pixel(edges, sides, pix, mrt);
	else
		color = centre_pixel(edges, sides, pix, mrt);
	return (color);
}
