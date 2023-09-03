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

/**
 * @brief Subtract a real number from each component of a 3D vector.
 *
 * @param vec The 3D vector.
 * @param real The real number to subtract.
 * @return The resulting vector after subtraction.
 */
t_v3d	ft_subs_real(t_v3d vec, double real)
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
t_v3d	ft_plus_real(t_v3d vec, double real)
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
double	ft_distance_v3d(t_v3d a, t_v3d b)
{
	return (sqrt(((b.x - a.x) * (b.x - a.x))
			+ ((b.y - a.y) * (b.y - a.y))
			+ ((b.z - a.z) * (b.z - a.z))));
}

/**
 * @brief Rotate a 3D vector by a given angle around the X-axis.
 *
 * @param vec The 3D vector to be rotated.
 * @param angle The angle (in degrees) by which the vector is to be rotated.
 * @return The rotated vector.
 */
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

/**
 * @brief Check if a given 3D vector is normalized
 * (its components lie between -1 and 1).
 *
 * @param v Pointer to the 3D vector.
 * @return TRUE if the vector is normalized, FALSE otherwise.
 */
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
