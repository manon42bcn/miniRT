/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:28:35 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 17:21:52 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	inp_resolution(t_mrt *mrt)
{
	if (mrt->scn.parsed == TRUE)
		parse_error("Ambient light should be declared just once");
	mrt->scn.parsed = TRUE;
	mrt->scn.w_x = ft_atoi(mrt->tab[RES_PARSE_X]);
	mrt->scn.w_y = ft_atoi(mrt->tab[RES_PARSE_Y]);
	mrt->scn.ratio = (double)mrt->scn.w_x / (double)mrt->scn.w_y;
}
