/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:24:36 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/20 22:19:19 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void ft_safe_free(void *ptr)
{
	if (!ptr)
		return ;
	free(ptr);
	ptr = NULL;
}

static inline void    clean_objects(t_mrt *mrt)
{
	t_obj   *node;

	node = mrt->obj;
	while (node)
	{
		node = node->next;
		mrt->obj = NULL;
		ft_safe_free(mrt->obj);
		mrt->obj = node;
	}
}

static inline void    clean_lights(t_mrt *mrt)
{
	t_light   *node;

	node = mrt->light;
	while (node)
	{
		node = node->next;
		mrt->light = NULL;
		ft_safe_free(mrt->light);
		mrt->light = node;
	}
}

static inline void    clean_cameras(t_mrt *mrt)
{
	t_cmr   *node;

	node = mrt->cmr;
	while (node)
	{
		node = node->next;
		mlx_destroy_image(mrt->mlx, mrt->cmr->img_ptr);
//		ft_safe_free(mrt->cmr->addr);
		mrt->cmr->img_ptr = NULL;
		ft_safe_free(mrt->cmr);
		mrt->cmr = node;
	}
	mrt->main_cam = NULL;
}

int    clear_all(t_mrt *mrt, int status)
{
	clean_objects(mrt);
	clean_lights(mrt);
	clean_cameras(mrt);
	ft_clear_tabs(mrt->tab);
	ft_safe_free(mrt->aux);
	mlx_destroy_window(mrt->mlx, mrt->mlx_win);
	exit(status);
}