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

t_rgb	calc_ray(int n, t_pix pix, t_mrt *mrt)
{
	t_v3d	dir;
	t_rgb	color;

	dir = camera_eye(n, pix, mrt);
	dir = set_view(dir, mrt->cmr->dir);
	color = tracer(mrt->cmr->position, dir, mrt, REFLECTION_LIMIT);
	return (color);
}
