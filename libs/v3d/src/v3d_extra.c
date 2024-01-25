/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_extra.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 13:12:03 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/25 10:50:47 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <v3d.h>

/**
 * @brief Subtract a real number from each component of a 3D vector.
 *
 * @param vec The 3D vector.
 * @param real The real number to subtract.
 * @return The resulting vector after subtraction.
 */
t_v3d	ft_subs_real(t_v3d vec, t_dec real)
{
	return ((t_v3d){vec.x - real, vec.y - real, vec.z - real});
}

/**
 * @brief Add a real number to each component of a 3D vector.
 *
 * @param vec The 3D vector.
 * @param real The real number to add.
 * @return The resulting vector after addition.
 */
t_v3d	ft_plus_real(t_v3d vec, t_dec real)
{
	return ((t_v3d){vec.x + real, vec.y + real, vec.z + real});
}

/**
 * @brief Calculate the distance between two 3D vectors.
 *
 * @param a The first 3D vector.
 * @param b The second 3D vector.
 * @return The distance between the two vectors.
 */
t_dec	ft_distance_v3d(t_v3d a, t_v3d b)
{
	return ((t_dec)sqrt(((b.x - a.x) * (b.x - a.x))
			+ ((b.y - a.y) * (b.y - a.y))
			+ ((b.z - a.z) * (b.z - a.z))));
}

/**
 * @brief Check if a given 3D vector is normalized
 * (its components magnitude is equal to 1). Some magnitudes
 * can be approximate 1.
 *
 * @param v Pointer to the 3D vector.
 * @return TRUE if the vector is normalized, FALSE otherwise.
 */
t_bool	ft_is_normal_v3d(t_v3d *v)
{
	t_dec	mag;

	mag = ft_mag_v3d(*v);
	if (mag >= 0.99F && mag <= 1.01F)
		return (TRUE);
	return (FALSE);
}
