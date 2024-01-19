/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_translate_handlers.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:19:23 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/19 23:02:43 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

/**
 * @brief Translates the camera's position based on user input.
 *
 * Adjusts the camera's position in the 3D space based on the key pressed.
 * Supports translation along the X, Y, and Z axes. For example, pressing
 * the "up" key moves the camera upward along the Y-axis. After translating
 * the camera, the scene is marked to be re-rendered.
 *
 * @param key Keycode representing the desired direction of translation.
 * @param mrt Main runtime structure containing the scene's camera and
 * other data.
 * @return t_bool Always returns TRUE to indicate successful translation.
 */
t_bool	cam_translate(int key, t_mrt *mrt)
{
	t_cmr	*node;

	node = mrt->cmr;
	if (key == K_UP)
		node->position.y += MOVE_FACTOR;
	if (key == K_DOWN)
		node->position.y -= MOVE_FACTOR;
	if (key == K_LEFT)
		node->position.x -= MOVE_FACTOR;
	if (key == K_RIGHT)
		node->position.x += MOVE_FACTOR;
	if (key == K_PLUS)
		node->position.z += MOVE_FACTOR;
	if (key == K_MINUS)
		node->position.z -= MOVE_FACTOR;
	mrt->to_img = TO_RENDER;
	return (TRUE);
}

/**
 * @brief Toggles the camera's translation mode.
 *
 * Switches between the camera's normal operation mode and its translation
 * mode. When in translation mode, user input directly affects the camera's
 * position in the scene. The function also provides console feedback to
 * inform the user when they've entered or exited the camera translation mode.
 *
 * @param mrt Main runtime structure which holds the current mode
 * of the camera.
 * @return t_bool Returns TRUE when entering camera translation mode,
 * and FALSE when exiting it.
 */
int	camera_translate_mode(t_mrt *mrt)
{
	if (mrt->sel_obj)
		return (FALSE);
	if (mrt->mode == TO_EYE)
	{
		mrt->mode = NORMAL;
		ft_putstr_fd("[BACK TO NORMAL MODE]\n", STDOUT_FILENO);
		return (FALSE);
	}
	mrt->mode = TO_EYE;
	ft_putstr_fd("[CAMERA TRANSLATE MODE ACTIVATE]\n", STDOUT_FILENO);
	return (TRUE);
}
