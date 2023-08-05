/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 00:00:47 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 21:53:17 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	inp_sphere(t_mrt *mrt)
{
	t_obj	*current;

	current = mrt->obj;
	mrt->obj = object_builder(SPHERE, mrt->obj);
	mrt->obj->elm.sph.centre = get_v3d(mrt, mrt->tab[SPH_CENTRE],
			V3D_COOR);
	mrt->obj->elm.sph.radius = ft_atolf(mrt->tab[SPH_DIAM]) / 2.0f;
	if (!check_range(mrt->obj->elm.sph.radius, 0, INFINITY))
		msg_error_parsing("Sphere radius out of range", mrt);
	get_common(mrt, SPH_DIAM, "Sphere");
	mrt->obj->position = ft_copy_v3d(&mrt->obj->elm.sph.centre);
	mrt->obj->next = current;
}
