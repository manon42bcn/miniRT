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
 * @brief Calculate the color for the first pixel in a row.
 *
 * This function specifically determines the color for the first pixel in a row
 * by computing the ray color from multiple points around the pixel and
 * returning an array of colors.
 *
 * @param edges Array representing color values of edges.
 * @param sides Array representing color values of the sides.
 * @param pix The pixel coordinates.
 * @param dta A pointer to a data structure containing context-specific
 * information.
 * @return t_rgb* Returns a pointer to an array of RGB values representing the
 * colors for the first pixel.
 */
static inline t_rgb	*first_pixel(int *edges, int sides[2],
						t_pix pix, t_info *dta)
{
	int		*color;

	color = (int *)ft_sec_calloc(sizeof(int) * 4);
	if (dta->y == dta->end_y)
	{
		color[0] = calc_ray(0, pix, dta->mrt);
		color[1] = calc_ray(2, pix, dta->mrt);
		color[2] = calc_ray(6, pix, dta->mrt);
		color[3] = calc_ray(8, pix, dta->mrt);
		sides[0] = color[3];
		sides[1] = color[1];
		edges[0] = color[2];
	}
	else
	{
		color[0] = edges[0];
		color[1] = edges[1];
		color[2] = calc_ray(6, pix, dta->mrt);
		color[3] = calc_ray(8, pix, dta->mrt);
		sides[0] = color[3];
		edges[0] = color[2];
	}
	return (color);
}

/**
 * @brief Calculate the color for the side pixels.
 *
 * This function computes the color for the side pixels by taking the
 * current state of the pixel and the scene context into consideration.
 *
 * @param edges Array representing color values of edges.
 * @param sides Array representing color values of the sides.
 * @param pix The pixel coordinates.
 * @param dta A pointer to a data structure containing context-specific
 * information.
 * @return t_rgb* Returns a pointer to an array of RGB values representing
 * the colors for the side pixels.
 */
static inline t_rgb	*sides_pixel(int *edges, int sides[2],
														t_pix pix, t_info *dta)
{
	int		*color;

	color = (int *)ft_sec_calloc(sizeof(int) * 4);
	if (dta->y == dta->end_y)
	{
		color[0] = sides[1];
		color[1] = calc_ray(2, pix, dta->mrt);
		color[2] = sides[0];
		color[3] = calc_ray(8, pix, dta->mrt);
		edges[dta->x] = color[2];
		edges[dta->x + 1] = color[3];
	}
	else
	{
		color[0] = edges[dta->x];
		color[1] = edges[dta->x + 1];
		color[2] = sides[0];
		color[3] = calc_ray(3, pix, dta->mrt);
		edges[dta->x] = color[2];
		edges[dta->x + 1] = color[3];
	}
	return (color);
}

/**
 * @brief Calculate the color for the central pixels.
 *
 * This function computes the color for the pixels that are not on the
 * edges or sides by using the ray tracing method and considering the
 * surrounding pixel colors.
 *
 * @param edges Array representing color values of edges.
 * @param sides Array representing color values of the sides.
 * @param pix The pixel coordinates.
 * @param dta A pointer to a data structure containing context-specific
 * information.
 * @return t_rgb* Returns a pointer to an array of RGB values representing
 * the colors for the central pixels.
 */
static inline t_rgb	*centre_pixel(int *edges, int sides[2],
														t_pix pix, t_info *dta)
{
	int		*color;

	color = (int *)ft_sec_calloc(sizeof(int) * 4);
	if (dta->y == dta->end_y)
	{
		color[0] = sides[1];
		color[1] = calc_ray(2, pix, dta->mrt);
		color[2] = sides[0];
		color[3] = calc_ray(8, pix, dta->mrt);
		sides[0] = color[3];
		sides[1] = color[1];
		edges[dta->x] = color[2];
	}
	else
	{
		color[0] = edges[dta->x];
		color[1] = edges[dta->x + 1];
		color[2] = sides[0];
		color[3] = calc_ray(4, pix, dta->mrt);
		sides[0] = color[3];
		edges[dta->x] = color[2];
	}
	return (color);
}

/**
 * @brief Sample the color of a pixel.
 *
 * Based on the position of the pixel (whether it's a first pixel,
 * side pixel, or a central pixel),
 * the appropriate color sampling function is chosen to compute the color.
 *
 * @param edges Array representing color values of edges.
 * @param sides Array representing color values of the sides.
 * @param pix The pixel coordinates.
 * @param dta A pointer to a data structure containing context-specific
 * information.
 * @return int* Returns a pointer to an array of RGB values representing
 * the colors for the sampled pixel.
 */
int	*sample_pixel(int *edges, int sides[2], t_pix pix, t_info *dta)
{
	int		*color;

	if (dta->x == 0)
		color = first_pixel(edges, sides, pix, dta);
	else if (dta->x == dta->mrt->scn.w_x - 1)
		color = sides_pixel(edges, sides, pix, dta);
	else
		color = centre_pixel(edges, sides, pix, dta);
	return (color);
}
