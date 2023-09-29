/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:05:01 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/27 15:05:03 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <v3d.h>

/**
 * @brief Get a vector that is approximately perpendicular to the given vector.
 *
 * This function computes a vector that is approximately perpendicular to the
 * input vector by using the cross product. It checks the cross product with
 * identity vectors along the x, y, and z axes and returns the one with the
 * highest magnitude after normalization.
 *
 * @param vec The input vector to which we want to find a perpendicular vector.
 *
 * @return A normalized vector that is approximately perpendicular to
 * the input vector.
 */
t_v3d	ft_perp_v3d(t_v3d vec)
{
	t_v3d	perp[3];

	perp[X_C] = ft_cross_v3d(vec, ft_v3d_identity(X_C));
	perp[Y_C] = ft_cross_v3d(vec, ft_v3d_identity(Y_C));
	perp[Z_C] = ft_cross_v3d(vec, ft_v3d_identity(Z_C));
	if (ft_mag_v3d(perp[X_C]) > ft_mag_v3d(perp[Y_C])
		&& ft_mag_v3d(perp[X_C]) > ft_mag_v3d(perp[Z_C]))
		return (ft_normal_v3d(perp[X_C]));
	else if (ft_mag_v3d(perp[Y_C]) > ft_mag_v3d(perp[Z_C]))
		return (ft_normal_v3d(perp[Y_C]));
	return (ft_normal_v3d(perp[Z_C]));
}
