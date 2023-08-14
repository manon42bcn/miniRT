/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_hooks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 23:12:33 by mporras-          #+#    #+#             */
/*   Updated: 2023/08/07 23:12:35 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

void	cylinder_y_translation(t_mrt *mrt, int key_dir)
{
	t_obj	*node;

	node = mrt->obj;
	while (node)
	{
		if (node->type == CYLINDER && key_dir == K_DOWN)
			node->elm.cyl.centre.y += 0.1f;
		if (node->type == CYLINDER && key_dir == K_UP)
			node->elm.cyl.centre.y -= 0.1f;
		if (node->type == CYLINDER)
		{
			node->position = ft_copy_v3d(&node->elm.cyl.centre);
			mrt->to_img = TO_RENDER;
		}
		node = node->next;
	}
}

void	cylinder_x_translation(t_mrt *mrt, int key_dir)
{
	t_obj	*node;

	node = mrt->obj;
	while (node)
	{
		if (node->type == CYLINDER && key_dir == K_DOWN)
			node->elm.cyl.centre.x += 0.1f;
		if (node->type == CYLINDER && key_dir == K_UP)
			node->elm.cyl.centre.x -= 0.1f;
		if (node->type == CYLINDER)
		{
			node->position = ft_copy_v3d(&node->elm.cyl.centre);
			mrt->to_img = TO_RENDER;
		}
		node = node->next;
	}
}

void	cylinder_z_translation(t_mrt *mrt, int key_dir)
{
	t_obj	*node;

	node = mrt->obj;
	while (node)
	{
		if (node->type == CYLINDER && key_dir == K_DOWN)
			node->elm.cyl.centre.z += 0.1f;
		if (node->type == CYLINDER && key_dir == K_UP)
			node->elm.cyl.centre.z -= 0.1f;
		if (node->type == CYLINDER)
		{
			node->position = ft_copy_v3d(&node->elm.cyl.centre);
			mrt->to_img = TO_RENDER;
		}
		node = node->next;
	}
}

void	cylinder_diam(t_mrt *mrt, int key_dir)
{
	t_obj	*node;

	node = mrt->obj;
	while (node)
	{
		if (key_dir == K_UP && node->type == CYLINDER)
			node->elm.cyl.radius *= 1.1f;
		else if (key_dir == K_DOWN && node->type == CYLINDER
			&& (node->elm.cyl.radius / 1.1f > 0))
			node->elm.cyl.radius /= 1.1f;
		if (node->type == CYLINDER)
			mrt->to_img = TO_RENDER;
		node = node->next;
	}
}

void	cylinder_height(t_mrt *mrt, int key_dir)
{
	t_obj	*node;

	node = mrt->obj;
	while (node)
	{
		if (key_dir == K_UP && node->type == CYLINDER)
			node->elm.cyl.height *= 1.1f;
		else if (key_dir == K_DOWN && node->type == CYLINDER
			&& (node->elm.cyl.height / 1.1f > 0))
			node->elm.cyl.height /= 1.1f;
		if (node->type == CYLINDER)
			mrt->to_img = TO_RENDER;
		node = node->next;
	}
}
