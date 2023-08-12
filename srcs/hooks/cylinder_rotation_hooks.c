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

#include "minirt.h"

void	cylinder_rotation_x(t_mrt *mrt, int x, int y, int mouse_code)
{
	t_obj	*node;
	double	old;

	(void)x;
	(void)y;
	node = mrt->obj;
	while (node)
	{
		if (mouse_code == RIGHT_CLICK && node->type == CYLINDER)
			node->angle += RAD_ANGLE;
		else if (mouse_code == LEFT_CLICK && node->type == CYLINDER)
			node->angle -= RAD_ANGLE;
		if (node->type == CYLINDER)
		{
			old = node->elm.cyl.dir.y;
			node->elm.cyl.dir.y = old * cos(node->angle)
				- node->elm.cyl.dir.z * sin(node->angle);
			node->elm.cyl.dir.z = old * sin(node->angle)
				+ node->elm.cyl.dir.z * cos(node->angle);
			node->elm.cyl.dir = ft_normal_v3d(node->elm.cyl.dir);
			mrt->to_img = TO_RENDER;
		}
		node = node->next;
	}
}

void	cylinder_rotation_y(t_mrt *mrt, int x, int y, int mouse_code)
{
	t_obj	*node;
	double	old;

	(void)x;
	(void)y;
	node = mrt->obj;
	while (node)
	{
		if (mouse_code == RIGHT_CLICK && node->type == CYLINDER)
			node->angle += RAD_ANGLE;
		else if (mouse_code == LEFT_CLICK && node->type == CYLINDER)
			node->angle -= RAD_ANGLE;
		if (node->type == CYLINDER)
		{
			old = node->elm.cyl.dir.x;
			node->elm.cyl.dir.x = old * cos(node->angle)
				+ node->elm.cyl.dir.z * sin(node->angle);
			node->elm.cyl.dir.z = -old * sin(node->angle)
				+ node->elm.cyl.dir.z * cos(node->angle);
			node->elm.cyl.dir = ft_normal_v3d(node->elm.cyl.dir);
			mrt->to_img = TO_RENDER;
		}
		node = node->next;
	}
}

void	cylinder_rotation_z(t_mrt *mrt, int x, int y, int mouse_code)
{
	t_obj	*node;
	double	old;

	(void)x;
	(void)y;
	node = mrt->obj;
	while (node)
	{
		if (mouse_code == RIGHT_CLICK && node->type == CYLINDER)
			node->angle += RAD_ANGLE;
		else if (mouse_code == LEFT_CLICK && node->type == CYLINDER)
			node->angle -= RAD_ANGLE;
		if (node->type == CYLINDER)
		{
			old = node->elm.cyl.dir.x;
			node->elm.cyl.dir.x = old * cos(node->angle)
				- node->elm.cyl.dir.y * sin(node->angle);
			node->elm.cyl.dir.y = old * sin(node->angle)
				+ node->elm.cyl.dir.y * cos(node->angle);
			node->elm.cyl.dir = ft_normal_v3d(node->elm.cyl.dir);
			mrt->to_img = TO_RENDER;
		}
		node = node->next;
	}
}
