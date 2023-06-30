/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:04:12 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 21:59:11 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	inp_cylinder(t_mrt *mrt)
{
	mrt->obj = object_builder(CYLINDER, mrt->obj);
	mrt->obj->elm.cyl.centre = get_v3d(mrt->tab[CYL_CENTRE],
			V3D_COOR);
	mrt->obj->elm.cyl.dir = get_v3d(mrt->tab[CYL_ORIENTATION],
			V3D_NORM);
	mrt->obj->elm.cyl.radius = ft_atolf(mrt->tab[CYL_DIAM]) / 2.0f;
	check_range(mrt->obj->elm.cyl.radius, 0, INFINITY, "Cylinder radius");
	mrt->obj->elm.cyl.height = ft_atolf(mrt->tab[CYL_HEIGHT]);
	check_range(mrt->obj->elm.cyl.height, 0, INFINITY, "Cylinder height");
	get_common(mrt, CYL_HEIGHT, "Cylinder");
	mrt->obj->normal = mrt->obj->elm.cyl.dir;
}
