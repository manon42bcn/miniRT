/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_rotation_hooks.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:15:38 by mporras-          #+#    #+#             */
/*   Updated: 2023/08/12 18:15:39 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

void	light_rotation_x(t_mrt *mrt, int x, int y, int key_dir)
{
	t_light	*node;

	(void)x;
	(void)y;
	node = mrt->scn.light;
	while (node)
	{
		if (key_dir == K_UP)
			node->angle += RAD_ANGLE;
		else if (key_dir == K_DOWN)
			node->angle -= RAD_ANGLE;
		node->origin = rotate_x(node->origin, node->angle);
		mrt->to_img = TO_RENDER;
		node = node->next;
	}
}

void	light_rotation_y(t_mrt *mrt, int x, int y, int key_dir)
{
	t_light	*node;

	(void)x;
	(void)y;
	node = mrt->scn.light;
	while (node)
	{
		if (key_dir == K_UP)
			node->angle += RAD_ANGLE;
		else if (key_dir == K_DOWN)
			node->angle -= RAD_ANGLE;
		node->origin = rotate_y(node->origin, node->angle);
		mrt->to_img = TO_RENDER;
		node = node->next;
	}
}

void	light_rotation_z(t_mrt *mrt, int x, int y, int key_dir)
{
	t_light	*node;

	(void)x;
	(void)y;
	node = mrt->scn.light;
	while (node)
	{
		if (key_dir == K_UP)
			node->angle += RAD_ANGLE;
		else if (key_dir == K_DOWN)
			node->angle -= RAD_ANGLE;
		node->origin = rotate_z(node->origin, node->angle);
		mrt->to_img = TO_RENDER;
		node = node->next;
	}
}
