/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 22:28:44 by mporras-          #+#    #+#             */
/*   Updated: 2023/07/02 22:28:46 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	mlx_starter(t_mrt *mrt)
{
	t_cmr	*node;

	node = mrt->cmr;
	while (node)
	{
		node->img_ptr = mlx_new_image(mrt->mlx, mrt->scn.w_x, mrt->scn.w_y);
		node->addr = (int *)mlx_get_data_addr(node->img_ptr,
				&node->bpp, &node->size, &node->endian);
		node = node->next;
	}
}

int	to_win(t_mrt *mrt)
{
	if (mrt->to_img == TO_RENDER)
	{
		if (mrt->window == TRUE)
			render_main(mrt);
		mlx_put_image_to_window(mrt->mlx, mrt->mlx_win,
			mrt->cmr->img_ptr, 0, 0);
		mrt->to_img = RENDERED;
		mrt->window = TRUE;
	}
	return (TRUE);
}

int	window_handler(t_mrt *mrt)
{
	exit(clear_all(mrt, 0, &mlx_clear_window, &mlx_destroy_image));
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


void handler_informator(int key)
{
	(void)key;
	if (key == K_S)
		ft_putstr_fd(" Sphere ", STDOUT_FILENO);
	if (key == K_C)
		ft_putstr_fd(" Cylinder ", STDOUT_FILENO);
	if (key == K_E)
		ft_putstr_fd(" Camera ", STDOUT_FILENO);
	if (key == K_D)
		ft_putstr_fd(" Radius ", STDOUT_FILENO);
	if (key == K_H)
		ft_putstr_fd(" Height", STDOUT_FILENO);
	if (key == K_T)
		ft_putstr_fd(" Translate ", STDOUT_FILENO);
	if (key == K_X)
		ft_putstr_fd(" X axis ", STDOUT_FILENO);
	if (key == K_Y)
		ft_putstr_fd(" Y axis ", STDOUT_FILENO);
	if (key == K_Z)
		ft_putstr_fd(" Z axis ", STDOUT_FILENO);
	if (key == K_O)
		ft_putstr_fd(" Orbit ", STDOUT_FILENO);
	if (key == K_A)
		ft_putstr_fd(" AROUND CLOSED ", STDOUT_FILENO);
	if (key == K_ENTER)
		ft_putstr_fd(" INTRO ", STDOUT_FILENO);
	if (key == K_L)
		ft_putstr_fd(" LIGHTS ", STDOUT_FILENO);
	if (key == K_R)
		ft_putstr_fd(" ROTATION ", STDOUT_FILENO);
	if (key == K_N)
		ft_putstr_fd(" NEAREST OBJECT ", STDOUT_FILENO);
	if (key == K_O)
		ft_putstr_fd(" ORBIT ", STDOUT_FILENO);
}

//TODO: camera and objects rotation
int	keys_handler(int key, t_mrt *mrt)
{
//	printf("%d key\n", key);
	if (key == K_ESC)
		exit(clear_all(mrt, 0, &mlx_clear_window, &mlx_destroy_image));
	if (key == K_SPACE)
		return (change_camera(mrt));
	if (mrt->key_press == 0)
		mrt->behaviour = 0;
	if (mrt->key_press == 3 || key == K_Q)
	{
		ft_putstr_fd(" BEHAVIOUR RESET TO 0\n", STDOUT_FILENO);
		mrt->key_press = 0;
		return (FALSE);
	}
	mrt->behaviour += key;
	mrt->key_press++;
	printf("%d beha %d press %d key\n", mrt->behaviour, mrt->key_press, key);
	handler_informator(key);
	if (mrt->key_press == 3)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		mrt->key_press = 0;
	}
	return (TRUE);
}
