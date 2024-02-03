/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 12:19:22 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/25 10:51:31 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <v3d.h>

/**
 * @brief Normalize a 3D vector in-place.
 * This function modifies the input vector such that its magnitude becomes 1.
 *
 * @param vec Pointer to the 3D vector to be normalized.
 */
void	ft_normalize_v3d(t_v3d *vec)
{
	t_dec	mag;

	mag = (vec->x * vec->x) + (vec->y * vec->y) + (vec->z * vec->z);
	vec->x /= mag;
	vec->y /= mag;
	vec->z /= mag;
}

/**
 * @brief Return a normalized version of a 3D vector.
 * This function returns a new vector derived from the input vector
 * but with a magnitude of 1.
 *
 * @param vec The 3D vector to be normalized.
 * @return A normalized 3D vector.
 */
t_v3d	ft_normal_v3d(t_v3d vec)
{
	t_dec	mag;

	mag = ft_mag_v3d(vec);
	if (mag != 0.0f)
		return ((t_v3d){vec.x / mag, vec.y / mag, vec.z / mag});
	return (vec);
}

/**
 * @brief Copy the components of a 3D vector to a new vector.
 *
 * @param vec Pointer to the 3D vector to be copied.
 * @return A new vector with the same components as the input vector.
 */
t_v3d	ft_copy_v3d(t_v3d *vec)
{
	return ((t_v3d){vec->x, vec->y, vec->z});
}

/**
 * @brief Create a new 3D vector with specified components.
 *
 * @param x The x-component of the vector.
 * @param y The y-component of the vector.
 * @param z The z-component of the vector.
 * @return A new 3D vector with the specified components.
 */
t_v3d	ft_new_v3d(t_dec x, t_dec y, t_dec z)
{
	return ((t_v3d){x, y, z});
}

/**
 * @brief Return a unit vector along one of the principal axes (X, Y, Z).
 * This function provides a convenient way to get a unit vector
 * along a specified axis.
 *
 * @param axis An integer indicating the desired axis
 * (0 for X, 1 for Y, 2 for Z).
 * @return A unit vector along the specified axis.
 */
t_v3d	ft_v3d_identity(int axis)
{
	static const t_v3d	idt[3] = {
		(t_v3d){1.0F, 0.0F, 0.0F},
		(t_v3d){0.0F, 1.0F, 0.0F},
		(t_v3d){0.0F, 0.0F, 1.0F}};

	return (idt[axis]);
}
