/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:44:32 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 22:00:44 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	inp_square(t_mrt *mrt)
{
	mrt->obj = object_builder(SQUARE, mrt->obj);
	mrt->obj->elm.sq.centre = get_v3d(mrt->tab[SQR_CENTRE], V3D_COOR);
	mrt->obj->elm.sq.orient = get_v3d(mrt->tab[SQR_ORIENT], V3D_NORM);
	mrt->obj->elm.sq.side = ft_atolf(mrt->tab[SQR_SIDE]);
	check_range(mrt->obj->elm.sq.side, 0, INFINITY, "Square side");
	get_common(mrt, SQR_SIDE, "Square");
	mrt->obj->solver = square_solver;
	mrt->obj->normal = mrt->obj->elm.sq.orient;
}
