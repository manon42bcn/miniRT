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

/**
 * @brief   Cleans up and frees the memory of objects stored in the Ray Tracer.
 *
 * @param   mrt  Pointer to the main Ray Tracer structure.
 */
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

/**
 * @brief   Cleans up and frees the memory of lights stored in the Ray Tracer.
 *
 * @param   mrt  Pointer to the main Ray Tracer structure.
 */
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

/**
 * @brief   Cleans up and frees the memory of cameras stored in the Ray Tracer.
 * Additionally, it releases the image pointers if provided with
 * an image function.
 *
 * @param   mrt  Pointer to the main Ray Tracer structure.
 * @param   img  Function pointer to the image releasing function
 * from mlx library.
 * If NULL, image releasing is skipped.
 */
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

/**
 * @brief   Comprehensive cleanup function that releases memory and resources
 * associated with objects, lights, cameras, and other Ray Tracer components.
 *
 * @param   mrt     Pointer to the main Ray Tracer structure.
 * @param   status  Exit status.
 * @param   win     Function pointer to the window releasing function.
 * from mlx library. If NULL, window releasing is skipped.
 * @param   img     Function pointer to the image releasing function
 * from mlx library. If NULL, image releasing is skipped.
 * @return  Exits the program with the provided status.
 */
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
