/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 17:57:08 by mporras-          #+#    #+#             */
/*   Updated: 2023/10/24 17:57:10 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Rotates the camera around the Y-axis relative to a selected object's
 * position.
 *
 * This function adjusts the camera's position based on the selected object's
 * center. It rotates the camera in a circular path around the Y-axis of the
 * object, either in a clockwise or counterclockwise direction, depending on
 * the key provided.
 *
 * @param mrt Main runtime structure containing all necessary scene information,
 *            including objects and the camera's current configuration.
 * @param key Keycode indicating the direction of rotation:
 *            - K_UP: Rotate the camera in the positive Y direction
 *            (counterclockwise).
 *            - K_DOWN: Rotate the camera in the negative Y direction
 *            (clockwise)
 */
static inline void	cam_orbit_y(t_mrt *mrt, int key)
{
	t_v3d	to_cam;

	if (key == K_UP)
		to_cam = ft_rot_v3d_y(
				ft_minus_v3d(mrt->cmr->position,
					mrt->sel_obj->elm.fig.centre), RAD_ANGLE);
	else
		to_cam = ft_rot_v3d_y(
				ft_minus_v3d(mrt->cmr->position,
					mrt->sel_obj->elm.fig.centre), -RAD_ANGLE);
	mrt->cmr->position = ft_plus_v3d(mrt->sel_obj->elm.fig.centre, to_cam);
}

/**
 * @brief Rotates the camera around the X-axis relative to a selected object's
 * position.
 *
 * Similar to cam_orbit_y, this function adjusts the camera's position to orbit
 * around the selected object's X-axis. This leads to an up-down circular motion
 * of the camera around the object.
 *
 * @param mrt Main runtime structure with scene details and camera configuration.
 * @param key Keycode indicating the direction of rotation:
 *            - K_LEFT: Rotate the camera in the positive X direction.
 *            - K_RIGHT: Rotate the camera in the negative X direction.
 */
static inline void	cam_orbit_x(t_mrt *mrt, int key)
{
	t_v3d	to_cam;

	if (key == K_RIGHT)
		to_cam = ft_rot_v3d_x(
				ft_minus_v3d(mrt->cmr->position,
					mrt->sel_obj->elm.fig.centre), RAD_ANGLE);
	else
		to_cam = ft_rot_v3d_x(
				ft_minus_v3d(mrt->cmr->position,
					mrt->sel_obj->elm.fig.centre), -RAD_ANGLE);
	mrt->cmr->position = ft_plus_v3d(mrt->sel_obj->elm.fig.centre, to_cam);
}

/**
 * @brief Rotates the camera around the Z-axis relative to a selected object's
 * position.
 *
 * By adjusting the camera's position relative to the selected object's Z-axis,
 * the camera orbits around the object in a flat circular motion, akin to
 * revolving around the equator of the object.
 *
 * @param mrt Contains scene data and current camera configuration.
 * @param key Keycode indicating the direction of rotation:
 *            - K_PLUS: Rotate the camera in the positive Z direction.
 *            - K_MINUS: Rotate the camera in the negative Z direction.
 */
static inline void	cam_orbit_z(t_mrt *mrt, int key)
{
	t_v3d	to_cam;

	if (key == K_PLUS)
		to_cam = ft_rot_v3d_z(
				ft_minus_v3d(mrt->cmr->position,
					mrt->sel_obj->elm.fig.centre), RAD_ANGLE);
	else
		to_cam = ft_rot_v3d_z(
				ft_minus_v3d(mrt->cmr->position,
					mrt->sel_obj->elm.fig.centre), -RAD_ANGLE);
	mrt->cmr->position = ft_plus_v3d(mrt->sel_obj->elm.fig.centre, to_cam);
}

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
	if (mrt->sel_obj == NULL || mrt->mode != TO_CAMERA)
		return (FALSE);
	if (key == K_LEFT || key == K_RIGHT)
		cam_orbit_x(mrt, key);
	if (key == K_UP || key == K_DOWN)
		cam_orbit_y(mrt, key);
	if (key == K_PLUS || key == K_MINUS)
		cam_orbit_z(mrt, key);
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
