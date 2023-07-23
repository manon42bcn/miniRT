/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:09:15 by mporras-          #+#    #+#             */
/*   Updated: 2023/07/23 22:09:19 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	ft_safe_free(void *ptr)
{
	if (!ptr)
		return ;
	free(ptr);
	ptr = NULL;
}

static inline void	clean_objects(t_mrt *mrt)
{
	t_obj	*node;

	while (mrt->obj)
	{
		node = mrt->obj->next;
		mrt->obj->next = NULL;
		ft_sec_free(mrt->obj);
		mrt->obj = node;
	}
}

static inline void	clean_lights(t_mrt *mrt)
{
	t_light	*node;

	while (mrt->scn.light)
	{
		node = mrt->scn.light->next;
		mrt->scn.light->next = NULL;
		ft_sec_free(mrt->scn.light);
		mrt->scn.light = node;
	}
}

static inline void	clean_cameras(t_mrt *mrt, int (*img)(void *, void *))
{
	t_cmr	*node;

	while (mrt->cmr)
	{
		node = mrt->cmr->next;
		if (img)
			img(mrt->mlx, mrt->cmr->img_ptr);
		mrt->cmr->img_ptr = NULL;
		mrt->cmr->next = NULL;
		ft_sec_free(mrt->cmr);
		mrt->cmr = node;
	}
	mrt->main_cam = NULL;
}

int	clear_all(t_mrt *mrt, int status, int (*win)(void *, void *),
			int (*img)(void *, void *))
{
	clean_objects(mrt);
	clean_lights(mrt);
	clean_cameras(mrt, img);
	ft_clear_tabs(mrt->tab);
	ft_sec_free(mrt->aux);
	if (win)
		win(mrt->mlx, mrt->mlx_win);
	if (mrt->fd)
		close(mrt->fd);
	ft_sec_free(mrt);
	exit(status);
}
