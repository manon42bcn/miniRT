/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 23:17:58 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/14 23:04:11 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

/**
 * @brief Resets the selected light to its default state and prints an
 * back to normal message.
 *
 * This function unselects the currently selected light source in the scene
 * and returns to the normal mode. It also outputs an back to normal message to
 * the standard output to inform the user that the light source has been
 * unselected.
 *
 * @param mrt Pointer to the main ray-tracing structure, holding information
 * about the scene.
 *
 * @return t_bool Returns TRUE if a light was unselected, otherwise returns
 * FALSE.
 */
t_bool	normal_light(t_mrt *mrt)
{
	if (mrt->scn.sel_light == NULL)
		return (FALSE);
	mrt->scn.sel_light = NULL;
	mrt->mode = NORMAL;
	mrt->to_img = TO_RENDER;
	ft_putstr_fd("[LIGHT UNSELECT - BACK TO NORMAL]\n", STDOUT_FILENO);
	return (TRUE);
}

/**
 * @brief Resets the selected object to its default state and prints an back
 * to normal message.
 *
 * This function unselects the currently selected object in the scene, reverts
 * its color to the original one, and returns to the normal mode. An back
 * to normal message is also printed to the standard output to notify the user
 * that the object has been unselected.
 *
 * @param mrt Pointer to the main ray-tracing structure, holding information
 * about the scene.
 *
 * @return t_bool Returns TRUE if an object was unselected, otherwise returns
 * FALSE.
 */
t_bool	normal_object(t_mrt *mrt)
{
	if (mrt->sel_obj == NULL)
		return (FALSE);
	mrt->sel_obj->color = mrt->sel_obj->orig_color;
	mrt->sel_obj = NULL;
	mrt->mode = NORMAL;
	mrt->to_img = TO_RENDER;
	ft_putstr_fd("[OBJECT UNSELECT - BACK TO NORMAL]\n", STDOUT_FILENO);
	return (TRUE);
}

/**
 * @brief Switches the scene back to the normal mode.
 *
 * This function resets the mode to NORMAL if it's currently set to other mode.
 * It unselects any selected light source and object in the scene.
 *
 * @param mrt Pointer to the main ray-tracing structure, holding information
 * about the scene and current mode.
 *
 * @return t_bool Returns TRUE if the mode was switched to NORMAL,
 * otherwise returns FALSE.
 */
t_bool	normal_mode(t_mrt *mrt)
{
	if (mrt->mode == NORMAL)
		return (FALSE);
	normal_light(mrt);
	normal_object(mrt);
	mrt->mode = NORMAL;
	return (TRUE);
}
