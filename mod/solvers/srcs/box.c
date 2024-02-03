/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:13:26 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/15 00:35:21 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Calculate the normal vector for a hit point on a box surface.
 *
 * This function computes the normal vector for a point of intersection on a box
 * surface based on the incoming ray direction and the box's orientation.
 *
 * @param dir The direction vector of the incoming ray.
 * @param hit The point of intersection on the box surface (unused in this
 * version).
 * @param inter Pointer to the intersection data structure.
 *
 * @return The normal vector at the point of intersection.
 */
t_v3d	box_normal(t_v3d dir, t_v3d hit, t_inter *inter)
{
	(void)hit;
	if (ft_cos_v3d(dir, inter->obj->elm.box.faces[inter->face].orient) > 0)
		return (ft_scalar_v3d(-1,
				inter->obj->elm.box.faces[inter->face].orient));
	else
		return (inter->obj->elm.box.faces[inter->face].orient);
}

/**
 * @brief Calculate the intersection point of a ray with a box.
 *
 * This function finds the intersection point of a ray with a box and returns the
 * distance from the ray origin to the intersection point. It also updates the
 * intersection data structure with the index of the intersected box face.
 *
 * @param origin The origin point of the ray.
 * @param dir The direction vector of the ray.
 * @param box The box structure representing the box.
 * @param inter Pointer to the intersection data structure to be updated.
 *
 * @return The distance from the ray origin to the intersection point or INFINITY
 * if there is no intersection with the box.
 */
t_dec	box_solver(t_v3d origin, t_v3d dir, t_box box, t_inter *inter)
{
	t_dec		evl;
	t_rectangle	tmp;
	t_dec		t;
	int			face;

	evl = INFINITY;
	t = INFINITY;
	face = -1;
	while (++face <= 5)
	{
		tmp = box.faces[face];
		t = rectangle_solver(origin, dir, tmp);
		if (t < evl && t > 0)
		{
			evl = t;
			box.hit = face;
		}
	}
	inter->face = box.hit;
	return (evl);
}
