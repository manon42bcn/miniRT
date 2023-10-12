/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 00:10:58 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/27 00:11:02 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

t_v3d	common_normal(t_v3d dir, t_v3d hit, t_obj *obj)
{
	(void)hit;
	if (ft_cos_v3d(dir, obj->elm.fig.orient) > 0)
		return (ft_scalar_v3d(-1, obj->elm.fig.orient));
	else
		return (obj->elm.fig.orient);
}

t_v3d	get_normal(t_obj *obj, t_v3d dir, t_v3d hit)
{
	static t_normal	normal[] = {&common_normal, &common_normal,
		&common_normal, &common_normal, &common_normal,
		&box_normal, &common_normal, &cone_normal,
		&common_normal, &common_normal};

	return (normal[obj->type](dir, hit, obj));
}
