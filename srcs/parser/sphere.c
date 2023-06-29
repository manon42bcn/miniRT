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

#include "minirt.h"

void	inp_sphere(t_mrt *mrt)
{
	mrt->obj = object_builder(SPHERE, mrt->obj);
	mrt->obj->elm.sph.centre = get_v3d(mrt->tab[SPH_CENTRE],
			V3D_COOR, "Sphere");
	mrt->obj->elm.sph.radius = ft_atolf(mrt->tab[SPH_DIAM]) / 2.0f;
	check_range(mrt->obj->elm.sph.radius, 0, INFINITY, "Sphere radius");
	get_common(mrt, SPH_DIAM, "Sphere");
	mrt->obj->solver = sphere_solver;
}
