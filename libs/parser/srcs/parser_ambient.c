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

#include "parse.h"

void	inp_ambient(t_mrt *mrt)
{
	if (mrt->scn.parsed == TRUE)
		msg_error_parsing("Ambient light should be declared just once", mrt);
	mrt->scn.bright = ft_atolf(mrt->tab[AMB_LIGHT]);
	if (!check_range(mrt->scn.bright, 0, 1))
		msg_error_parsing("Ambient light ratio out of range", mrt);
	mrt->scn.amb_rgb = get_color(mrt->tab[AMB_COLOR], mrt);
	mrt->scn.bgr = 0x202020;
	mrt->scn.parsed = TRUE;
}
