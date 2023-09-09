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
 * @brief Initializes the cube's base normals and related values.
 *
 * This function sets up the fundamental directions for a cube's faces,
 * and also sets the cube's center and side based on the provided object's
 * attributes.
 *
 * @param cube Pointer to a cube structure which will be filled with base values.
 * @param obj The cube object which provides basic attributes for setup.
 */
static void	cube_base_values(t_cube *cube, t_obj *obj)
{
	cube->normal[0] = (t_v3d){1, 0, 0};
	cube->normal[1] = (t_v3d){-1, 0, 0};
	cube->normal[2] = (t_v3d){0, 1, 0};
	cube->normal[3] = (t_v3d){0, -1, 0};
	cube->normal[4] = (t_v3d){0, 0, 1};
	cube->normal[5] = (t_v3d){0, 0, -1};
	cube->center = obj->elm.sq.centre;
	cube->sq.elm.sq.side = obj->elm.sq.side;
}

/**
 * @brief Determines the intersection between a ray and a cube.
 *
 * This function checks the intersection between a ray and each face of
 * the cube. The closest intersection point (if any) is returned.
 * The normal at the intersection point is also updated for the object.
 *
 * @param origin Origin of the ray.
 * @param dir Direction of the ray.
 * @param obj The cube object.
 * @return Distance from the ray's origin to the closest intersection point.
 *         Returns INFINITY if there's no intersection.
 */
double	cube_solver(t_v3d origin, t_v3d dir, t_obj *obj)
{
	t_cube		cube;
	t_v3d		cl_normal;
	double		cl_inter;
	double		inter;
	int			i;

	cube_base_values(&cube, obj);
	cl_inter = INFINITY;
	i = 0;
	while (i < 6)
	{
		cube.sq.elm.sq.centre = ft_plus_v3d(cube.center,
				ft_scalar_v3d(obj->elm.sq.side / 2, cube.normal[i]));
		cube.sq.normal = cube.normal[i];
		inter = square_solver(origin, dir, &(cube.sq));
		if (inter > EPSILON && inter < cl_inter)
		{
			cl_inter = inter;
			cl_normal = cube.sq.normal;
		}
		i++;
	}
	obj->normal = cl_normal;
	return (cl_inter);
}
