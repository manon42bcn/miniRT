/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:29:07 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 22:01:02 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	inp_triangle(t_mrt *mrt)
{
	mrt->obj = object_builder(TRIANGLE, mrt->obj);
	mrt->obj->elm.trg.v1 = get_v3d(mrt->tab[TRG_VERTEX_1],
			V3D_COOR);
	mrt->obj->elm.trg.v2 = get_v3d(mrt->tab[TRG_VERTEX_2],
			V3D_COOR);
	mrt->obj->elm.trg.v3 = get_v3d(mrt->tab[TRG_VERTEX_3],
			V3D_COOR);
	mrt->obj->elm.trg.orient = ft_cross_v3d(
			ft_minus_v3d(mrt->obj->elm.trg.v3, mrt->obj->elm.trg.v1),
			ft_minus_v3d(mrt->obj->elm.trg.v2, mrt->obj->elm.trg.v1)
			);
	get_common(mrt, TRG_VERTEX_3, "Triangle");
	mrt->obj->normal = mrt->obj->elm.trg.orient;
	mrt->obj->solver = triangle_solver;
}
