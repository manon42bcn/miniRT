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

/**
 * @brief Adjust the camera's position on the Y-axis based on key direction.
 *
 * This function modifies the camera's position in relation to its target
 * (the closest object). It recalculates the position based on an orbital
 * movement around the Y-axis.
 *
 * @param mrt The main struct containing the camera and its attributes.
 * @param key_dir The direction in which the key is pressed (e.g., up or down).
 * @return void
 */
void	camera_closest_y(t_mrt *mrt, int key_dir)
{
	if (key_dir == K_UP)
		mrt->cmr->angle += RAD_ANGLE;
	else
		mrt->cmr->angle -= RAD_ANGLE;
	mrt->cmr->position.x = mrt->cmr->close_obj->position.x
		+ mrt->cmr->orbit * cos(mrt->cmr->angle);
	mrt->cmr->position.z = mrt->cmr->close_obj->position.z
		+ mrt->cmr->orbit * sin(mrt->cmr->angle);
	mrt->cmr->dir = ft_normal_v3d(
			ft_minus_v3d(mrt->cmr->close_obj->position,
				mrt->cmr->position));
	mrt->to_img = TO_RENDER;
}

/**
 * @brief Adjust the camera's position on the X-axis based on key direction.
 *
 * This function modifies the camera's position in relation to its target
 * (the closest object). It recalculates the position based on an orbital
 * movement around the X-axis.
 *
 * @param mrt The main struct containing the camera and its attributes.
 * @param key_dir The direction in which the key is pressed (e.g., up or down).
 * @return void
 */
void	camera_closest_x(t_mrt *mrt, int key_dir)
{
	if (key_dir == K_UP)
		mrt->cmr->angle += RAD_ANGLE;
	else
		mrt->cmr->angle -= RAD_ANGLE;
	mrt->cmr->position.y = mrt->cmr->close_obj->position.y
		+ mrt->cmr->orbit * cos(mrt->cmr->angle);
	mrt->cmr->position.z = mrt->cmr->close_obj->position.z
		+ mrt->cmr->orbit * sin(mrt->cmr->angle);
	mrt->cmr->dir = ft_normal_v3d(
			ft_minus_v3d(mrt->cmr->close_obj->position,
				mrt->cmr->position));
	mrt->to_img = TO_RENDER;
}

/**
 * @brief Adjust the camera's position on the Z-axis based on key direction.
 *
 * This function modifies the camera's position in relation to its target
 * (the closest object). It recalculates the position based on an orbital
 * movement around the Z-axis.
 *
 * @param mrt The main struct containing the camera and its attributes.
 * @param key_dir The direction in which the key is pressed (e.g., up or down).
 * @return void
 */
void	camera_closest_z(t_mrt *mrt, int key_dir)
{
	if (key_dir == K_UP)
		mrt->cmr->angle += RAD_ANGLE;
	else
		mrt->cmr->angle -= RAD_ANGLE;
	mrt->cmr->position.x = mrt->cmr->close_obj->position.x
		+ mrt->cmr->orbit * cos(mrt->cmr->angle);
	mrt->cmr->position.y = mrt->cmr->close_obj->position.y
		+ mrt->cmr->orbit * sin(mrt->cmr->angle);
	mrt->cmr->dir = ft_normal_v3d(
			ft_minus_v3d(mrt->cmr->close_obj->position,
				mrt->cmr->position));
	mrt->to_img = TO_RENDER;
}
