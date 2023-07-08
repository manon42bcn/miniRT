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

int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

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
		render_main(mrt);
		mlx_put_image_to_window(mrt->mlx, mrt->mlx_win, mrt->cmr->img_ptr, 0, 0);
		mrt->to_img = TRUE;
	}
	return (TRUE);
}

int	window_handler(t_mrt *mrt)
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

void	sphere_diam(t_mrt *mrt, int key)
{
	t_obj	*node;

	node = mrt->obj;
	if (key == K_D)
	{
		while (node)
		{
			if (node->type == SPHERE)
				node->elm.sph.radius *= 1.1f;
			node = node->next;
		}
	}
	else
	{
		while (node)
		{
			if (node->type == SPHERE)
				if (node->elm.sph.radius / 1.1f > 0)
					node->elm.sph.radius /= 1.1f;
			node = node->next;
		}
	}
}

int	keys_handler(int key, t_mrt *mrt)
{
	printf("%d - key\n", key);
	if (key == K_ESC)
		exit(clear_all(mrt, 0));
	if (key == K_D || key == K_E)
		sphere_diam(mrt, key);
	else if (key == K_SPACE)
		change_camera(mrt);
	mrt->to_img = FALSE;
	return (to_win(mrt));
}
