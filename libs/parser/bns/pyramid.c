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

#include "parse.h"

void	inp_pyramid(t_mrt *mrt)
{
	mrt->obj = object_builder(PYRAMID, mrt->obj);
	mrt->obj->elm.sq.centre = get_v3d(mrt, mrt->tab[PYR_CENTRE],
			V3D_COOR);
	mrt->obj->elm.sq.side = ft_atolf(mrt->tab[PYR_SIDE]);
	if (!check_range(mrt->obj->elm.sq.side, 0, INFINITY))
		msg_error_parsing("Pyramid side out of range", mrt);
	get_common(mrt, PYR_SIDE, "Cube");
}
