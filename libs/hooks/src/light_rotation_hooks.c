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

void	light_rotation_x(t_mrt *mrt, int x, int y, int mouse_code)
{
	t_light	*node;
	t_v3d	old;

	(void)x;
	(void)y;
	node = mrt->scn.light;
	while (node)
	{
		if (mouse_code == RIGHT_CLICK)
			node->angle += RAD_ANGLE;
		else if (mouse_code == LEFT_CLICK)
			node->angle -= RAD_ANGLE;
		old = ft_copy_v3d(&node->origin);
		node->origin.x = old.x;
		node->origin.y = old.y * cos(node->angle) - old.z * sin(node->angle);
		node->origin.z = old.y * sin(node->angle) + old.z * cos(node->angle);
		mrt->to_img = TO_RENDER;
		node = node->next;
	}
}

void	light_rotation_y(t_mrt *mrt, int x, int y, int mouse_code)
{
	t_light	*node;
	t_v3d	old;

	(void)x;
	(void)y;
	node = mrt->scn.light;
	while (node)
	{
		if (mouse_code == RIGHT_CLICK)
			node->angle += RAD_ANGLE;
		else if (mouse_code == LEFT_CLICK)
			node->angle -= RAD_ANGLE;
		old = ft_copy_v3d(&node->origin);
		node->origin.x = old.x * cos(node->angle) + old.z * sin(node->angle);
		node->origin.z = -old.x * sin(node->angle) + old.z * cos(node->angle);
		mrt->to_img = TO_RENDER;
		node = node->next;
	}
}

void	light_rotation_z(t_mrt *mrt, int x, int y, int mouse_code)
{
	t_light	*node;
	t_v3d	old;

	(void)x;
	(void)y;
	node = mrt->scn.light;
	while (node)
	{
		if (mouse_code == RIGHT_CLICK)
			node->angle += RAD_ANGLE;
		else if (mouse_code == LEFT_CLICK)
			node->angle -= RAD_ANGLE;
		old = ft_copy_v3d(&node->origin);
		node->origin.x = old.x * cos(node->angle) - old.y * sin(node->angle);
		node->origin.y = old.x * sin(node->angle) + old.y * cos(node->angle);
		mrt->to_img = TO_RENDER;
		node = node->next;
	}
}
