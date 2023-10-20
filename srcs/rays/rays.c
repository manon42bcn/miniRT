/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:05:03 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/25 23:22:20 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Calculate the direction for a ray from the camera's eye based on a
 * pixel and offset.
 *
 * This function determines the direction in which a ray should be cast from
 * the camera's eye through a particular pixel on the view screen.
 * It takes into account a specific offset, defined by the parameter `n`,
 * to introduce a form of supersampling or sub-pixel rendering. The offset
 * essentially divides a pixel into sub-pixels and then calculates the ray
 * direction for each sub-pixel, ensuring a smoother and more detailed render.
 *
 * @param n Index or identifier for specific ray direction or pattern.
 * Determines x and y offsets.
 * @param pix Structure containing information about the current pixel.
 * @param mrt Pointer to the main rendering structure containing scene,
 * camera, and other details.
 * @return A 3D vector (t_v3d) representing the calculated direction for the ray.
 */
static inline t_v3d	camera_eye(int n, t_pix pix, t_mrt *mrt)
{
	double	x_ofs;
	double	y_ofs;
	t_v3d	p;

	x_ofs = ((n % 3) * 0.5);
	y_ofs = ((n / 3) * 0.5);
	p.x = ((2 * ((pix.x + x_ofs) / pix.w_x)) - 1)
		* mrt->scn.ratio * mrt->cmr->fov;
	p.y = (1 - (2 * ((pix.y + y_ofs) / pix.w_y))) * mrt->cmr->fov;
	p.x = -p.x;
	p.z = 1;
	return (p);
}

/**
 * @brief Transform a given direction vector to align with the camera's
 * rientation.
 *
 * The function adjusts the given direction to be relative to the
 * camera'sorientation. This is achieved by constructing a local coordinate
 * system (or a basis) at the camera's position. The `cam_dir` represents
 * the forward direction (or z-axis) of the camera. The function computes
 * the right (x-axis) and up (y-axis) directions based on the camera's
 * forward direction, ensuring a right-handed coordinate system.
 * The input direction is then expressed in terms of this new basis.
 *
 * The function handles the special case when the camera is pointing directly
 * up or down, adjusting the x-axis appropriately.
 *
 * @param dir Initial direction vector, typically in world space.
 * @param cam_dir The forward direction of the camera.
 * @return A 3D vector (t_v3d) representing the adjusted direction
 * in camera space.
 */
static inline t_v3d	set_view(t_v3d dir, t_v3d cam_dir)
{
	t_v3d	x_ax;
	t_v3d	y_ax;
	t_v3d	z_ax;
	t_v3d	tmp;
	t_v3d	rst;

	tmp = ft_new_v3d(0, 1, 0);
	z_ax = cam_dir;
	if (cam_dir.y == 1 || cam_dir.y == -1)
	{
		if (cam_dir.y == 1)
			x_ax = (t_v3d){1, 0, 0};
		else
			x_ax = (t_v3d){-1, 0, 0};
	}
	else
		x_ax = ft_cross_v3d(tmp, z_ax);
	y_ax = ft_cross_v3d(z_ax, x_ax);
	rst.x = dir.x * x_ax.x + dir.y * y_ax.x + dir.z * z_ax.x;
	rst.y = dir.x * x_ax.y + dir.y * y_ax.y + dir.z * z_ax.y;
	rst.z = dir.x * x_ax.z + dir.y * y_ax.z + dir.z * z_ax.z;
	return (rst);
}

/**
 * @brief Calculate the color for a pixel by casting a ray from the camera.
 *
 * The function calculates the RGB value for a pixel by sending a ray from
 * the camera's eye through a specific position on the view screen, determined
 * by the pixel's coordinates. This ray is then used to determine interactions
 * with objects in the scene, such as reflections, to finally compute
 * the pixel's color.
 *
 * @param n An index or identifier to define a specific ray direction or pattern.
 * @param pix Structure containing information about the current pixel.
 * @param mrt Pointer to the main rendering structure containing scene,
 * camera, and other details.
 * @param REFLECTION_LIMIT Maximum number of reflections considered when
 * computing color.
 * @return An RGB structure representing the calculated color for the pixel.
 */
t_rgb	calc_ray(int n, t_pix pix, t_mrt *mrt)
{
	t_v3d	dir;
	t_rgb	color;

	dir = camera_eye(n, pix, mrt);
	dir = set_view(dir, mrt->cmr->dir);
	color = tracer(mrt->cmr->position, dir, mrt, REFLECTION_LIMIT);
	return (color);
}

t_v3d	ray_from_pixel(int x, int y, t_mrt *mrt)
{
	t_pix	pix;

	pix.w_x = mrt->scn.w_x;
	pix.w_y = mrt->scn.w_y;
	pix.x = x;
	pix.y = y;
	return (set_view(camera_eye(4, pix, mrt), mrt->cmr->dir));
}