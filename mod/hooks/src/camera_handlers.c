/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:57:08 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/05 15:55:51 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

/**
 * @brief Handles the camera rotation based on user input.
 *
 * Determines the axis and direction of rotation based on the provided key
 * input and calls the appropriate function to rotate the camera around the
 * selected object. After rotation, it recalculates the camera's direction vector
 * to ensure it still points towards the selected object.
 *
 * @param key Keycode representing the desired rotation direction and axis.
 * @param mrt Main runtime structure with all scene details and current camera
 * settings.
 * @return int Returns TRUE if a valid rotation is performed, otherwise returns
 * FALSE.
 */
int	cam_rotation(int key, t_mrt *mrt)
{
	t_v3d	to_cam;
	t_v3d	cam_obj;

	if (mrt->sel_obj == NULL || mrt->mode != TO_CAMERA)
		return (FALSE);
	cam_obj = ft_minus_v3d(mrt->cmr->position, mrt->sel_obj->elm.fig.centre);
	if (key == K_RIGHT)
		to_cam = ft_rot_v3d(cam_obj, X_C, RAD_ANGLE);
	else if (key == K_LEFT)
		to_cam = ft_rot_v3d(cam_obj, X_C, -RAD_ANGLE);
	else if (key == K_UP)
		to_cam = ft_rot_v3d(cam_obj, Y_C, RAD_ANGLE);
	else if (key == K_DOWN)
		to_cam = ft_rot_v3d(cam_obj, Y_C, -RAD_ANGLE);
	else if (key == K_PLUS)
		to_cam = ft_rot_v3d(cam_obj, Z_C, RAD_ANGLE);
	else
		to_cam = ft_rot_v3d(cam_obj, Z_C, -RAD_ANGLE);
	mrt->cmr->position = ft_plus_v3d(mrt->sel_obj->elm.fig.centre, to_cam);
	mrt->cmr->dir = ft_normal_v3d(
			ft_minus_v3d(mrt->sel_obj->elm.fig.centre,
				mrt->cmr->position));
	mrt->to_img = TO_RENDER;
	return (TRUE);
}

/**
 * @brief Toggles the camera's rotation mode.
 *
 * This function manages the camera's rotation mode. When invoked:
 * - If the camera is currently in rotation mode, it switches back to the
 *   normal mode.
 * - If there's no object currently selected, the function exits without
 * 	 enabling rotation mode.
 * - Otherwise, it switches to the camera rotation mode, allowing the user
 *   to orbit the camera around the selected object.
 *
 * Additionally, the function provides console feedback to notify the user
 * when they've entered the camera rotation mode.
 *
 * @param mrt Main runtime structure holding the current mode of the camera
 * and the selected object.
 * @return int Returns TRUE when entering or exiting camera rotation mode,
 * and FALSE otherwise.
 */
int	camera_rotation_mode(t_mrt *mrt)
{
	if (mrt->mode == TO_CAMERA)
		return (normal_mode(mrt));
	if (mrt->sel_obj == NULL)
		return (FALSE);
	mrt->mode = TO_CAMERA;
	ft_putstr_fd("[CAMERA ROTATION MODE ACTIVATE]\n", STDOUT_FILENO);
	return (TRUE);
}
