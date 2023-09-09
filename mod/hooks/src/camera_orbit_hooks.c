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

/**
 * @brief Adjust the camera's orbital position around the Y-axis.
 *
 * This function modifies the camera's position based on an orbital
 * movement around the Y-axis. It recalculates the camera's position
 * and direction based on the angle and the defined radius of the orbit.
 *
 * @param mrt The main struct containing the camera and its attributes.
 * @param key_dir The direction in which the key is pressed (e.g., up or down).
 * @return void
 */
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

/**
 * @brief Adjust the camera's orbital position around the X-axis.
 *
 * This function modifies the camera's position based on an orbital
 * movement around the X-axis. It recalculates the camera's position
 * and direction based on the angle and the defined radius of the orbit.
 *
 * @param mrt The main struct containing the camera and its attributes.
 * @param key_dir The direction in which the key is pressed (e.g., up or down).
 * @return void
 */
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

/**
 * @brief Adjust the camera's orbital position around the Z-axis.
 *
 * This function modifies the camera's position based on an orbital
 * movement around the Z-axis. It recalculates the camera's position
 * and direction based on the angle and the defined radius of the orbit.
 *
 * @param mrt The main struct containing the camera and its attributes.
 * @param key_dir The direction in which the key is pressed (e.g., up or down).
 * @return void
 */
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
