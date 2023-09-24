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
//
///**
// * @brief Initializes the cube's base normals and related values.
// *
// * This function sets up the fundamental directions for a cube's faces,
// * and also sets the cube's center and side based on the provided object's
// * attributes.
// *
// * @param cube Pointer to a cube structure which will be filled with base values.
// * @param obj The cube object which provides basic attributes for setup.
// */
//static void	cube_base_values(t_cube *cube, t_obj *obj)
//{
//	cube->normal[0] = (t_v3d){1, 0, 0};
//	cube->normal[1] = (t_v3d){-1, 0, 0};
//	cube->normal[2] = (t_v3d){0, 1, 0};
//	cube->normal[3] = (t_v3d){0, -1, 0};
//	cube->normal[4] = (t_v3d){0, 0, 1};
//	cube->normal[5] = (t_v3d){0, 0, -1};
//	cube->center = obj->elm.sq.centre;
//	cube->sq.elm.sq.side = obj->elm.sq.side;
//}
//
///**
// * @brief Determines the intersection between a ray and a cube.
// *
// * This function checks the intersection between a ray and each face of
// * the cube. The closest intersection point (if any) is returned.
// * The normal at the intersection point is also updated for the object.
// *
// * @param origin Origin of the ray.
// * @param dir Direction of the ray.
// * @param obj The cube object.
// * @return Distance from the ray's origin to the closest intersection point.
// *         Returns INFINITY if there's no intersection.
// */
//double	cube_solver(t_v3d origin, t_v3d dir, t_obj *obj)
//{
//	t_cube		cube;
//	t_v3d		cl_normal;
//	double		cl_inter;
//	double		inter;
//	int			i;
//
//	cube_base_values(&cube, obj);
//	cl_inter = INFINITY;
//	i = 0;
//	while (i < 6)
//	{
//		cube.sq.elm.sq.centre = ft_plus_v3d(cube.center,
//				ft_scalar_v3d(obj->elm.sq.side / 2, cube.normal[i]));
//		cube.sq.normal = cube.normal[i];
//		inter = square_solver(origin, dir, &(cube.sq));
//		if (inter > EPSILON && inter < cl_inter)
//		{
//			cl_inter = inter;
//			cl_normal = cube.sq.normal;
//		}
//		i++;
//	}
//	obj->normal = cl_normal;
//	return (cl_inter);
//}

void swap(double *a, double *b) {
	double temp = *a;
	*a = *b;
	*b = temp;
}

double box_solver(t_v3d origin, t_v3d dir, t_obj *box) {
	double tmin, tmax, tymin, tymax, tzmin, tzmax;

	t_v3d inv_dir = {1 / dir.x, 1 / dir.y, 1 / dir.z};

	if (inv_dir.x >= 0) {
		tmin = (box->elm.box.min.x - origin.x) * inv_dir.x;
		tmax = (box->elm.box.max.x - origin.x) * inv_dir.x;
	} else {
		tmin = (box->elm.box.max.x - origin.x) * inv_dir.x;
		tmax = (box->elm.box.min.x - origin.x) * inv_dir.x;
	}
	if (inv_dir.y >= 0) {
		tymin = (box->elm.box.min.y - origin.y) * inv_dir.y;
		tymax = (box->elm.box.max.y - origin.y) * inv_dir.y;
	} else {
		tymin = (box->elm.box.max.y - origin.y) * inv_dir.y;
		tymax = (box->elm.box.min.y - origin.y) * inv_dir.y;
	}

	if ((tmin > tymax) || (tymin > tmax))
		return INFINITY;

	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;

	if (inv_dir.z >= 0) {
		tzmin = (box->elm.box.min.z - origin.z) * inv_dir.z;
		tzmax = (box->elm.box.max.z - origin.z) * inv_dir.z;
	} else {
		tzmin = (box->elm.box.max.z - origin.z) * inv_dir.z;
		tzmax = (box->elm.box.min.z - origin.z) * inv_dir.z;
	}

	if ((tmin > tzmax) || (tzmin > tmax))
		return INFINITY;

	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;

	if (tmin < 0) {
		if (tmax < 0)
			return INFINITY;
		else
			tmin = tmax;
	}

	t_v3d hitted = ft_plus_v3d(origin, ft_scalar_v3d(tmin, dir));

	int r = 0, g = 0, b = 0;
	if (fabs(hitted.x - box->elm.box.min.x) < EPSILON) {
		r = 255;b = 255;  // Rojo para cara mínima x
	} else if (fabs(hitted.x - box->elm.box.max.x) < EPSILON) {
		g = 255;  // Verde para cara máxima x
	} else if (fabs(hitted.y - box->elm.box.min.y) < EPSILON) {
		b = 255;  // Azul para cara mínima y
	} else if (fabs(hitted.y - box->elm.box.max.y) < EPSILON) {
		r = 255; g = 255; // Amarillo para cara máxima y
	} else if (fabs(hitted.z - box->elm.box.min.z) < EPSILON) {
		r = 255; // Magenta para cara mínima z
	} else if (fabs(hitted.z - box->elm.box.max.z) < EPSILON) {
		g = 255; b = 255; // Cian para cara máxima z
	}

	box->color = (r << 16) | (g << 8) | b;

	return tmin;
}
