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

/**
 * @brief Rotates a 3D vector around the X-axis.
 *
 * This function performs a rotation transformation on a given 3D vector
 * around the X-axis by the specified angle.
 *
 * @param vec The 3D vector to be rotated.
 * @param angle The angle of rotation in radians.
 *
 * @return t_v3d The rotated vector.
 */
t_v3d	ft_rot_v3d_x(t_v3d vec, double angle)
{
	t_v3d	row1;
	t_v3d	row2;
	t_v3d	row3;
	t_v3d	rotated;

	row1 = (t_v3d){1, 0, 0};
	row2 = (t_v3d){0, cos(angle), -sin(angle)};
	row3 = (t_v3d){0, sin(angle), cos(angle)};
	rotated.x = vec.x * row1.x + vec.y * row1.y + vec.z * row1.z;
	rotated.y = vec.x * row2.x + vec.y * row2.y + vec.z * row2.z;
	rotated.z = vec.x * row3.x + vec.y * row3.y + vec.z * row3.z;
	return (rotated);
}

/**
 * @brief Rotates a 3D vector around the Y-axis.
 *
 * This function performs a rotation transformation on a given 3D vector
 * around the Y-axis by the specified angle.
 *
 * @param vec The 3D vector to be rotated.
 * @param angle The angle of rotation in radians.
 *
 * @return t_v3d The rotated vector.
 */
t_v3d	ft_rot_v3d_y(t_v3d vec, double angle)
{
	t_v3d	row1;
	t_v3d	row2;
	t_v3d	row3;
	t_v3d	rotated;

	row1 = (t_v3d){cos(angle), 0, sin(angle)};
	row2 = (t_v3d){0, 1, 0};
	row3 = (t_v3d){-sin(angle), 0, cos(angle)};
	rotated.x = vec.x * row1.x + vec.y * row1.y + vec.z * row1.z;
	rotated.y = vec.x * row2.x + vec.y * row2.y + vec.z * row2.z;
	rotated.z = vec.x * row3.x + vec.y * row3.y + vec.z * row3.z;
	return (rotated);
}

/**
 * @brief Rotates a 3D vector around the Z-axis.
 *
 * This function performs a rotation transformation on a given 3D vector
 * around the Z-axis by the specified angle.
 *
 * @param vec The 3D vector to be rotated.
 * @param angle The angle of rotation in radians.
 *
 * @return t_v3d The rotated vector.
 */
t_v3d	ft_rot_v3d_z(t_v3d vec, double angle)
{
	t_v3d	row1;
	t_v3d	row2;
	t_v3d	row3;
	t_v3d	rotated;

	row1 = (t_v3d){cos(angle), -sin(angle), 0};
	row2 = (t_v3d){sin(angle), cos(angle), 0};
	row3 = (t_v3d){0, 0, 1};
	rotated.x = vec.x * row1.x + vec.y * row1.y + vec.z * row1.z;
	rotated.y = vec.x * row2.x + vec.y * row2.y + vec.z * row2.z;
	rotated.z = vec.x * row3.x + vec.y * row3.y + vec.z * row3.z;
	return (rotated);
}
