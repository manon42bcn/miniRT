/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:13:26 by mporras-          #+#    #+#             */
/*   Updated: 2023/10/12 13:44:51 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Compute the normal vector at the point of intersection for a box.
 *
 * This function calculates the normal vector at the point where a ray
 * intersects a box. Since a box consists of multiple flat faces, the function
 * derives the normal based on which face of the box is hit by the ray.
 * The orientation of the normal might be inverted depending on the direction
 * of the incoming ray.
 *
 * The function utilizes the `hit` index stored in the `box` structure of the
 * object to determine which face was hit and subsequently, retrieves the
 * precomputed normal orientation for that face.
 *
 * @param dir The direction of the incoming ray.
 * @param hit The point of intersection on the box (unused in the function).
 * @param inter Pointer to the intersection structure containing details about
 * the intersection.
 *
 * @return The normal vector at the point of intersection.
 */
t_v3d	box_normal(t_v3d dir, t_v3d hit, t_inter *inter)
{
	(void)hit;
	if (ft_cos_v3d(dir, inter->obj->elm.box.faces[inter->obj->elm.box.hit].orient) > 0)
		return (ft_scalar_v3d(-1, inter->obj->elm.box.faces[inter->obj->elm.box.hit].orient));
	else
		return (inter->obj->elm.box.faces[inter->obj->elm.box.hit].orient);
}

/**
 * @brief Computes the intersection of a ray with a box by checking against
 * its faces.
 *
 * This function uses rectangle_solver to get the hit point of each face.
 *
 * @param origin Starting point of the ray.
 * @param dir Direction vector of the ray.
 * @param obj Object containing box details.
 * @return The distance from the ray origin to the intersection,
 * or INFINITY if no hit.
 */
double	box_solver(t_v3d origin, t_v3d dir, t_obj *obj)
{
	double	evl;
	t_obj	tmp;
	double	t;
	int		face;

	evl = INFINITY;
	t = INFINITY;
	face = 0;
	while (face++ < 6)
	{
		tmp.elm.rc = obj->elm.box.faces[face];
		t = rectangle_solver(origin, dir, &tmp);
		if (t < evl && t > 0)
		{
			evl = t;
			obj->elm.box.hit = face;
		}
	}
	return (evl);
}
