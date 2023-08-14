/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 23:06:00 by mporras-          #+#    #+#             */
/*   Updated: 2023/08/13 23:06:02 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

static inline void	axis_informator(int key)
{
	if (key == K_X)
		ft_putstr_fd("[X axis]", STDOUT_FILENO);
	if (key == K_Y)
		ft_putstr_fd("[Y axis]", STDOUT_FILENO);
	if (key == K_Z)
		ft_putstr_fd("[Z axis]", STDOUT_FILENO);
}

static inline void	handler_informator(int key)
{
	if (key == K_S)
		ft_putstr_fd("[Sphere]", STDOUT_FILENO);
	else if (key == K_C)
		ft_putstr_fd("[Cylinder]", STDOUT_FILENO);
	else if (key == K_E)
		ft_putstr_fd("[Camera]", STDOUT_FILENO);
	else if (key == K_D)
		ft_putstr_fd("[Radius]", STDOUT_FILENO);
	else if (key == K_H)
		ft_putstr_fd("[Height", STDOUT_FILENO);
	else if (key == K_T)
		ft_putstr_fd("[Translate]", STDOUT_FILENO);
	else if (key == K_X || key == K_Y || key == K_Z)
		axis_informator(key);
	else if (key == K_O)
		ft_putstr_fd("[Orbit]", STDOUT_FILENO);
	else if (key == K_L)
		ft_putstr_fd("[Lights]", STDOUT_FILENO);
	else if (key == K_R)
		ft_putstr_fd("[Rotation]", STDOUT_FILENO);
	else if (key == K_N)
		ft_putstr_fd("[Nearest Object]", STDOUT_FILENO);
}

static inline int	action_handler(t_mrt *mrt, int key)
{
	t_hook	changes;

	if (mrt->behaviour == 0 || mrt->behaviour > 256)
		return (FALSE);
	changes = mrt->hooks[mrt->behaviour];
	if (changes)
		changes(mrt, key);
	return (TRUE);
}

static inline int	change_camera(t_mrt *mrt)
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

int	keys_handler(int key, t_mrt *mrt)
{
	if (key == K_ESC)
		exit(clear_all(mrt, 0, mrt->clean_window, mrt->clean_image));
	if (key == K_SPACE)
		return (change_camera(mrt));
	if (key == K_UP || key == K_DOWN)
		return (action_handler(mrt, key));
	if (key == K_Q)
	{
		ft_putstr_fd("[-BEHAVIOUR RESET-]\n", STDOUT_FILENO);
		mrt->key_press = 0;
		mrt->behaviour = 0;
		return (FALSE);
	}
	if (mrt->key_press == 3)
		return (FALSE);
	mrt->behaviour += key;
	mrt->key_press++;
	handler_informator(key);
	if (mrt->key_press == 3)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (TRUE);
}
