/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   after_parse_process.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:23:53 by mporras-          #+#    #+#             */
/*   Updated: 2023/10/26 15:23:56 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Load bump textures for all objects in the scene.
 *
 * Iterates through all objects in the scene and, for those with bump mapping
 * enabled, loads the associated bump texture.
 *
 * @param mrt Pointer to the main RT structure that contains scene and
 * rendering details.
 */
static inline void	get_bumps_textures(t_mrt *mrt)
{
	t_obj	*node;

	node = mrt->obj;
	while (node)
	{
		if (node->bump)
		{
			node->xpm.img = mlx_xpm_file_to_image(mrt->mlx,
					node->xpm.path, &node->xpm.width,
					&node->xpm.height);
			node->xpm.addr = mlx_get_data_addr(node->xpm.img,
					&node->xpm.bbp, &node->xpm.ll,
					&node->xpm.endian);
		}
		node = node->next;
	}
}

/**
 * @brief Finalizes the parsing process and initializes specific rendering
 * parameters.
 * Once the scene is parsed, this function is used to set specific screen
 * parameters and initialize the scene's camera. It also sets up the
 * necessary hooks for interactivity.
 *
 * @param mrt Pointer to the main structure containing scene, camera,
 * and other essential data.
 */
void	after_parse_process(t_mrt *mrt)
{
	t_cmr	*node;

	node = mrt->cmr;
	mrt->main_cam = node;
	if (mrt->scn.res_init == FALSE)
		my_mlx_getScreenSize(&(mrt->scn.w_x), &(mrt->scn.w_y));
	mrt->scn.w_x /= 3;
	mrt->scn.w_y /= 3;
	mrt->scn.ratio = (double)mrt->scn.w_x / (double)mrt->scn.w_y;
	while (node)
	{
		node->ratio = mrt->scn.ratio;
		node = node->next;
	}
	mrt->clean_window = &mlx_clear_window;
	mrt->clean_image = &mlx_destroy_image;
	mrt->get_solver = &get_solver;
	mrt->ray_pixel = &ray_from_pixel;
	mrt->window = FALSE;
	mlx_starter(mrt);
	get_bumps_textures(mrt);
}
