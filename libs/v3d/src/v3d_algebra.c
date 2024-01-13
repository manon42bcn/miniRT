/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_algebra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:06:51 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/08 11:46:00 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <v3d.h>

/**
 * @brief Computes the squared magnitude of a vector.
 *
 * @param vec The input vector.
 * @return The squared magnitude (length) of the vector.
 */
t_dec	ft_length_v3d(t_v3d vec)
{
	return ((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z));
}

/**
 * @brief Computes the magnitude (length) of a vector.
 *
 * @param vector The input vector.
 * @return The magnitude of the vector.
 */
t_dec	ft_mag_v3d(t_v3d vector)
{
	return (sqrt(ft_length_v3d(vector)));
}

/**
 * @brief Computes the cosine of the angle between two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The cosine of the angle between the vectors.
 */
t_dec	ft_cos_v3d(t_v3d a, t_v3d b)
{
	return (ft_dot_v3d(a, b) / (ft_mag_v3d(a) * ft_mag_v3d(b)));
}

/**
 * @brief Computes the sine of the angle between two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The sine of the angle between the vectors.
 */
t_dec	ft_sin_v3d(t_v3d a, t_v3d b)
{
	t_dec	cos;

	cos = ft_cos_v3d(a, b);
	return ((t_dec)sqrt(1.0L - (cos * cos)));
}

/**
 * @brief Computes the cross product of two vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The cross product of the vectors as a new vector.
 */
t_v3d	ft_cross_v3d(t_v3d a, t_v3d b)
{
	return ((t_v3d){(a.y * b.z) - (a.z * b.y),
		(a.z * b.x) - (a.x * b.z),
		(a.x * b.y) - (a.y * b.x)});
}
