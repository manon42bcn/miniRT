/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 22:09:53 by mporras-          #+#    #+#             */
/*   Updated: 2023/10/22 22:09:55 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Switches the current mode to LIGHT mode for selecting and adjusting
 * scene lights.
 *
 * If the program is currently in a mode down to TO_CAMERA, the function will
 * not switch to LIGHT mode. Otherwise, it toggles between the currently selected
 * light and the next light in the scene's light list.
 * A console output is provided to notify the user when a light is selected.
 *
 * @param mrt Pointer to the main ray-tracing structure which holds information
 * about the current mode, the selected light, and other scene details.
 *
 * @return int Returns TRUE if a light was successfully selected or toggled to,
 * and FALSE if the mode change wasn't allowed due to the current mode.
 */
int	light_mode(t_mrt *mrt)
{
	if (mrt->mode > NORMAL && mrt->mode <= TO_CAMERA)
		return (FALSE);
	if (mrt->scn.sel_light == NULL)
		mrt->scn.sel_light = mrt->scn.light;
	else
	{
		if (!mrt->scn.sel_light->next)
			return (normal_light(mrt));
		mrt->scn.sel_light = mrt->scn.sel_light->next;
	}
	mrt->mode = TO_LIGHT;
	ft_putstr_fd("[LIGHT SELECTED]\n", STDOUT_FILENO);
	return (TRUE);
}

/**
 * @brief Translates the selected light's position based on the provided key
 * input.
 *
 * This function allows the user to move the selected light source in the 3D
 * space along the x, y, and z axes. The magnitude of the translation is set
 * to 0.1 units It only works when the mode is in SELECTION.
 *
 * Key Options:
 * - K_UP: Move the light upwards in the y direction.
 * - K_DOWN: Move the light downwards in the y direction.
 * - K_LEFT: Move the light to the left in the x direction.
 * - K_RIGHT: Move the light to the right in the x direction.
 * - K_PLUS: Move the light forwards in the z direction.
 * - K_MINUS: Move the light backwards in the z direction.
 *
 * After translating the light source, the scene is flagged for re-rendering.
 *
 * @param key The input key code determining the direction of the light's
 * movement.
 * @param mrt Pointer to the main ray-tracing structure, holding information
 * about the scene.
 *
 * @return int Returns TRUE if the light was successfully translated,
 * FALSE otherwise.
 */
static inline int	light_traslation(int key, t_mrt *mrt)
{
	t_light	*node;

	node = mrt->scn.sel_light;
	if (key == K_UP)
		node->origin.y += 0.1f;
	if (key == K_DOWN)
		node->origin.y -= 0.1f;
	if (key == K_LEFT)
		node->origin.x -= 0.1f;
	if (key == K_RIGHT)
		node->origin.x += 0.1f;
	if (key == K_PLUS)
		node->origin.z += 0.1f;
	if (key == K_MINUS)
		node->origin.z -= 0.1f;
	mrt->to_img = TO_RENDER;
	return (TRUE);
}

/**
 * @brief Adjusts the brightness of the selected light source based on the
 * provided key input.
 *
 * This function allows the user to modify the brightness level of the currently
 * selected light.
 * Each key press adjusts the brightness by a magnitude of 0.1 units.
 *
 * Key Options:
 * - K_B: Increase the brightness of the light by 0.1.
 * - K_V: Decrease the brightness of the light by 0.1, ensuring it doesn't
 * 		  go below 0.
 *
 * @param key The input key code determining the direction of the brightness
 * adjustment.
 * @param mrt Pointer to the main ray-tracing structure, holding information
 * about the scene.
 *
 * @return int Returns TRUE after adjusting the brightness.
 */
static inline int	light_bright(int key, t_mrt *mrt)
{
	t_light	*light;

	light = mrt->scn.sel_light;
	if (key == K_B)
		light->bright += 0.1f;
	if (key == K_V && light->bright - 0.1f > 0)
		light->bright -= 0.1f;
	return (TRUE);
}

/**
 * @brief Handles changes to the behavior of the currently selected light source.
 *
 * Depending on the key pressed, this function adjusts the position or brightness
 * of the selected light source. If no light source is currently selected, the
 * function returns immediately.
 *
 * @param key An integer representing the key pressed by the user.
 * @param mrt Pointer to the main ray-tracing structure, holding information
 * about the scene and selected elements.
 *
 * @return int Returns TRUE if any changes were made to the light's behavior;
 * otherwise returns FALSE.
 */
int	light_behaviour(int key, t_mrt *mrt)
{
	if (mrt->scn.sel_light == NULL)
		return (FALSE);
	if (key == K_MINUS || key == K_PLUS || (key >= K_LEFT && key <= K_UP))
		return (light_traslation(key, mrt));
	if (key == K_B || key == K_V)
		return (light_bright(key, mrt));
	return (FALSE);
}
