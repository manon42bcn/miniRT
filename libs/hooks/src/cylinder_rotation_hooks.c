/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_rotation_hooks.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 19:29:40 by mporras-          #+#    #+#             */
/*   Updated: 2023/08/11 19:29:43 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

void	cylinder_rotation_x(t_mrt *mrt, int key_dir)
{
	t_obj	*node;

	node = mrt->obj;
	while (node)
	{
		if (key_dir == K_UP && node->type == CYLINDER)
			node->angle += RAD_ANGLE;
		else if (key_dir == K_DOWN && node->type == CYLINDER)
			node->angle -= RAD_ANGLE;
		if (node->type == CYLINDER)
		{
			node->elm.cyl.dir = ft_normal_v3d(
					rotate_x(node->elm.cyl.dir, node->angle));
			mrt->to_img = TO_RENDER;
		}
		node = node->next;
	}
}

void	cylinder_rotation_y(t_mrt *mrt, int key_dir)
{
	t_obj	*node;

	node = mrt->obj;
	while (node)
	{
		if (key_dir == K_UP && node->type == CYLINDER)
			node->angle += RAD_ANGLE;
		else if (key_dir == K_DOWN && node->type == CYLINDER)
			node->angle -= RAD_ANGLE;
		if (node->type == CYLINDER)
		{
			node->elm.cyl.dir = ft_normal_v3d(
					rotate_y(node->elm.cyl.dir, node->angle));
			mrt->to_img = TO_RENDER;
		}
		node = node->next;
	}
}

void	cylinder_rotation_z(t_mrt *mrt, int key_dir)
{
	t_obj	*node;

	node = mrt->obj;
	while (node)
	{
		if (key_dir == K_UP && node->type == CYLINDER)
			node->angle += RAD_ANGLE;
		else if (key_dir == K_DOWN && node->type == CYLINDER)
			node->angle -= RAD_ANGLE;
		if (node->type == CYLINDER)
		{
			node->elm.cyl.dir = ft_normal_v3d(
					rotate_z(node->elm.cyl.dir, node->angle));
			mrt->to_img = TO_RENDER;
		}
		node = node->next;
	}
}
