/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 16:52:11 by mporras-          #+#    #+#             */
/*   Updated: 2023/08/05 16:52:12 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
//
//static inline void	moveCamera(t_cmr *camera, double angle, t_v3d center, double radius)
//{
//	if (camera->rotate_over == ROTATE_X)
//	{
//		camera->position.x = center.x;
//		camera->position.y = center.y + radius * cos(angle);
//		camera->position.z = center.z + radius * sin(angle);
//	}
//	if (camera->rotate_over == ROTATE_Y)
//	{
//		camera->position.x = center.x + radius * cos(angle);
//		camera->position.y = center.y;
//		camera->position.z = center.z + radius * sin(angle);
//	}
//	if (camera->rotate_over == ROTATE_Z)
//	{
//		camera->position.x = center.x + radius * cos(angle);
//		camera->position.y = center.y + radius * sin(angle);
//		camera->position.z = center.z;
//	}
//	camera->dir = ft_normal_v3d(ft_minus_v3d(center, camera->position));
//}
//
//int	mouse_handler(int mouse_code, int x, int y, t_mrt *mrt)
//{
//	static double	angle = 0;
//
//	printf("%d %d\n", x, y);
////	t_v3d camaraPosition = mrt->cmr->position;
////	t_v3d cameraDirection = mrt->cmr->dir;
//
////	t_v3d lookAtPoint = ft_plus_v3d(camaraPosition, cameraDirection);
//	if (mouse_code == RIGHT_CLICK)
//		angle += RAD_ANGLE;
//	else
//		angle -= RAD_ANGLE;
////	double rad = sqrt(mrt->cmr->position.x * mrt->cmr->position.x + mrt->cmr->position.y * mrt->cmr->position.y + mrt->cmr->position.z * mrt->cmr->position.z);
////	printf("%f distance?\n", rad);
//	moveCamera(mrt->cmr, angle, (t_v3d){0, 0, 0}, 25);
//	mrt->to_img = TO_RENDER;
//	return (TRUE);
//}
