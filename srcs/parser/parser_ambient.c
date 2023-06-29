/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:06:04 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 17:21:49 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	inp_ambient(t_mrt *mrt)
{
	static t_bool	parsed = FALSE;

	if (parsed == TRUE)
		msg_error_exit("Ambient light founded more then one time");
	mrt->scn.bright = ft_atolf(mrt->tab[AMB_LIGHT]);
	check_range(mrt->scn.bright, 0, 1, "Ambient light");
	mrt->scn.amb_rgb = get_color(mrt->tab[AMB_COLOR], "Ambient light");
	mrt->scn.bgr = 0x202020;
	parsed = TRUE;
}
