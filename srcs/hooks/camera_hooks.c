/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 23:57:38 by mporras-          #+#    #+#             */
/*   Updated: 2023/08/07 23:57:40 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	camera_closest_y(t_mrt *mrt, int x, int y, int mouse_code)
{
	static double	angle = 0;
	double			rad;

	(void)x;
	(void)y;
	rad = sqrt(mrt->cmr->position.x * mrt->cmr->position.x
			+ mrt->cmr->position.y * mrt->cmr->position.y
			+ mrt->cmr->position.z * mrt->cmr->position.z);
	if (mouse_code == RIGHT_CLICK)
		angle += RAD_ANGLE;
	else
		angle -= RAD_ANGLE;
	mrt->cmr->position.x = mrt->cmr->close_obj->position.x + rad * cos(angle);
	mrt->cmr->position.y = mrt->cmr->close_obj->position.y;
	mrt->cmr->position.z = mrt->cmr->close_obj->position.z + rad * sin(angle);
	mrt->cmr->dir = ft_normal_v3d(
			ft_minus_v3d(mrt->cmr->close_obj->position, mrt->cmr->position));
	mrt->to_img = TO_RENDER;
}

void	camera_closest_x(t_mrt *mrt, int x, int y, int mouse_code)
{
	static double	angle = 0;
	double			rad;

	(void)x;
	(void)y;
	rad = sqrt(mrt->cmr->position.x * mrt->cmr->position.x
			+ mrt->cmr->position.y * mrt->cmr->position.y
			+ mrt->cmr->position.z * mrt->cmr->position.z);
	if (mouse_code == RIGHT_CLICK)
		angle += RAD_ANGLE;
	else
		angle -= RAD_ANGLE;
	mrt->cmr->position.x = mrt->cmr->close_obj->position.x;
	mrt->cmr->position.y = mrt->cmr->close_obj->position.y + rad * cos(angle);
	mrt->cmr->position.z = mrt->cmr->close_obj->position.z + rad * sin(angle);
	mrt->cmr->dir = ft_normal_v3d(
			ft_minus_v3d(mrt->cmr->close_obj->position, mrt->cmr->position));
	mrt->to_img = TO_RENDER;
}

void	camera_closest_z(t_mrt *mrt, int x, int y, int mouse_code)
{
	static double	angle = 0;
	double			rad;

	(void)x;
	(void)y;
	rad = sqrt(mrt->cmr->position.x * mrt->cmr->position.x
			+ mrt->cmr->position.y * mrt->cmr->position.y
			+ mrt->cmr->position.z * mrt->cmr->position.z);
	if (mouse_code == RIGHT_CLICK)
		angle += RAD_ANGLE;
	else
		angle -= RAD_ANGLE;
	mrt->cmr->position.x = mrt->cmr->close_obj->position.x + rad * cos(angle);
	mrt->cmr->position.y = mrt->cmr->close_obj->position.y + rad * sin(angle);
	mrt->cmr->position.z = mrt->cmr->close_obj->position.z;
	mrt->cmr->dir = ft_normal_v3d(
			ft_minus_v3d(mrt->cmr->close_obj->position, mrt->cmr->position));
	mrt->to_img = TO_RENDER;
}
