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

#include "hooks.h"

void	camera_closest_y(t_mrt *mrt, int key_dir)
{
	static double	angle = 0;

	if (key_dir == K_UP)
		angle += RAD_ANGLE;
	else
		angle -= RAD_ANGLE;
	mrt->cmr->position.x = mrt->cmr->close_obj->position.x
		+ mrt->cmr->orbit * cos(angle);
	mrt->cmr->position.z = mrt->cmr->close_obj->position.z
		+ mrt->cmr->orbit * sin(angle);
	mrt->cmr->dir = ft_normal_v3d(
			ft_minus_v3d(mrt->cmr->close_obj->position,
				mrt->cmr->position));
	mrt->to_img = TO_RENDER;
}

void	camera_closest_x(t_mrt *mrt, int key_dir)
{
	static double	angle = 0;

	if (key_dir == K_UP)
		angle += RAD_ANGLE;
	else
		angle -= RAD_ANGLE;
	mrt->cmr->position.y = mrt->cmr->close_obj->position.y
		+ mrt->cmr->orbit * cos(angle);
	mrt->cmr->position.z = mrt->cmr->close_obj->position.z
		+ mrt->cmr->orbit * sin(angle);
	mrt->cmr->dir = ft_normal_v3d(
			ft_minus_v3d(mrt->cmr->close_obj->position,
				mrt->cmr->position));
	mrt->to_img = TO_RENDER;
}

void	camera_closest_z(t_mrt *mrt, int key_dir)
{
	static double	angle = 0;

	if (key_dir == K_UP)
		angle += RAD_ANGLE;
	else
		angle -= RAD_ANGLE;
	mrt->cmr->position.x = mrt->cmr->close_obj->position.x
		+ mrt->cmr->orbit * cos(angle);
	mrt->cmr->position.y = mrt->cmr->close_obj->position.y
		+ mrt->cmr->orbit * sin(angle);
	mrt->cmr->dir = ft_normal_v3d(
			ft_minus_v3d(mrt->cmr->close_obj->position,
				mrt->cmr->position));
	mrt->to_img = TO_RENDER;
}
