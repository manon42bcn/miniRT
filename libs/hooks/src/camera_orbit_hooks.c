/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_orbit_hooks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 18:50:17 by mporras-          #+#    #+#             */
/*   Updated: 2023/08/08 18:50:19 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

void	camera_orbit_y(t_mrt *mrt, int key_dir)
{
	if (key_dir == K_UP)
		mrt->cmr->angle += RAD_ANGLE;
	else
		mrt->cmr->angle -= RAD_ANGLE;
	mrt->cmr->position.x = mrt->cmr->orbit * cos(mrt->cmr->angle);
	mrt->cmr->position.z = mrt->cmr->orbit * sin(mrt->cmr->angle);
	mrt->cmr->dir = ft_normal_v3d(
			ft_minus_v3d((t_v3d){0, 0, 0}, mrt->cmr->position));
	mrt->to_img = TO_RENDER;
}

void	camera_orbit_x(t_mrt *mrt, int key_dir)
{
	if (key_dir == K_UP)
		mrt->cmr->angle += RAD_ANGLE;
	else
		mrt->cmr->angle -= RAD_ANGLE;
	mrt->cmr->position.y = mrt->cmr->orbit * cos(mrt->cmr->angle);
	mrt->cmr->position.z = mrt->cmr->orbit * sin(mrt->cmr->angle);
	mrt->cmr->dir = ft_normal_v3d(
			ft_minus_v3d((t_v3d){0, 0, 0}, mrt->cmr->position));
	mrt->to_img = TO_RENDER;
}

void	camera_orbit_z(t_mrt *mrt, int key_dir)
{
	if (key_dir == K_UP)
		mrt->cmr->angle += RAD_ANGLE;
	else
		mrt->cmr->angle -= RAD_ANGLE;
	mrt->cmr->position.x = mrt->cmr->orbit * cos(mrt->cmr->angle);
	mrt->cmr->position.y = mrt->cmr->orbit * sin(mrt->cmr->angle);
	mrt->cmr->dir = ft_normal_v3d(
			ft_minus_v3d((t_v3d){0, 0, 0}, mrt->cmr->position));
	mrt->to_img = TO_RENDER;
}
