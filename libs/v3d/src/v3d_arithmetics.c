/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_arithmetics.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:02:14 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/08 11:48:06 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <v3d.h>

/**
 * @brief Adds two 3D vectors component-wise.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The result of the addition as a new vector.
 */
t_v3d	ft_plus_v3d(t_v3d a, t_v3d b)
{
	return ((t_v3d){a.x + b.x, a.y + b.y, a.z + b.z});
}

/**
 * @brief Subtracts two 3D vectors component-wise.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The result of the subtraction as a new vector.
 */
t_v3d	ft_minus_v3d(t_v3d a, t_v3d b)
{
	return ((t_v3d){a.x - b.x, a.y - b.y, a.z - b.z});
}

/**
 * @brief Computes the dot product of two 3D vectors.
 *
 * @param a The first vector.
 * @param b The second vector.
 * @return The dot product of the two vectors.
 */
t_dec	ft_dot_v3d(t_v3d a, t_v3d b)
{
	return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

/**
 * @brief Multiplies a 3D vector by a scalar value.
 *
 * @param scalar The scalar value to multiply with.
 * @param vec The vector to be multiplied.
 * @return The result of the scalar multiplication as a new vector.
 */
t_v3d	ft_scalar_v3d(t_dec scalar, t_v3d vec)
{
	t_v3d	rst;

	if (vec.x == 0.0F || scalar == 0.0F)
		rst.x = 0.0F;
	else
		rst.x = vec.x * scalar;
	if (vec.y == 0.0F || scalar == 0.0F)
		rst.y = 0.0F;
	else
		rst.y = vec.y * scalar;
	if (vec.z == 0.0F || scalar == 0.0F)
		rst.z = 0.0F;
	else
		rst.z = vec.z * scalar;
	return (rst);
}

/**
 * @brief Divides each component of a 3D vector by a real number.
 *
 * @param vec The vector whose components are to be divided.
 * @param real The real number by which each component of the vector
 * is to be divided.
 * @return The result of the division as a new vector.
 */
t_v3d	ft_div_v3d(t_v3d vec, t_dec	real)
{
	return ((t_v3d){vec.x / real, vec.y / real, vec.z / real});
}
