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

#include "minirt.h"


//void	sphere_minus_translate(t_mrt *mrt, int key)
//{
//	t_obj	*node;
//
//	node = mrt->obj;
//	while (key == K_U && node)
//	{
//		if (node->type == SPHERE)
//			node->elm.sph.centre.x -= 0.1f;
//		node = node->next;
//	}
//	while (key == K_J && node)
//	{
//		if (node->type == SPHERE)
//			node->elm.sph.centre.y -= 0.1f;
//		node = node->next;
//	}
//	while (key == K_M && node)
//	{
//		if (node->type == SPHERE)
//			node->elm.sph.centre.z -= 0.1f;
//		node = node->next;
//	}
//}

void	sphere_diam(t_mrt *mrt, int x, int y, int mouse_code)
{
	t_obj	*node;

	(void)x;
	y = 0;
	node = mrt->obj;
	while (node)
	{
		if (mouse_code == RIGHT_CLICK && node->type == SPHERE)
			node->elm.sph.radius *= 1.1f;
		else if (mouse_code == LEFT_CLICK && node->type == SPHERE
			&& (node->elm.sph.radius / 1.1f > 0))
			node->elm.sph.radius /= 1.1f;
		if (node->type == SPHERE)
			y++;
		node = node->next;
	}
	if (y > 0)
		mrt->to_img = TO_RENDER;
}
