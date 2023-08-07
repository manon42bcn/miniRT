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
//	mlx_png_file_to_image(mrt->mlx, "icon.png", &mrt->scn.w_x, &mrt->scn.w_y);
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



void	cylinder_radius(t_mrt *mrt, int key)
{
	t_obj	*node;

	node = mrt->obj;
	while (key == K_F && node)
	{
		if (node->type == CYLINDER)
			node->elm.cyl.radius *= 1.1f;
		node = node->next;
	}
	while (key == K_R && node)
	{
		if (node->type == CYLINDER && (node->elm.cyl.radius / 1.1f > 0))
			node->elm.cyl.radius /= 1.1f;
		node = node->next;
	}
}

void	cylinder_height(t_mrt *mrt, int key)
{
	t_obj	*node;

	node = mrt->obj;
	while (key == K_G && node)
	{
		if (node->type == CYLINDER)
			node->elm.cyl.height *= 1.1f;
		node = node->next;
	}
	while (key == K_T && node)
	{
		if (node->type == CYLINDER && (node->elm.cyl.height / 1.1f > 0))
			node->elm.cyl.height /= 1.1f;
		node = node->next;
	}
}

void	sphere_plus_translate(t_mrt *mrt, int key)
{
	t_obj	*node;

	node = mrt->obj;
	while (key == K_Y && node)
	{
		if (node->type == SPHERE)
			node->elm.sph.centre.x += 0.1f;
		node = node->next;
	}
	while (key == K_H && node)
	{
		if (node->type == SPHERE)
			node->elm.sph.centre.y += 0.1f;
		node = node->next;
	}
	while (key == K_N && node)
	{
		if (node->type == SPHERE)
			node->elm.sph.centre.z += 0.1f;
		node = node->next;
	}
}

void	sphere_minus_translate(t_mrt *mrt, int key)
{
	t_obj	*node;

	node = mrt->obj;
	while (key == K_U && node)
	{
		if (node->type == SPHERE)
			node->elm.sph.centre.x -= 0.1f;
		node = node->next;
	}
	while (key == K_J && node)
	{
		if (node->type == SPHERE)
			node->elm.sph.centre.y -= 0.1f;
		node = node->next;
	}
	while (key == K_M && node)
	{
		if (node->type == SPHERE)
			node->elm.sph.centre.z -= 0.1f;
		node = node->next;
	}
}

void handler_informator(int key)
{
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
}

//TODO: camera and objects rotation
int	keys_handler(int key, t_mrt *mrt)
{
	printf("%d key\n", key);
	if (key == K_ESC)
		exit(clear_all(mrt, 0, &mlx_clear_window, &mlx_destroy_image));
	if (key == K_SPACE)
		return (change_camera(mrt));
	if (mrt->key_press == 0)
		mrt->behaviour = 0;
	if (mrt->key_press == 2 || key == K_Q)
	{
		ft_putstr_fd(" BEHAVIOUR RESET TO 0\n", STDOUT_FILENO);
		mrt->key_press = 0;
		return (FALSE);
	}
	mrt->behaviour += key;
	mrt->key_press++;
	handler_informator(key);
	if (mrt->key_press == 2)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		mrt->key_press = 0;
	}
	return (TRUE);
}
