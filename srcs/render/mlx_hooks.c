/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 22:28:44 by mporras-          #+#    #+#             */
/*   Updated: 2023/07/02 22:28:46 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void mlx_starter(t_mrt *mrt)
{
	t_cmr *node;

	node = mrt->cmr;
	while (node)
	{
		node->img_ptr = mlx_new_image(mrt->mlx, mrt->scn.w_x, mrt->scn.w_y);
		node->addr = (int *)mlx_get_data_addr(node->img_ptr,
		                                      &node->bpp, &node->size, &node->endian);
		node = node->next;
	}
}

int to_win(t_mrt *mrt) {
	if (mrt->to_img == FALSE)
	{
		mlx_put_image_to_window(mrt->mlx, mrt->mlx_win, mrt->cmr->img_ptr, 0, 0);
		mrt->to_img = TRUE;
	}
	return (TRUE);
}

int window_handler(t_mrt *mrt)
{
	exit(clear_all(mrt, 0));
}

static inline void change_camera(t_mrt *mrt)
{
	if (mrt->cmr->next == NULL)
		mrt->cmr = mrt->main_cam;
	else
		mrt->cmr = mrt->cmr->next;
}

int	keys_handler(int key, t_mrt *mrt)
{
	if (key == K_ESC)
		exit(clear_all(mrt, 0));
	else if (key == K_SPACE)
		change_camera(mrt);
	mrt->to_img = FALSE;
	return (to_win(mrt));
}