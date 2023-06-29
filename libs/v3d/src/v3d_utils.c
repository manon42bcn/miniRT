/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:19:22 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/07 23:53:53 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <v3d.h>

void	ft_normalize_v3d(t_v3d *vec)
{
	double	mag;

	mag = (vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z);
	vec->x /= mag;
	vec->y /= mag;
	vec->z /= mag;
}

t_v3d	ft_normal_v3d(t_v3d vec)
{
	double	mag;

	mag = ft_mag_v3d(vec);
	return ((t_v3d){vec.x / mag, vec.y / mag, vec.z / mag});
}

t_v3d	ft_copy_v3d(t_v3d *vec)
{
	return ((t_v3d){vec->x, vec->y, vec->z});
}

t_v3d	ft_new_v3d(double x, double y, double z)
{
	return ((t_v3d){x, y, z});
}

t_v3d	ft_v3d_identity(int axis)
{
	static const t_v3d	idt[3] = {
		(t_v3d){1.0, 0.0, 0.0},
		(t_v3d){0.0, 1.0, 0.0},
		(t_v3d){0.0, 0.0, 1.0}};

	return (idt[axis]);
}
