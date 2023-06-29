/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_arithmetics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:02:14 by mporras-          #+#    #+#             */
/*   Updated: 2023/04/05 12:02:18 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <v3d.h>

t_v3d	ft_plus_v3d(t_v3d a, t_v3d b)
{
	return ((t_v3d){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_v3d	ft_minus_v3d(t_v3d a, t_v3d b)
{
	return ((t_v3d){a.x - b.x, a.y - b.y, a.z - b.z});
}

double	ft_dot_v3d(t_v3d a, t_v3d b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

t_v3d	ft_scalar_v3d(double scalar, t_v3d vec)
{
	return ((t_v3d){vec.x * scalar, vec.y * scalar, vec.z * scalar});
}

t_v3d	ft_div_v3d(t_v3d vec, double real)
{
	return ((t_v3d){vec.x / real, vec.y / real, vec.z / real});
}
