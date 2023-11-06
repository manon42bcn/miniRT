/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 22:28:44 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/06 23:13:26 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Initializes the MiniLibX library and prepares the images for each
 * camera.
 *
 * Initializes the MiniLibX library and creates an image for each camera in
 * the scene. Each camera's image pointer, address, bytes per pixel, size,
 * and endianness are stored within the camera's structure.
 *
 * @param mrt A pointer to the general properties of the scene.
 */
void	mlx_starter(t_mrt *mrt)
{
	t_cmr	*node;

	node = mrt->cmr;
	mrt->mlx = mlx_init();
	if (mrt->mlx == NULL)
		msg_error_exit("mlx init error");
	while (node)
	{
		node->img_ptr = mlx_new_image(mrt->mlx, mrt->scn.w_x, mrt->scn.w_y);
		node->addr = (int *)mlx_get_data_addr(node->img_ptr,
				&node->bpp, &node->size, &node->endian);
		node = node->next;
	}
}

/**
 * @brief Allocates memory for an array of RGB values to represent edges.
 *
 * Uses secure memory allocation to prevent unexpected behaviors.
 * This function serves as a utility for preparing edge data structures
 * in the rendering process.
 *
 * @param size Number of RGB values required (often corresponds to
 * screen width + 2).
 * @return Pointer to the newly allocated array of RGB values.
 */
t_rgb	*create_edges_new(int size)
{
	t_rgb	*rst;

	rst = (t_rgb *)ft_sec_calloc(sizeof(t_rgb) * size);
	return (rst);
}

/**
 * @brief Renders and displays the scene to the window.
 *
 * If the scene is set to be rendered, it will call the rendering function.
 * After rendering or if already rendered, it will then display the image
 * corresponding to the current camera to the window.
 *
 * @param mrt A pointer to the general properties of the scene.
 * @return Always returns TRUE. Used for hook functions in MiniLibX.
 */
int	to_win(t_mrt *mrt)
{
	if (mrt->to_img == TO_RENDER)
	{
		if (mrt->window == TRUE)
			render_main(mrt);
		mlx_put_image_to_window(mrt->mlx, mrt->mlx_win,
			mrt->cmr->img_ptr, 0, 0);
		mrt->to_img = RENDERED;
		mrt->window = TRUE;
	}
	return (TRUE);
}
