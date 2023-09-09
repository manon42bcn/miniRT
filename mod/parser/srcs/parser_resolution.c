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

#ifdef BONUS

/**
 * @brief Parse the resolution data in bonus mode.
 *
 * Parse the screen resolution values from the input data.
 * This function ensures that the resolution is declared only once.
 * After parsing, it calculates the aspect ratio of the scene.
 *
 * @param mrt The main structure containing all parsed data.
 */
void	inp_resolution(t_mrt *mrt)
{
	if (mrt->scn.res_init == TRUE)
		msg_error_parsing("Resolution should be declared once", mrt);
	mrt->scn.w_x = ft_atoi(mrt->tab[RES_PARSE_X]);
	mrt->scn.w_y = ft_atoi(mrt->tab[RES_PARSE_Y]);
	mrt->scn.ratio = (double)mrt->scn.w_x / (double)mrt->scn.w_y;
	mrt->scn.res_init = TRUE;
}

#else

/**
 * @brief Displays an error when trying to parse resolution in
 * the mandatory version.
 *
 * In the mandatory version, the resolution parsing is not supported.
 * Hence, it raises an error if a user tries to define a resolution.
 *
 * @param mrt The main structure containing all parsed data.
 */
void	inp_resolution(t_mrt *mrt)
{
	msg_error_parsing("Resolution is not supported at mandatory version", mrt);
}

#endif