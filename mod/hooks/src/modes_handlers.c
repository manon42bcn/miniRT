/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 00:41:26 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/14 23:02:23 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

/**
 * @brief Activates the rotation modification mode for the currently selected
 * object.
 *
 * If the program is currently in NORMAL mode or any mode beyond TO_CAMERA,
 * the function will not switch to rotation mode. If the switch is successful,
 * it provides a console output to notify the user of the mode change.
 * Once activated, a corresponding message is displayed to the standard output.
 *
 * @param mrt Pointer to the main ray-tracing structure which holds information
 * about the scene and current mode.
 *
 * @return t_bool Returns TRUE if the rotation mode was activated,
 * and FALSE otherwise.
 */
t_bool	rotation_mode(t_mrt *mrt)
{
	if (mrt->mode == NORMAL || mrt->mode > TO_CAMERA)
		return (FALSE);
	mrt->mode = TO_ROTATE;
	ft_putstr_fd("[ROTATION MODE ACTIVATE]\n", STDOUT_FILENO);
	return (TRUE);
}

/**
 * @brief Activates the width-diameter adjustment mode for the selected object.
 *
 * If the program is currently in NORMAL mode or any mode beyond TO_CAMERA,
 * the function will not switch to width-diameter mode. If the switch is
 * successful, it provides a console output to notify the user of the mode
 * change. Once activated, a corresponding message is displayed to the standard
 * output.
 *
 * @param mrt Pointer to the main ray-tracing structure which holds information
 * about the scene and current mode.
 *
 * @return t_bool Returns TRUE if the mode was activated, and FALSE otherwise.
 */
t_bool	width_mode(t_mrt *mrt)
{
	if (mrt->mode == NORMAL || mrt->mode > TO_CAMERA)
		return (FALSE);
	mrt->mode = TO_WIDTH;
	ft_putstr_fd("[WIDTH-DIAM MODE ACTIVATE]\n", STDOUT_FILENO);
	return (TRUE);
}

/**
 * @brief Activates the height modification mode for the currently selected
 * object.
 *
 * If the program is currently in NORMAL mode or any mode beyond TO_CAMERA,
 * the function will not switch to height mode. If the switch is successful,
 * it provides a console output to notify the user of the mode change.
 * Once activated, a corresponding message is displayed to the standard output.
 *
 * @param mrt Pointer to the main ray-tracing structure which holds information
 * about the scene and current mode.
 *
 * @return t_bool Returns TRUE if the height mode was activated,
 * and FALSE otherwise.
 */
t_bool	height_mode(t_mrt *mrt)
{
	if (mrt->mode == NORMAL || mrt->mode > TO_CAMERA)
		return (FALSE);
	mrt->mode = TO_HEIGHT;
	ft_putstr_fd("[HEIGHT MODE ACTIVATE]\n", STDOUT_FILENO);
	return (TRUE);
}

/**
 * @brief Switches the current mode to translate mode for adjusting object
 * positions.
 *
 * If the program is currently in NORMAL mode or any mode beyond TO_CAMERA,
 * the function will not switch to translate mode. If the switch is successful,
 * it provides a console output to notify the user of the mode change.
 * Once activated, a corresponding message is displayed to the standard output.
 *
 * @param mrt Pointer to the main ray-tracing structure which holds information
 * about the scene and current mode.
 *
 * @return t_bool Returns TRUE if the translate mode was activated,
 * and FALSE otherwise.
 */
t_bool	translate_mode(t_mrt *mrt)
{
	if (mrt->mode == NORMAL || mrt->mode > TO_CAMERA)
		return (FALSE);
	mrt->mode = TO_TRANSLATE;
	ft_putstr_fd("[TRANSLATE MODE ACTIVATE]\n", STDOUT_FILENO);
	return (TRUE);
}

/**
 * @brief Activates the SELECTION MODE for the scene.
 *
 * If NORMAL mode is set, this function sets the scene mode
 * to TO_SELECT and provides a user notification that
 * SELECTION MODE has been activated.
 *
 * @param mrt Pointer to the scene's main struct which contains the
 * list of objects and the current mode.
 *
 * @return t_bool Returns TRUE after setting the mode and printing the
 * notification message if NORMAL mode is active. Otherwise
 * return FALSE.
 */
t_bool	selection_mode(t_mrt *mrt)
{
	if (mrt->mode > TO_CAMERA)
		return (FALSE);
	if (mrt->mode > NORMAL && mrt->mode <= TO_CAMERA)
		return (normal_mode(mrt));
	mrt->mode = TO_SELECT;
	ft_putstr_fd("[SELECTION MODE ACTIVATE]\n", STDOUT_FILENO);
	return (TRUE);
}
