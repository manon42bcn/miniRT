/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:33:52 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/26 00:25:14 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Calculate RGB values for the first pixel in the rendering scene.
 *
 * This function determines the color of a pixel that is in the first column
 * of the rendered scene. It takes into consideration the RGB values of adjacent
 * pixels and utilizes ray tracing to compute the final color.
 *
 * @param edges Pointer to an array representing the edges' RGB values.
 * @param sides Array of RGB values representing the sides of the pixel.
 * @param pix Structure containing information about the current pixel.
 * @param mrt Pointer to the main rendering structure containing scene and
 * camera details.
 * @return Pointer to an array of RGB values representing the pixel's color.
 */
static inline t_rgb	*first_pixel(int *edges, int sides[2],
						t_pix pix, t_mrt *mrt)
{
	int		*color;

	color = (int *)ft_sec_calloc(sizeof(int) * 4);
	if (mrt->y == mrt->scn.w_y)
	{
		color[0] = calc_ray(0, pix, mrt);
		color[1] = calc_ray(2, pix, mrt);
		color[2] = calc_ray(6, pix, mrt);
		color[3] = calc_ray(8, pix, mrt);
		sides[0] = color[3];
		sides[1] = color[1];
		edges[0] = color[2];
	}
	else
	{
		color[0] = edges[0];
		color[1] = edges[1];
		color[2] = calc_ray(6, pix, mrt);
		color[3] = calc_ray(8, pix, mrt);
		sides[0] = color[3];
		edges[0] = color[2];
	}
	return (color);
}

/**
 * @brief Calculate RGB values for a pixel located on the sides of the
 * rendering scene.
 *
 * This function determines the color of a pixel that's located on either
 * the left or right boundaries of the rendered scene.
 * It computes the pixel's color by considering the RGB values of its
 * adjacent pixels and performing ray tracing for certain color
 * components.
 *
 * @param edges Pointer to an array representing the edges' RGB values.
 * @param sides Array of RGB values representing the sides of the pixel.
 * @param pix Structure containing information about the current pixel.
 * @param mrt Pointer to the main rendering structure containing scene
 * and camera details.
 * @return Pointer to an array of RGB values representing the pixel's color.
 */
static inline t_rgb	*sides_pixel(int *edges, int sides[2],
														t_pix pix, t_mrt *mrt)
{
	int		*color;

	color = (int *)ft_sec_calloc(sizeof(int) * 4);
	if (mrt->y == mrt->scn.w_y)
	{
		color[0] = sides[1];
		color[1] = calc_ray(2, pix, mrt);
		color[2] = sides[0];
		color[3] = calc_ray(8, pix, mrt);
		edges[mrt->x] = color[2];
		edges[mrt->x + 1] = color[3];
	}
	else
	{
		color[0] = edges[mrt->x];
		color[1] = edges[mrt->x + 1];
		color[2] = sides[0];
		color[3] = calc_ray(3, pix, mrt);
		edges[mrt->x] = color[2];
		edges[mrt->x + 1] = color[3];
	}
	return (color);
}

/**
 * @brief Calculate RGB values for a pixel located within the central
 * region of the rendering scene.
 *
 * This function determines the color of a pixel that's not located on the
 * boundaries of the rendered scene. The color computation for such a pixel
 * relies on the RGB values of its surrounding pixels as well as the result
 * of a ray tracing operation. The function considers pixels that are within
 * the main portion of the scene, excluding the outermost boundaries.
 *
 * @param edges Pointer to an array representing the edges' RGB values.
 * @param sides Array of RGB values representing the sides of the pixel.
 * @param pix Structure containing information about the current pixel.
 * @param mrt Pointer to the main rendering structure containing scene and
 * camera details.
 * @return Pointer to an array of RGB values representing the pixel's color.
 */
static inline t_rgb	*centre_pixel(int *edges, int sides[2],
														t_pix pix, t_mrt *mrt)
{
	int		*color;

	color = (int *)ft_sec_calloc(sizeof(int) * 4);
	if (mrt->y == mrt->scn.w_y)
	{
		color[0] = sides[1];
		color[1] = calc_ray(2, pix, mrt);
		color[2] = sides[0];
		color[3] = calc_ray(8, pix, mrt);
		sides[0] = color[3];
		sides[1] = color[1];
		edges[mrt->x] = color[2];
	}
	else
	{
		color[0] = edges[mrt->x];
		color[1] = edges[mrt->x + 1];
		color[2] = sides[0];
		color[3] = calc_ray(4, pix, mrt);
		sides[0] = color[3];
		edges[mrt->x] = color[2];
	}
	return (color);
}

/**
 * @brief Sample a pixel's color based on its position in the scene.
 *
 * Depending on the pixel's x-coordinate, this function determines its color by
 * invoking an appropriate method to handle edge pixels (first or last column)
 * or center pixels.
 *
 * @param edges Pointer to an array representing the edges' RGB values.
 * @param sides Array of RGB values representing the sides.
 * @param pix Structure containing information about the current pixel.
 * @param mrt Pointer to the main rendering structure containing scene and
 * camera details.
 * @return Pointer to an array of RGB values representing the sampled
 * pixel color.
 */
int	*sample_pixel(int *edges, int sides[2], t_pix pix, t_mrt *mrt)
{
	int		*color;

	if (mrt->x == 0)
		color = first_pixel(edges, sides, pix, mrt);
	else if (mrt->x == mrt->scn.w_x - 1)
		color = sides_pixel(edges, sides, pix, mrt);
	else
		color = centre_pixel(edges, sides, pix, mrt);
	return (color);
}
