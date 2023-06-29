/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_algebra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:06:51 by mporras-          #+#    #+#             */
/*   Updated: 2023/04/05 12:06:56 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <v3d.h>

double	ft_length_v3d(t_v3d vec)
{
	return ((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

double	ft_mag_v3d(t_v3d vector)
{
	return (sqrt(ft_length_v3d(vector)));
}

double	ft_cos_v3d(t_v3d a, t_v3d b)
{
	return (ft_dot_v3d(a, b) / (ft_mag_v3d(a) * ft_mag_v3d(b)));
}

double	ft_sin_v3d(t_v3d a, t_v3d b)
{
	double	cos;

	cos = ft_cos_v3d(a, b);
	return (sqrt(1 - (cos * cos)));
}

t_v3d	ft_cross_v3d(t_v3d a, t_v3d b)
{
	return ((t_v3d){(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z),
		(a.x * b.y) - (a.y * b.x)});
}
