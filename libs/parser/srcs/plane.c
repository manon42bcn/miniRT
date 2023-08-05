/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 00:37:40 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 22:00:18 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	inp_plane(t_mrt *mrt)
{
	mrt->obj = object_builder(PLANE, mrt->obj);
	mrt->obj->elm.pl.centre = get_v3d(mrt, mrt->tab[PLN_CENTRE],
			V3D_COOR);
	mrt->obj->elm.pl.orient = get_v3d(mrt, mrt->tab[PLN_ORIENTATION],
			V3D_NORM);
	get_common(mrt, PLN_ORIENTATION, "Plane");
	mrt->obj->normal = mrt->obj->elm.pl.orient;
	mrt->obj->position = ft_copy_v3d(&mrt->obj->elm.pl.centre);
}
