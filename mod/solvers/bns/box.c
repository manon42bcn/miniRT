/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:13:26 by mporras-          #+#    #+#             */
/*   Updated: 2023/10/12 13:44:51 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

t_v3d	box_normal(t_v3d dir, t_v3d hit, t_inter *inter)
{
	(void)hit;
	if (ft_cos_v3d(dir, inter->obj->elm.box.faces[inter->face].orient) > 0)
		return (ft_scalar_v3d(-1, inter->obj->elm.box.faces[inter->face].orient));
	else
		return (inter->obj->elm.box.faces[inter->face].orient);
}

double	box_solver(t_v3d origin, t_v3d dir, t_box box, t_inter *inter)
{
	double		evl;
	t_rectangle	tmp;
	double		t;
	int			face;

	evl = INFINITY;
	t = INFINITY;
	face = 0;
	while (face++ < 6)
	{
		tmp = box.faces[face];
		t = rectangle_solver(origin, dir, tmp);
		if (t < evl && t > 0)
		{
			evl = t;
			box.hit = face;
		}
	}
	inter->face = box.hit;
	return (evl);
}
