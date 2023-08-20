/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:52:11 by mporras-          #+#    #+#             */
/*   Updated: 2023/08/05 16:52:12 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

static inline t_v3d	pix_to_win(int x, int y, t_mrt *mrt)
{
	t_v3d	p;

	p.x = ((2 * ((float)x / mrt->scn.w_x)) - 1)
		  * mrt->scn.ratio * mrt->cmr->fov;
	p.y = (1 - (2 * ((float )y / mrt->scn.w_y))) * mrt->cmr->fov;
	p.x = -p.x;
	p.z = mrt->cmr->position.z;
	return (p);
}

int	mouse_handler(int mouse_code, int x, int y, t_mrt *mrt)
{
	(void )mouse_code;
	mlx_mouse_get_pos(mrt->mlx_win, &x, &y);
	if (x < 0 || y < 0)
		return (FALSE);
	if (mrt->behaviour != 33 && mrt->behaviour != 53)
		return (FALSE);
	printf("HERE WE ARE\n");
	if (mrt->behaviour == 53)
		mrt->cmr->position = pix_to_win(x, y, mrt);
	if (mrt->behaviour == 33)
		mrt->cmr->position.z = y;
	mrt->cmr->dir = ft_normal_v3d(
			ft_minus_v3d(mrt->cmr->close_obj->position, mrt->cmr->position));
	mrt->to_img = TO_RENDER;
	return (TRUE);
}
