/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:03:40 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 21:57:12 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	inp_cube(t_mrt *mrt)
{
	mrt->obj = object_builder(CUBE, mrt->obj);
	mrt->obj->elm.sq.centre = get_v3d(mrt, mrt->tab[CUBE_CENTRE], V3D_COOR);
	mrt->obj->elm.sq.side = ft_atolf(mrt->tab[CUBE_SIDE]);
	if (!check_range(mrt->obj->elm.sq.side, 0, INFINITY))
		msg_error_parsing("Cube side out of range", mrt);
	get_common(mrt, CUBE_SIDE, "Cube");
}
