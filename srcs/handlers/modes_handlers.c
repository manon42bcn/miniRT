/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modes_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 00:41:26 by mporras-          #+#    #+#             */
/*   Updated: 2023/10/22 00:41:28 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Activates the rotation modification mode for the currently selected
 * object.
 *
 * This function checks if the current mode is SELECTION. If so, the mode
 * is changed to TO_ROTATE, which indicates that the user is in rotation
 * modification mode. It also provides a console output to notify the user
 * of the mode change.
 *
 * @param mrt Pointer to the main ray-tracing structure which holds information
 * about the scene and current mode.
 *
 * @return int Returns TRUE if the rotation mode was activated,
 * and FALSE otherwise.
 */
int	rotation_mode(t_mrt *mrt)
{
	if (mrt->mode != SELECTION)
		return (FALSE);
	mrt->mode = TO_ROTATE;
	ft_putstr_fd("[ROTATION MODE ACTIVATE]\n", STDOUT_FILENO);
	return (TRUE);
}

/**
 * @brief Activates the width-diameter adjustment mode for the selected object.
 *
 * This function switches the mode to TO_WIDTH for adjusting the width or
 * diameter of the currently selected object. The function will only activate
 * the mode if the current mode is SELECTION. Once activated, a corresponding
 * message is displayed to the standard output.
 *
 * @param mrt Pointer to the main ray-tracing structure which holds information
 * about the scene and current mode.
 *
 * @return int Returns TRUE if the mode was activated, and FALSE otherwise.
 */
int	width_mode(t_mrt *mrt)
{
	if (mrt->mode != SELECTION)
		return (FALSE);
	mrt->mode = TO_WIDTH;
	ft_putstr_fd("[WIDTH-DIAM MODE ACTIVATE]\n", STDOUT_FILENO);
	return (TRUE);
}

/**
 * @brief Activates the height modification mode for the currently selected
 * object.
 *
 * This function checks if the current mode is SELECTION. If so, the mode
 * is changed to TO_HEIGHT, which indicates that the user is in height
 * modification mode. It also provides a console output to notify the user
 * of the mode change.
 *
 * @param mrt Pointer to the main ray-tracing structure which holds information
 * about the scene and current mode.
 *
 * @return int Returns TRUE if the height mode was activated,
 * and FALSE otherwise.
 */
int	height_mode(t_mrt *mrt)
{
	if (mrt->mode != SELECTION)
		return (FALSE);
	mrt->mode = TO_HEIGHT;
	ft_putstr_fd("[HEIGHT MODE ACTIVATE]\n", STDOUT_FILENO);
	return (TRUE);
}
