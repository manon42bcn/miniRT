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

void mlx_starter(t_mrt *mrt)
{
	t_cmr *node;

	node = mrt->cmr;
	while (node)
	{
		node->img_ptr = mlx_new_image(mrt->mlx, mrt->scn.w_x, mrt->scn.w_y);
		node->addr = (int *)mlx_get_data_addr(node->img_ptr,
				&node->bpp, &node->size, &node->endian);
		node = node->next;
	}
}

int	to_win(t_mrt *mrt) {
	if (mrt->to_img == FALSE)
	{
		if (mrt->window == TRUE)
			render_main(mrt);
		mlx_put_image_to_window(mrt->mlx, mrt->mlx_win,
			mrt->cmr->img_ptr, 0, 0);
		mrt->to_img = TRUE;
		mrt->window = TRUE;
	}
	return (TRUE);
}

int	window_handler(t_mrt *mrt)
{
	exit(clear_all(mrt, 0));
}

static inline void change_camera(t_mrt *mrt)
{
	if (mrt->cmr->next == NULL)
		mrt->cmr = mrt->main_cam;
	else
		mrt->cmr = mrt->cmr->next;
}

void	sphere_diam(t_mrt *mrt, int key)
{
	t_obj	*node;

	node = mrt->obj;
	if (key == K_D)
	{
		while (node)
		{
			if (node->type == SPHERE)
				node->elm.sph.radius *= 1.1f;
			node = node->next;
		}
	}
	else
	{
		while (node)
		{
			if (node->type == SPHERE)
				if (node->elm.sph.radius / 1.1f > 0)
					node->elm.sph.radius /= 1.1f;
			node = node->next;
		}
	}
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

int	keys_handler(int key, t_mrt *mrt)
{
	printf("%d - key\n", key);
	if (key == K_ESC)
		exit(clear_all(mrt, 0));
	else if (key == K_D || key == K_E)
		sphere_diam(mrt, key);
	else if (key == K_F || key == K_R)
		cylinder_radius(mrt, key);
	else if (key == K_G || key == K_T)
		cylinder_height(mrt, key);
	else if (key == K_Y || key == K_H || key == K_N)
		sphere_plus_translate(mrt, key);
	else if (key == K_U || key == K_J || key == K_M)
		sphere_minus_translate(mrt, key);
	else if (key == K_SPACE)
		change_camera(mrt);
	mrt->to_img = FALSE;
	return (to_win(mrt));
}
