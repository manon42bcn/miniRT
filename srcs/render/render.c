/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:41:01 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/25 23:56:35 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static inline t_rgb	calc_pixel_color(int *edges, t_rgb sides[2], t_mrt *mrt)
{
	t_pix	pix;
	int		*color;

	pix.limit = 3;
	pix.w_x = mrt->scn.w_x;
	pix.w_y = mrt->scn.w_y;
	pix.x = mrt->x;
	pix.y = mrt->y;
	color = sample_pixel(edges, sides, pix, mrt);
	if (ft_rgb_diff(color[0], color[3])
		|| ft_rgb_diff(color[1], color[2]))
		return (supersample(color, pix, mrt));
	return (ft_rgb_balance(color));
}

static inline t_rgb	*create_edges_new(int size)
{
	t_rgb	*rst;

	rst = (t_rgb *)ft_sec_calloc(sizeof(t_rgb) * size);
	return (rst);
}


static inline void	render_scene(t_mrt *mrt)
{
	t_rgb	*edges;
	t_rgb	sides[3];
	t_rgb	color;

	edges = create_edges_new(mrt->scn.w_x + 2);
	mrt->y = 0;
	while (mrt->y < mrt->scn.w_y)
	{
		mrt->x = 0;
		while (mrt->x < mrt->scn.w_x)
		{
			color = calc_pixel_color(edges, sides, mrt);
			mrt->cmr->addr[mrt->y * mrt->scn.w_x + mrt->x] = color;
			mrt->x++;
		}
		mrt->y++;
	}
	ft_sec_free(edges);
}

void	render_main(t_mrt *mrt)
{
	while (mrt->cmr)
	{
		render_scene(mrt);
		mrt->cmr = mrt->cmr->next;
	}
	mrt->cmr = mrt->main_cam;
}
