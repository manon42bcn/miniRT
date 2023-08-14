/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:08:34 by mporras-          #+#    #+#             */
/*   Updated: 2023/08/14 23:08:35 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

t_v3d	rotate_x(t_v3d old, double angle)
{
	t_v3d	rst;

	rst.x = old.x;
	rst.y = old.y * cos(angle) - old.z * sin(angle);
	rst.z = old.y * sin(angle) + old.z * cos(angle);
	return (rst);
}

t_v3d	rotate_y(t_v3d old, double angle)
{
	t_v3d	rst;

	rst.x = old.x * cos(angle) + old.z * sin(angle);
	rst.y = old.y;
	rst.z = -old.x * sin(angle) + old.z * cos(angle);
	return (rst);
}

t_v3d	rotate_z(t_v3d old, double angle)
{
	t_v3d	rst;

	rst.x = old.x * cos(angle) - old.y * sin(angle);
	rst.y = old.x * sin(angle) + old.y * cos(angle);
	rst.z = old.z;
	return (rst);
}
