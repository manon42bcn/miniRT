/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 23:08:34 by mporras-          #+#    #+#             */
/*   Updated: 2023/08/14 23:08:35 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

/**
 * @brief Rotate a 3D vector around the X-axis.
 *
 * This function applies a rotation transformation to the input vector
 * around the X-axis by the specified angle.
 *
 * @param old The original vector to be rotated.
 * @param angle The rotation angle in radians.
 * @return t_v3d The rotated vector.
 */
t_v3d	rotate_x(t_v3d old, double angle)
{
	t_v3d	rst;

	rst.x = old.x;
	rst.y = old.y * cos(angle) - old.z * sin(angle);
	rst.z = old.y * sin(angle) + old.z * cos(angle);
	return (rst);
}

/**
 * @brief Rotate a 3D vector around the Y-axis.
 *
 * This function applies a rotation transformation to the input vector
 * around the Y-axis by the specified angle.
 *
 * @param old The original vector to be rotated.
 * @param angle The rotation angle in radians.
 * @return t_v3d The rotated vector.
 */
t_v3d	rotate_y(t_v3d old, double angle)
{
	t_v3d	rst;

	rst.x = old.x * cos(angle) + old.z * sin(angle);
	rst.y = old.y;
	rst.z = -old.x * sin(angle) + old.z * cos(angle);
	return (rst);
}

/**
 * @brief Rotate a 3D vector around the Z-axis.
 *
 * This function applies a rotation transformation to the input vector
 * around the Z-axis by the specified angle.
 *
 * @param old The original vector to be rotated.
 * @param angle The rotation angle in radians.
 * @return t_v3d The rotated vector.
 */
t_v3d	rotate_z(t_v3d old, double angle)
{
	t_v3d	rst;

	rst.x = old.x * cos(angle) - old.y * sin(angle);
	rst.y = old.x * sin(angle) + old.y * cos(angle);
	rst.z = old.z;
	return (rst);
}
