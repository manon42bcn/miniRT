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

/**
 * @brief Calculate the color value for a given pixel.
 *
 * The function determines the color of a pixel based on the scene's
 * information, edges, and sides. It uses supersampling if there's a
 * difference in adjacent pixel colors to enhance image quality.
 *
 * @param edges Pointer to an array representing the edges' RGB values.
 * @param sides Array of RGB values representing the sides.
 * @param mrt Pointer to the main rendering structure containing scene
 * and camera details.
 * @return Calculated RGB color for the pixel.
 */
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
static inline t_rgb	*create_edges_new(int size)
{
	t_rgb	*rst;

	rst = (t_rgb *)ft_sec_calloc(sizeof(t_rgb) * size);
	return (rst);
}

/**
 * @brief Renders the scene for a given camera.
 *
 * Iteratively calculates the color for each pixel in the scene using
 * the camera's perspective and fills the corresponding pixel in the
 * camera's image buffer. Utilizes edge calculation for defining scene
 * boundaries and then uses the calculated edges to derive pixel color.
 *
 * @param mrt Pointer to the main structure containing scene, camera,
 * and other essential data.
 */
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

/**
 * @brief Renders the entire scene for each camera in the scene.
 *
 * Iterates through all the cameras in the scene and calls the render
 * function for each. After rendering, it resets the active camera to the
 * main camera of the scene.
 *
 * @param mrt Pointer to the main structure containing scene, camera,
 * and other essential data.
 */
void	render_main(t_mrt *mrt)
{
	while (mrt->cmr)
	{
		render_scene(mrt);
		mrt->cmr = mrt->cmr->next;
	}
	mrt->cmr = mrt->main_cam;
}
