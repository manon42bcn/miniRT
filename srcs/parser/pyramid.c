/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:18:06 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 21:55:25 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	inp_pyramid(t_mrt *mrt)
{
	mrt->obj = object_builder(PYRAMID, mrt->obj);
	mrt->obj->elm.sq.centre = get_v3d(mrt->tab[PYR_CENTRE],
			V3D_COOR, "Pyramid");
	mrt->obj->elm.sq.side = ft_atolf(mrt->tab[PYR_SIDE]);
	check_range(mrt->obj->elm.sq.side, 0, INFINITY, "Pyramid side");
	get_common(mrt, PYR_SIDE, "Cube");
	mrt->obj->solver = pyramid_solver;
}
