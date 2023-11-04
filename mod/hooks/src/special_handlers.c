/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 21:49:23 by mporras-          #+#    #+#             */
/*   Updated: 2023/10/24 21:49:28 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

/**
 * @brief Handle the window exit operations.
 *
 * This function is called to safely close the window, ensuring
 * that all resources are appropriately freed.
 *
 * @param mrt The main struct with cleanup routines.
 * @return int Always returns 0.
 */
int	window_handler(t_mrt *mrt)
{
	exit(clear_all(mrt, 0, mrt->clean_window, mrt->clean_image));
}

/**
 * @brief Change the active camera in the scene.
 *
 * This function switches the active camera to the next camera in the
 * linked list. If the currently active camera is the last one in the list,
 * it switches back to the main camera. If there's only one camera
 * (the main one), it does not make any changes.
 *
 * @param mrt Pointer to the main runtime structure containing the
 * application's state, including the current active camera.
 * @return int Returns TRUE if the active camera was successfully switched,
 * otherwise returns FALSE.
 */
int	change_camera(t_mrt *mrt)
{
	if (mrt->cmr->next == NULL && mrt->cmr == mrt->main_cam)
		return (FALSE);
	if (mrt->cmr->next == NULL)
		mrt->cmr = mrt->main_cam;
	else
		mrt->cmr = mrt->cmr->next;
	mrt->to_img = TO_RENDER;
	return (TRUE);
}
