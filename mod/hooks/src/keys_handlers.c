/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:44:41 by mporras-          #+#    #+#             */
/*   Updated: 2023/10/24 20:44:43 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

/**
 * @brief Check if the provided key code corresponds to a directional key.
 *
 * This function determines if a key corresponds to directional movements or
 * adjustments. These keys are represented by the arrows (left, right, up, down),
 * plus, and minus.
 *
 * @param key The key code to evaluate.
 * @return t_bool TRUE if the key corresponds to a direction, otherwise FALSE.
 */
static inline t_bool	is_direction(int key)
{
	return (key == K_MINUS || key == K_PLUS
		|| (key >= K_LEFT && key <= K_UP));
}

/**
 * @brief Determine the action to take based on the current mode and
 * key pressed.
 *
 * This function is responsible for calling the appropriate function for
 * a key press depending on the current mode (translation, rotation, etc.).
 * It acts as a dispatcher for the key behavior based on context.
 *
 * @param key The key code that was pressed.
 * @param mrt Main runtime structure containing the application's state.
 * @return int Returns TRUE if an action was taken, otherwise FALSE.
 */
static inline int	key_modes(int key, t_mrt *mrt)
{
	if (mrt->mode == TO_TRANSLATE && is_direction(key))
		return (object_traslation(key, mrt));
	if (mrt->mode == TO_ROTATE && is_direction(key))
		return (object_rotation(key, mrt));
	if (mrt->mode == TO_WIDTH
		&& (key == K_MINUS || key == K_PLUS))
		return (object_width(key, mrt));
	if (mrt->mode == TO_HEIGHT
		&& (key == K_MINUS || key == K_PLUS))
		return (object_height(key, mrt));
	if (mrt->mode == TO_CAMERA && is_direction(key))
		return (cam_rotation(key, mrt));
	if (mrt->mode == TO_LIGHT
		&& (is_direction(key) || key == K_B || key == K_V))
		return (light_behaviour(key, mrt));
	if (mrt->mode == TO_EYE && is_direction(key))
		return (cam_translate(key, mrt));
	return (FALSE);
}

/**
 * @brief Main handler to determine behavior based on a key press.
 *
 * This function serves as the primary input handler for various key
 * presses. It checks if the pressed key corresponds to a special action,
 * then dispatches to key_modes or directly handles mode switching and
 * other operations.
 *
 * @param key The key code that was pressed.
 * @param mrt Main runtime structure containing the application's state.
 * @return int Returns TRUE if an action was taken or a mode was changed,
 * otherwise FALSE.
 */
static inline int	key_behaviour(int key, t_mrt *mrt)
{
	if (mrt->mode != NORMAL
		&& (is_direction(key) || key == K_B || key == K_V))
		return (key_modes(key, mrt));
	if (key == K_Q)
		return (normal_mode(mrt));
	if (key == K_S)
		return (selection_mode(mrt));
	if (key == K_T)
		return (translate_mode(mrt));
	if (key == K_R)
		return (rotation_mode(mrt));
	if (key == K_D)
		return (width_mode(mrt));
	if (key == K_H)
		return (height_mode(mrt));
	if (key == K_C)
		return (camera_rotation_mode(mrt));
	if (key == K_L)
		return (light_mode(mrt));
	if (key == K_E)
		return (camera_translate_mode(mrt));
	return (FALSE);
}

/**
 * @brief Handle the main key events for the application.
 *
 * This function responds to key inputs and triggers the appropriate
 * action based on the key pressed by the user. It handles global keys
 * like exit (ESC) and change camera (SPACE) and defers other specific
 * mode-dependent keys to the `key_behaviour` function.
 *
 * @param key The key code of the pressed key.
 * @param mrt Pointer to the main runtime structure containing the
 * application's state and context, including active mode, cameras, and objects.
 * @return int Returns TRUE if a valid key action was triggered,
 * otherwise returns FALSE.
 */
int	key_main(int key, t_mrt *mrt)
{
	if (key == K_ESC)
		exit(clear_all(mrt, 0, mrt->clean_window, mrt->clean_image));
	if (key == K_SPACE)
		return (change_camera(mrt));
	if (key == K_D || key == K_H || key == K_C || key == K_E
		|| key == K_R || key == K_T || key == K_Q || key == K_L
		|| key == K_S || key == K_B || key == K_V || is_direction(key))
		return (key_behaviour(key, mrt));
	return (FALSE);
}
