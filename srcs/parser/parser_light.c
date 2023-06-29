/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:06:05 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 17:48:03 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	inp_light(t_mrt *mrt)
{
	mrt->scn.light = light_builder(mrt->scn.light);
	mrt->scn.light->origin = get_v3d(mrt->tab[LIGHT_CENTRE], V3D_COOR, "Light");
	mrt->scn.light->bright = ft_atolf(mrt->tab[LIGHT_RATIO]);
	check_range(mrt->scn.light->bright, 0, 1, "Light ratio");
	mrt->scn.light->color = get_color(mrt->tab[LIGHT_COLOR], "Light");
}
