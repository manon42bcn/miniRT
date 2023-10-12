/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:13:26 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/23 17:24:18 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Calculates the normal of the hit face on the box.
 *
 * The function determines the normal vector of the face of the box that was
 * hit. The normal direction is dependent on the direction of the incoming ray.
 *
 * @param dir The direction of the incoming ray.
 * @param hit Unused. To make normal functions standard
 * @param obj Pointer to the object structure, which contains details about
 * the hit box.
 * @return t_v3d structure representing the normal of the hit face.
 */
t_v3d	box_normal(t_v3d dir, t_v3d hit, t_obj *obj)
{
	(void)hit;
	if (ft_cos_v3d(dir, obj->elm.box.faces[obj->elm.box.hit].orient) > 0)
		return (ft_scalar_v3d(-1, obj->elm.box.faces[obj->elm.box.hit].orient));
	else
		return (obj->elm.box.faces[obj->elm.box.hit].orient);
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
