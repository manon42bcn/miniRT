/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supersample.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:34:23 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/25 23:22:22 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_rgb			first_corner(t_rgb *color, int centre,
												t_pix pix, t_mrt *mrt)
{
	t_pix	mini_pix;
	int		*mini_sqr;
	int		col;

	mini_sqr = (int *)ft_sec_malloc(sizeof(int) * 4);
	mini_sqr[0] = color[0];
	mini_sqr[1] = calc_ray(1, pix, mrt);
	mini_sqr[2] = calc_ray(3, pix, mrt);
	mini_sqr[3] = centre;
	mini_pix.limit = pix.limit - 1;
	mini_pix.x = pix.x * 2 - 1;
	mini_pix.y = pix.y * 2 - 1;
	mini_pix.w_x = pix.w_x * 2;
	mini_pix.w_y = pix.w_y * 2;
	col = supersample(mini_sqr, mini_pix, mrt);
	return (col);
}

static inline t_rgb			second_corner(t_rgb *color, int centre,
												t_pix pix, t_mrt *mrt)
{
	t_pix	mini_pix;
	int		*mini_sqr;
	int		col;

	mini_sqr = (int *)ft_sec_malloc(sizeof(int) * 4);
	mini_sqr[0] = calc_ray(3, pix, mrt);
	mini_sqr[1] = color[1];
	mini_sqr[2] = centre;
	mini_sqr[3] = calc_ray(5, pix, mrt);
	mini_pix.limit = pix.limit - 1;
	mini_pix.x = pix.x * 2;
	mini_pix.y = pix.y * 2 - 1;
	mini_pix.w_x = pix.w_x * 2;
	mini_pix.w_y = pix.w_y * 2;
	col = supersample(mini_sqr, mini_pix, mrt);
	return (col);
}

static inline t_rgb			third_corner(t_rgb *color, int centre,
												t_pix pix, t_mrt *mrt)
{
	t_pix	mini_pix;
	int		*mini_sqr;
	int		col;

	mini_sqr = (int *)ft_sec_malloc(sizeof(int) * 4);
	mini_sqr[0] = calc_ray(3, pix, mrt);
	mini_sqr[1] = centre;
	mini_sqr[2] = color[2];
	mini_sqr[3] = calc_ray(7, pix, mrt);
	mini_pix.limit = pix.limit - 1;
	mini_pix.x = pix.x * 2 - 1;
	mini_pix.y = pix.y * 2;
	mini_pix.w_x = pix.w_x * 2;
	mini_pix.w_y = pix.w_y * 2;
	col = supersample(mini_sqr, mini_pix, mrt);
	return (col);
}

static inline t_rgb			fourth_corner(t_rgb *color, int centre,
												t_pix pix, t_mrt *mrt)
{
	t_pix	mini_pix;
	int		*mini_sqr;
	int		col;

	mini_sqr = (int *)ft_sec_malloc(sizeof(int) * 4);
	mini_sqr[0] = centre;
	mini_sqr[1] = calc_ray(5, pix, mrt);
	mini_sqr[2] = calc_ray(7, pix, mrt);
	mini_sqr[3] = color[3];
	mini_pix.limit = pix.limit - 1;
	mini_pix.x = pix.x * 2;
	mini_pix.y = pix.y * 2;
	mini_pix.w_x = pix.w_x * 2;
	mini_pix.w_y = pix.w_y * 2;
	col = supersample(mini_sqr, mini_pix, mrt);
	return (col);
}

t_rgb	supersample(int *color, t_pix pix, t_mrt *mrt)
{
	int		centre;
	int		corner;
	static t_rgb (*sampling[])(t_rgb *, int, t_pix, t_mrt *) =
			{first_corner, second_corner, third_corner, fourth_corner};

	centre = calc_ray(4, pix, mrt);
	corner = 0;
	while (corner < 4)
	{
		if (!ft_rgb_diff(color[corner], centre) || pix.limit == 0)
			color[corner] = ft_rgb_avg(color[corner], centre);
		else
			color[corner] = sampling[corner](color, centre, pix, mrt);
		corner++;
	}
	return (ft_rgb_balance(color));
}
