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
 * @brief Calculate the color of a specific pixel.
 *
 * This function determines the color of a pixel based on its location and the
 * given edges. If the colors at the four corners of a pixel are different,
 * the function uses supersampling to get a more accurate color. Otherwise,
 * it computes an average color.
 *
 * @param edges Pointer to the array of edge colors for the scene.
 * @param sides An array of RGB colors representing the sides of the pixel.
 * @param dta Pointer to a structure containing scene and pixel details.
 *
 * @return The RGB color of the pixel.
 */
static inline t_rgb	calc_pixel_color(int *edges, t_rgb sides[2], t_info *dta)
{
	t_pix	pix;
	int		*color;

	pix.limit = 3;
	pix.w_x = dta->mrt->scn.w_x;
	pix.w_y = dta->mrt->scn.w_y;
	pix.max_y = dta->end_y;
	pix.x = dta->x;
	pix.y = dta->y;
	color = sample_pixel(edges, sides, pix, dta);
	if (ft_rgb_diff(color[0], color[3])
		|| ft_rgb_diff(color[1], color[2]))
		return (supersample(color, pix, dta->mrt));
	return (ft_rgb_balance(color));
}

/**
 * @brief Render a part of the scene.
 *
 * This function is designed to be thread-safe and can be used as a target
 * for pthreads or for a single thread execution. It renders a portion of the
 * scene based on the information in the provided structure,
 * storing the resulting colors in a buffer associated with the current camera.
 *
 * @param info A pointer to the structure containing details about the part of
 * the scene to render. It includes the starting and ending y-coordinates,
 * as well as scene and pixel details.
 *
 * @return NULL. It's a convention for pthread functions.
 */
static inline void	*render_scene(void *info)
{
	t_rgb	*edges;
	t_rgb	sides[3];
	t_rgb	color;
	t_info	*dta;

	dta = (t_info *)info;
	edges = create_edges_new(dta->mrt->scn.w_x + 2);
	while (dta->y < dta->end_y)
	{
		dta->x = 0;
		while (dta->x < dta->mrt->scn.w_x)
		{
			color = calc_pixel_color(edges, sides, dta);
			dta->mrt->cmr->addr[dta->y * dta->mrt->scn.w_x + dta->x] = color;
			dta->x++;
		}
		dta->y++;
	}
	ft_sec_free(edges);
	return (NULL);
}

#ifdef BONUS

/**
 * @brief Renders a part of the scene using multiple threads.
 *
 * The scene's height is divided into bands, and each thread renders a
 * specific band. This parallel processing enhances the rendering speed
 * by utilizing multi-core processors.
 *
 * @param mrt Pointer to the main structure containing all the information
 * about the scene, including cameras, objects, and other settings.
 * @param band_height Height of the band (portion of the scene) each thread
 * is responsible for.
 */
void	render_cam(t_mrt *mrt, int band)
{
	pthread_t	thread[THREADS];
	t_info		data[THREADS];
	int			thr;

	thr = -1;
	ft_memset(&thread, 0, sizeof(pthread_t) * THREADS);
	while (++thr < THREADS)
	{
		data[thr].mrt = mrt;
		data[thr].y = thr * band;
		if (thr == THREADS - 1)
			data[thr].end_y = mrt->scn.w_y;
		else
			data[thr].end_y = (thr + 1) * band;
		data[thr].max_y = thr * band;
		if (pthread_create(&thread[thr], NULL, render_scene, &data[thr]) != 0)
			msg_error_exit("Tread creation error");
	}
	thr = -1;
	while (++thr < THREADS)
		pthread_join(thread[thr], NULL);
}

/**
 * @brief Renders the main scene using all cameras available.
 * -BONUS VERSION-
 * Iterates through each camera in the scene, calling the multi-threaded
 * render function to generate the scene's perspective for that particular
 * camera. Once all cameras have rendered their views, the primary camera
 * is set as the active camera.
 *
 * @param mrt Pointer to the main structure containing all the information
 * about the scene, including cameras, objects, and other settings.
 */
void	render_main(t_mrt *mrt)
{
	int	band;

	band = mrt->scn.w_y / THREADS;
	while (mrt->cmr)
	{
		render_cam(mrt, band);
		mrt->cmr = mrt->cmr->next;
	}
	mrt->cmr = mrt->main_cam;
}

#else

/**
 * @brief Renders the main scene using the primary camera perspective.
 * -MANDATORY VERSION-
 * Initializes the rendering parameters, such as starting and ending
 * coordinates, then invokes the rendering function to generate the scene
 * from the primary camera's viewpoint.
 *
 * @param mrt Pointer to the main structure containing all the information
 * about the scene, including cameras, objects, and other settings.
 */
void	render_main(t_mrt *mrt)
{
	t_info	info;

	info.mrt = mrt;
	info.end_y = mrt->scn.w_y;
	info.max_y = mrt->scn.w_y;
	info.x = 0;
	info.y = 0;
	render_scene(&info);
}

#endif
