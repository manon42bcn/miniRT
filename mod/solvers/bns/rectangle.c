/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:03:22 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/27 19:03:25 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

t_bool is_point_inside_rect(t_v3d point, t_obj *obj)
{
	t_v3d	oc;

	oc = ft_minus_v3d(point, obj->elm.rc.centre);

	// Obtener el vector de referencia usando ft_perp_v3d
	t_v3d reference = ft_perp_v3d(obj->elm.rc.orient);

	t_v3d u = ft_cross_v3d(obj->elm.rc.orient, reference);
	t_v3d v = ft_cross_v3d(obj->elm.rc.orient, u);

	// Proyectar la diferencia en u y v
	double proj_on_u = ft_dot_v3d(oc, u);
	double proj_on_v = ft_dot_v3d(oc, v);

	// Chequear si la proyección está dentro de los límites
	if (fabs(proj_on_u) <= obj->elm.rc.width * 0.5 && fabs(proj_on_v) <= obj->elm.rc.height * 0.5)
		return TRUE;

	return FALSE;
}


double rectangle_solver(t_v3d origin, t_v3d dir, t_obj *obj) {
	double inter_distance;
	t_v3d inter_point;

	inter_distance = plane_hit(origin, dir, obj->elm.rc.centre, obj->normal);
	inter_point = ft_plus_v3d(origin, ft_scalar_v3d(inter_distance, dir));

	if (!is_point_inside_rect(inter_point, obj))
		return INFINITY;

	return inter_distance;
}


