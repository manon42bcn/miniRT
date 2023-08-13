/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 20:25:53 by mporras-          #+#    #+#             */
/*   Updated: 2023/08/07 20:25:55 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

void	sphere_y_translation(t_mrt *mrt, int x, int y, int mouse_code)
{
	t_obj	*node;

	node = mrt->obj;
	(void)x;
	(void)y;
	while (node)
	{
		if (node->type == SPHERE && mouse_code == LEFT_CLICK)
			node->elm.sph.centre.y += 0.1f;
		if (node->type == SPHERE && mouse_code == RIGHT_CLICK)
			node->elm.sph.centre.y -= 0.1f;
		if (node->type == SPHERE)
		{
			node->position = ft_copy_v3d(&node->elm.sph.centre);
			mrt->to_img = TO_RENDER;
		}
		node = node->next;
	}
}

void	sphere_x_translation(t_mrt *mrt, int x, int y, int mouse_code)
{
	t_obj	*node;

	node = mrt->obj;
	(void)x;
	(void)y;
	while (node)
	{
		if (node->type == SPHERE && mouse_code == LEFT_CLICK)
			node->elm.sph.centre.x += 0.1f;
		if (node->type == SPHERE && mouse_code == RIGHT_CLICK)
			node->elm.sph.centre.x -= 0.1f;
		if (node->type == SPHERE)
		{
			node->position = ft_copy_v3d(&node->elm.sph.centre);
			mrt->to_img = TO_RENDER;
		}
		node = node->next;
	}
}

void	sphere_z_translation(t_mrt *mrt, int x, int y, int mouse_code)
{
	t_obj	*node;

	node = mrt->obj;
	(void)x;
	(void)y;
	while (node)
	{
		if (node->type == SPHERE && mouse_code == LEFT_CLICK)
			node->elm.sph.centre.z += 0.1f;
		if (node->type == SPHERE && mouse_code == RIGHT_CLICK)
			node->elm.sph.centre.z -= 0.1f;
		if (node->type == SPHERE)
		{
			node->position = ft_copy_v3d(&node->elm.sph.centre);
			mrt->to_img = TO_RENDER;
		}
		node = node->next;
	}
}

void	sphere_diam(t_mrt *mrt, int x, int y, int mouse_code)
{
	t_obj	*node;

	(void)x;
	(void)y;
	node = mrt->obj;
	while (node)
	{
		if (mouse_code == RIGHT_CLICK && node->type == SPHERE)
			node->elm.sph.radius *= 1.1f;
		else if (mouse_code == LEFT_CLICK && node->type == SPHERE
			&& (node->elm.sph.radius / 1.1f > 0))
			node->elm.sph.radius /= 1.1f;
		if (node->type == SPHERE)
			mrt->to_img = TO_RENDER;
		node = node->next;
	}
}