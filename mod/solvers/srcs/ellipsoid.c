/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:30:53 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/24 22:43:13 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Calculate the normal vector for a hit point on an ellipsoid surface.
 *
 * This function computes the normal vector for a point of intersection on an
 * ellipsoid surface based on the incoming ray direction and the ellipsoid's
 * properties.
 *
 * @param dir The direction vector of the incoming ray (unused in this version).
 * @param hit The point of intersection on the ellipsoid surface.
 * @param inter Pointer to the intersection data structure.
 *
 * @return The normal vector at the point of intersection.
 */

t_v3d	ft_div_v3d_by_vec(t_v3d vec, t_v3d vec2)
{
	return ((t_v3d){vec.x / (vec2.x * vec2.x), vec.y / (vec2.y * vec2.y), vec.z / (vec2.z * vec2.z)});
}

t_v3d	ellipsoid_normal(t_v3d dir, t_v3d hit, t_inter *inter)
{
	t_v3d hit_to_centre;
	//double	length;
	t_v3d	normal;
	t_v3d	rad;

	(void)dir;
	rad = (t_v3d){inter->obj->elm.elp.rx, inter->obj->elm.elp.ry, inter->obj->elm.elp.rz};
	hit_to_centre = ft_minus_v3d(hit, inter->obj->elm.elp.centre);
	//length = ft_length_v3d(hit_to_centre);
	normal = ft_div_v3d(hit_to_centre, ft_length_v3d(hit_to_centre));
	normal = ft_div_v3d_by_vec(normal, rad);
	return (normal);


//	t_v3d normal;
//	t_v3d hit_to_centre;
////	t_ellip *ellip = &inter->obj->elm.elp;
//	t_ellip el = inter->obj->elm.elp;
//
//	(void)dir;
//	hit_to_centre = ft_minus_v3d(hit, el.centre);
//	normal.x = hit_to_centre.x / sqrt(el.rx * el.rx * hit.x * hit.x + el.ry * el.ry * hit.y * hit.y + el.rz * el.rz * hit.z * hit.z);
//	normal.y = hit_to_centre.y / sqrt(el.rx * el.rx * hit.x * hit.x + el.ry * el.ry * hit.y * hit.y + el.rz * el.rz * hit.z * hit.z);
//	normal.z = hit_to_centre.z / sqrt(el.rx * el.rx * hit.x * hit.x + el.ry * el.ry * hit.y * hit.y + el.rz * el.rz * hit.z * hit.z);
//
////	inter->normal = normal;
//
//	return (normal);

//	t_v3d	local_normal;
//	t_v3d	global_normal;
//	t_v3d	local;
//	t_ellip	elp;
//	t_v3d	orientation;
//
//	(void)dir;
//	local = ft_minus_v3d(hit, inter->obj->elm.elp.centre);
//	elp = inter->obj->elm.elp;
//
//	// Calculate the local normal vector
//	local_normal.x = 2.0 * local.x / (elp.rx * elp.rx);
//	local_normal.y = 2.0 * local.y / (elp.ry * elp.ry);
//	local_normal.z = 2.0 * local.z / (elp.rz * elp.rz);
//
//	// Extract the ellipsoid's orientation vector
//	orientation = elp.dir;
//
//	// Transform the local normal vector into global coordinates using the orientation matrix
//	global_normal = ft_rotate_normal_v3d(local_normal, orientation);
//
//	return (ft_normal_v3d(global_normal));
}

//t_v3d	ellipsoid_normal(t_v3d dir, t_v3d hit, t_inter *inter)
//{
//	t_v3d	normal;
//	t_v3d	rst;
//	t_v3d	local;
//	t_ellip	elp;
//
//	(void)dir;
//	local = ft_minus_v3d(hit, inter->obj->elm.elp.centre);
//	elp = inter->obj->elm.elp;
//	normal.x = 2.0 * local.x / (elp.rx * elp.rx);
//	normal.y = 2.0 * local.y / (elp.ry * elp.ry);
//	normal.z = 2.0 * local.z / (elp.rz * elp.rz);
//	rst.x = normal.x * elp.dir.x + normal.y * elp.dirx.x
//		+ normal.z * elp.diry.x;
//	rst.y = normal.x * elp.dir.y + normal.y * elp.dirx.y
//		+ normal.z * elp.diry.y;
//	rst.z = normal.x * elp.dir.z + normal.y * elp.dirx.z
//		+ normal.z * elp.diry.z;
//	return (ft_normal_v3d(rst));
//}

//t_v3d	ellipsoid_normal(t_v3d dir, t_v3d hit, t_inter *inter)
//{
//	t_v3d	normal;
//	t_v3d	local;
//
//	(void)dir;
//	local = ft_minus_v3d(hit, inter->obj->elm.elp.centre);
//	normal.x = 2.0 * local.x / (inter->obj->elm.elp.rx
//			* inter->obj->elm.elp.rx);
//	normal.y = 2.0 * local.y / (inter->obj->elm.elp.ry
//			* inter->obj->elm.elp.ry);
//	normal.z = 2.0 * local.z / (inter->obj->elm.elp.rz
//			* inter->obj->elm.elp.rz);
//	return (ft_normal_v3d(normal));
//}

/**
 * @brief Calculate the coefficients for the quadratic equation representing an
 * ellipsoid.
 *
 * This function computes the coefficients of the quadratic equation that
 * represents the intersection of a ray with an ellipsoid. The equation is used
 * to solve for the intersection points.
 *
 * @param coef An array to store the coefficients (E_A, E_B, E_C) of the
 * quadratic equation.
 * @param elp The ellipsoid structure representing the ellipsoid.
 * @param origin The origin point of the ray.
 * @param dir The direction vector of the ray.
 */
static void	ellipsoid_quad(double *coef, t_ellip elp, t_v3d origin, t_v3d dir)
{
	t_v3d	oc;
	t_v3d	loc_dir;
	t_v3d	loc_oc;

	oc = ft_minus_v3d(origin, elp.centre);
	loc_dir = (t_v3d){ft_dot_v3d(dir, elp.dir) / elp.rx,
		ft_dot_v3d(dir, elp.dirx) / elp.ry,
		ft_dot_v3d(dir, elp.diry) / elp.rz};
	coef[E_A] = (loc_dir.x * loc_dir.x) + (loc_dir.y * loc_dir.y)
		+ (loc_dir.z * loc_dir.z);
	loc_oc = (t_v3d){ft_dot_v3d(oc, elp.dir) / elp.rx,
		ft_dot_v3d(oc, elp.dirx) / elp.ry,
		ft_dot_v3d(oc, elp.diry) / elp.rz};
	coef[E_B] = 2 * ((loc_oc.x * loc_dir.x) + (loc_oc.y * loc_dir.y)
			+ (loc_oc.z * loc_dir.z));
	coef[E_C] = (loc_oc.x * loc_oc.x) + (loc_oc.y * loc_oc.y)
		+ (loc_oc.z * loc_oc.z) - 1;
}

//static void	ellipsoid_quad(double *coef, t_ellip elp, t_v3d origin, t_v3d dir_one)
//{
//	t_v3d	oc;
//	t_v3d	dir;
//
//	oc = ft_minus_v3d(origin, elp.centre);
////	dir = ft_proj_v3d(ft_proj_v3d(dir_one, elp.dir), elp.dir);
//	dir = dir_one;
//	coef[E_A] = (dir.x * dir.x / (elp.rx * elp.rx))
//		+ (dir.y * dir.y / (elp.ry * elp.ry))
//		+ (dir.z * dir.z / (elp.rz * elp.rz));
//	coef[E_B] = 2 * (oc.x * dir.x / (elp.rx * elp.rx))
//		+ 2 * (oc.y * dir.y / (elp.ry * elp.ry))
//		+ 2 * (oc.z * dir.z / (elp.rz * elp.rz));
//	coef[E_C] = (oc.x * oc.x / (elp.rx * elp.rx))
//		+ (oc.y * oc.y / (elp.ry * elp.ry))
//		+ (oc.z * oc.z / (elp.rz * elp.rz)) - 1;
//}

/**
 * @brief Calculate the intersection point of a ray with an ellipsoid.
 *
 * This function finds the intersection point of a ray with an ellipsoid and
 * returns the distance from the ray origin to the intersection point. It uses
 * quadratic equations to solve for the intersection.
 *
 * @param origin The origin point of the ray.
 * @param dir The direction vector of the ray.
 * @param elp The ellipsoid structure representing the ellipsoid.
 *
 * @return The distance from the ray origin to the intersection point or INFINITY
 * if there is no intersection with the ellipsoid.
 */
double	ellipsoid_solver(t_v3d origin, t_v3d dir, t_ellip elp)
{
	double	coef[3];
	double	t[2];

	ellipsoid_quad(&coef[0], elp, origin, dir);
	if (!quadratic(&coef[0], &t[0]))
		return (INFINITY);
	if (t[0] > 0)
		return (t[0]);
	if (t[1] > 0)
		return (t[1]);
	return (INFINITY);
}
