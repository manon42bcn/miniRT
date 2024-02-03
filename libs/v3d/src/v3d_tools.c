/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 15:05:01 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/25 10:51:11 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <v3d.h>
#include <stdio.h>
/**
 * @brief Rotate a 3D vector around an arbitrary axis by a specified angle.
 *
 * This function rotates a 3D vector around an arbitrary axis by a
 * specified angle using the Rodrigue's rotation formula.
 *
 * @param vec The 3D vector to be rotated.
 * @param ax The axis of rotation.
 * @param angle The angle of rotation in radians.
 * @return The rotated 3D vector.
 */
t_v3d	ft_rot_v3d(t_v3d vec, int axis, t_dec angle)
{
	t_dec	c_the;
	t_dec	s_the;
	t_dec	one;
	t_v3d	ax;
	t_v3d	mtx[3];

	c_the = (t_dec)cos(angle);
	s_the = (t_dec)sin(angle);
	ax = ft_v3d_identity(axis);
	one = 1.0F - c_the;
	mtx[0] = (t_v3d){c_the + one * ax.x * ax.x,
		one * ax.x * ax.y - s_the * ax.z,
		one * ax.x * ax.z + s_the * ax.y};
	mtx[1] = (t_v3d){one * ax.y * ax.x + s_the * ax.z,
		c_the + one * ax.y * ax.y,
		one * ax.y * ax.z - s_the * ax.x};
	mtx[2] = (t_v3d){one * ax.z * ax.x - s_the * ax.y,
		one * ax.z * ax.y + s_the * ax.x,
		c_the + one * ax.z * ax.z};
	return ((t_v3d){mtx[0].x * vec.x + mtx[0].y * vec.y + mtx[0].z * vec.z,
		mtx[1].x * vec.x + mtx[1].y * vec.y + mtx[1].z * vec.z,
		mtx[2].x * vec.x + mtx[2].y * vec.y + mtx[2].z * vec.z});
}

/**
 * @brief Get a vector that is approximately perpendicular to the given vector.
 *
 * This function computes a vector that is approximately perpendicular to the
 * input vector by using the cross product. It checks the cross product with
 * identity vectors along the x, y, and z axes and returns the one that is not
 * null (evaluating from x to z).
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
 * @brief Check if a 3D vector is an identity vector along any of the
 * coordinate axes.
 *
 * This function checks if a given 3D vector is identical to one of the
 * standard unit vectors along the coordinate axes
 * (i.e., (1, 0, 0), (0, 1, 0), or (0, 0, 1)).
 *
 * @param vec The 3D vector to be checked.
 * @return axis if the vector is an identity vector along any
 * coordinate axis, NO_MATCH (-1) otherwise.
 */
t_bool	ft_is_idt_v3d(t_v3d vec)
{
	static const t_v3d	idt[3] = {
		(t_v3d){1.0F, 0.0F, 0.0F},
		(t_v3d){0.0F, 1.0F, 0.0F},
		(t_v3d){0.0F, 0.0F, 1.0F}};
	int					axis;
	t_v3d				cmp;

	axis = -1;
	while (++axis < 3)
	{
		cmp = idt[axis];
		if (vec.x == cmp.x && vec.y == cmp.y && vec.z == cmp.z)
			return (axis);
	}
	return (NO_MATCH);
}
