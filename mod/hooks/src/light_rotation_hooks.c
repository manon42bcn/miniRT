/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_rotation_hooks.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:15:38 by mporras-          #+#    #+#             */
/*   Updated: 2023/08/12 18:15:39 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

/**
 * @brief Rotates the light source about the X-axis.
 *
 * Depending on the key direction, the function modifies the rotation angle
 * of the light. The new position of the light is then calculated by
 * rotating the original position about the X-axis.
 *
 * @param mrt Pointer to the main runtime structure.
 * @param key_dir Direction of rotation (K_UP for counterclockwise,
 * K_DOWN for clockwise).
 */
void	light_rotation_x(t_mrt *mrt, int key_dir)
{
	t_light	*node;

	node = mrt->scn.light;
	while (node)
	{
		if (key_dir == K_UP)
			node->angle += RAD_ANGLE;
		else if (key_dir == K_DOWN)
			node->angle -= RAD_ANGLE;
		node->origin = rotate_x(node->origin, node->angle);
		mrt->to_img = TO_RENDER;
		node = node->next;
	}
}

/**
 * @brief Rotates the light source about the Y-axis.
 *
 * Depending on the key direction, the function modifies the rotation angle
 * of the light. The new position of the light is then calculated by
 * rotating the original position about the Y-axis.
 *
 * @param mrt Pointer to the main runtime structure.
 * @param key_dir Direction of rotation (K_UP for counterclockwise,
 * K_DOWN for clockwise).
 */
void	light_rotation_y(t_mrt *mrt, int key_dir)
{
	t_light	*node;

	node = mrt->scn.light;
	while (node)
	{
		if (key_dir == K_UP)
			node->angle += RAD_ANGLE;
		else if (key_dir == K_DOWN)
			node->angle -= RAD_ANGLE;
		node->origin = rotate_y(node->origin, node->angle);
		mrt->to_img = TO_RENDER;
		node = node->next;
	}
}

/**
 * @brief Rotates the light source about the Z-axis.
 *
 * Depending on the key direction, the function modifies the rotation angle
 * of the light. The new position of the light is then calculated by
 * rotating the original position about the Z-axis.
 *
 * @param mrt Pointer to the main runtime structure.
 * @param key_dir Direction of rotation (K_UP for counterclockwise,
 * K_DOWN for clockwise).
 */
void	light_rotation_z(t_mrt *mrt, int key_dir)
{
	t_light	*node;

	node = mrt->scn.light;
	while (node)
	{
		if (key_dir == K_UP)
			node->angle += RAD_ANGLE;
		else if (key_dir == K_DOWN)
			node->angle -= RAD_ANGLE;
		node->origin = rotate_z(node->origin, node->angle);
		mrt->to_img = TO_RENDER;
		node = node->next;
	}
}
