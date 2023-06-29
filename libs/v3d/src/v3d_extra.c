/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_extra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:12:03 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/08 00:07:11 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <v3d.h>

t_v3d	ft_subs_real(t_v3d vec, double real)
{
	return ((t_v3d){vec.x - real, vec.y - real, vec.z - real});
}

t_v3d	ft_plus_real(t_v3d vec, double real)
{
	return ((t_v3d){vec.x + real, vec.y + real, vec.z + real});
}

double	ft_distance_v3d(t_v3d a, t_v3d b)
{
	return (sqrt(((b.x - a.x) * (b.x - a.x))
		+ ((b.y - a.y) * (b.y - a.y))
			+ ((b.z - a.z) * (b.z - a.z))));
}

t_v3d	ft_rotate_v3d(t_v3d vec, double angle)
{
	t_v3d	row1;
	t_v3d	row2;
	t_v3d	row3;
	t_v3d	rotated;
	double	rad_angle;

	rad_angle = angle * M_PI / 180;
	row1 = (t_v3d){1, 0, 0};
	row2 = (t_v3d){0, cos(rad_angle), -sin(rad_angle)};
	row3 = (t_v3d){0, sin(rad_angle), cos(rad_angle)};
	rotated.x = vec.x * row1.x + vec.y * row1.y + vec.z * row1.z;
	rotated.y = vec.x * row2.x + vec.y * row2.y + vec.z * row2.z;
	rotated.z = vec.x * row3.x + vec.y * row3.y + vec.z * row3.z;
	return (rotated);
}

t_bool	ft_is_normal_v3d(t_v3d *v)
{
	if (v->x < -1.0 && v->x > 1.0)
		return (FALSE);
	if (v->y < -1.0 && v->y > 1.0)
		return (FALSE);
	if (v->z < -1.0 && v->z > 1.0)
		return (FALSE);
	return (TRUE);
}
