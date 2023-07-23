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

#include "parse.h"

static inline t_bool	check_light_color(t_mrt *mrt, int last)
{
	int	len;

	len = 0;
	while (mrt->tab[++last])
		len++;
	if (len == 0)
		return (FALSE);
	return (TRUE);
}

void	inp_light(t_mrt *mrt)
{
	mrt->scn.light = light_builder(mrt->scn.light);
	mrt->scn.light->origin = get_v3d(mrt, mrt->tab[LIGHT_CENTRE], V3D_COOR);
	mrt->scn.light->bright = ft_atolf(mrt->tab[LIGHT_RATIO]);
	if (!check_range(mrt->scn.light->bright, 0, 1))
		msg_error_parsing("Light ratio out of range", mrt);
	if (check_light_color(mrt, LIGHT_RATIO))
		mrt->scn.light->color = get_color(mrt->tab[LIGHT_COLOR], mrt);
}
