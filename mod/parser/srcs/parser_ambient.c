/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 22:06:04 by mporras-          #+#    #+#             */
/*   Updated: 2024/02/03 18:42:42 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief   Parses and sets the ambient light properties in the scene.
 * This function expects the `mrt` structure to contain valid parsing data,
 * and it initializes the scene's ambient light properties based
 * on the provided data.
 *
 * Like all builders, first check if the data founded at file has the
 * necessary element to build it.
 * @param   mrt  Pointer to the main Ray Tracer structure containing
 * the parsing data.
 *
 * @note    Ambient light should only be declared once in the scene.
 * If it's declared more than once, a parsing error will be raised.
 * The function will also raise parsing errors and terminate if invalid
 * data is detected.
 */
void	inp_ambient(t_mrt *mrt)
{
	if (mrt->scn.parsed == TRUE)
		msg_error_parsing("Ambient light should be declared just once", mrt);
	if (ft_count_tab(mrt->tab) != ELM_AMB)
		msg_error_parsing("Wrong data elements to build ambient", mrt);
	mrt->scn.bright = ft_atolf(mrt->tab[AMB_LIGHT]);
	if (!check_range(mrt->scn.bright, 0, 1))
		msg_error_parsing("Ambient light ratio out of range", mrt);
	mrt->scn.amb_rgb = get_color(mrt->tab[AMB_COLOR], mrt);
	mrt->scn.bgr = ft_rgb_get((t_rgb [3]){0, 0, 0});
	mrt->scn.parsed = TRUE;
}
