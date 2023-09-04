/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 16:44:12 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/23 17:12:04 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Initializes the pyramid's base normals and related values.
 *
 * This function sets up the fundamental directions for a pyramid's faces
 * and vertices, and also calculates the center of the pyramid's base and
 * side length based on the provided object's attributes.
 *
 * @param pyr Pointer to a pyramid structure which will be filled with
 * base values.
 * @param obj The pyramid object which provides basic attributes for setup.
 */
static void	pyramid_base_values(t_pyr *pyr, t_obj *obj)
{
	int	i;

	pyr->normal[0] = (t_v3d){1, 0, 0};
	pyr->normal[1] = (t_v3d){0, 0, 1};
	pyr->normal[2] = (t_v3d){-1, 0, 0};
	pyr->normal[3] = (t_v3d){0, 0, -1};
	pyr->normal[4] = (t_v3d){1, 0, 0};
	pyr->tr_center = ft_plus_v3d(obj->elm.sq.centre,
			ft_scalar_v3d(obj->elm.sq.side, (t_v3d){0, 1, 0}));
	pyr->sq.elm.sq.side = obj->elm.sq.side;
	pyr->sq.elm.sq.centre = obj->elm.sq.centre;
	pyr->sq.normal = (t_v3d){0, -1, 0};
	i = 0;
	while (i < 4)
	{
		pyr->corner[i] = ft_plus_v3d(obj->elm.sq.centre,
				ft_scalar_v3d(obj->elm.sq.side / 2, pyr->normal[i]));
		pyr->corner[i] = ft_plus_v3d(pyr->corner[i],
				ft_scalar_v3d(obj->elm.sq.side / 2, pyr->normal[i + 1]));
		i++;
	}
	pyr->trg.elm.trg.v3 = pyr->tr_center;
}

/**
 * @brief Determines the second vertex of a pyramid's face triangle.
 *
 * Based on the index, this function returns either the provided corner
 * or the first vertex, determining the layout of the pyramid's triangle face.
 *
 * @param i Index of the face being processed.
 * @param corner The provided corner vertex.
 * @param first The first vertex.
 * @return The second vertex.
 */
static inline t_v3d	second_vertex(int i, t_v3d corner, t_v3d first)
{
	if (i < 3)
		return (corner);
	return (first);
}

/**
 * @brief Determines the intersection between a ray and a pyramid.
 *
 * This function checks the intersection between a ray and each face
 * of the pyramid. The closest intersection point (if any) is returned.
 * The normal at the intersection point is also updated for the object.
 *
 * @param origin Origin of the ray.
 * @param dir Direction of the ray.
 * @param obj The pyramid object.
 * @return Distance from the ray's origin to the closest intersection point.
 *         Returns INFINITY if there's no intersection.
 */
double	pyramid_solver(t_v3d origin, t_v3d dir, t_obj *obj)
{
	t_pyr		pyr;
	t_v3d		cl_normal;
	int			i;

	pyramid_base_values(&pyr, obj);
	pyr.closest = INFINITY;
	i = 0;
	while (i < 4)
	{
		pyr.trg.elm.trg.v1 = pyr.corner[i];
		pyr.trg.elm.trg.v2 = second_vertex(i, pyr.corner[i + 1], pyr.corner[0]);
		pyr.trg.normal = ft_cross_v3d(ft_minus_v3d(pyr.trg.elm.trg.v3,
					pyr.trg.elm.trg.v1), ft_minus_v3d(pyr.trg.elm.trg.v2,
					pyr.trg.elm.trg.v1));
		pyr.intersection = triangle_solver(origin, dir, &(pyr.trg));
		if (pyr.intersection > EPSILON && pyr.intersection < pyr.closest)
		{
			pyr.closest = pyr.intersection;
			cl_normal = pyr.trg.normal;
		}
		i++;
	}
	obj->normal = cl_normal;
	return (pyr.intersection);
}
