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

/**
 * @brief Check if there's a specified color for the light.
 *
 * Determine if there are any additional parameters after the light's
 * brightness ratio.
 * If there are, then it's expected to be the light's color.
 *
 * @param mrt The main structure containing all parsed data.
 * @param last Index of the last parsed parameter.
 * @return TRUE if a color is specified, otherwise FALSE.
 */
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

#ifdef BONUS

/**
 * @brief Parses light source data.
 * - BONUS VERSION - Multiples lights can be declared
 * Creates a light source object and sets its properties including origin,
 * brightness ratio, and optionally color.
 * If the brightness ratio isn't in the valid range [0, 1], an error is raised.
 * If a color is specified after the brightness ratio, it's parsed and set.
 *
 * @param mrt The main structure containing all parsed data.
 */
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

#else

/**
 * @brief Parses light source data.
 * - MANDATORY VERSION - only one light can be declared.
 * Creates a light source object and sets its properties including origin,
 * brightness ratio, and optionally color.
 * If the brightness ratio isn't in the valid range [0, 1], an error is raised.
 * If a color is specified after the brightness ratio, it's parsed and set.
 *
 * @param mrt The main structure containing all parsed data.
 */
void	inp_light(t_mrt *mrt)
{
	if (mrt->scn.light != NULL)
		msg_error_parsing("Only one light can be declared", mrt);
	mrt->scn.light = light_builder(mrt->scn.light);
	mrt->scn.light->origin = get_v3d(mrt, mrt->tab[LIGHT_CENTRE], V3D_COOR);
	mrt->scn.light->bright = ft_atolf(mrt->tab[LIGHT_RATIO]);
	if (!check_range(mrt->scn.light->bright, 0, 1))
		msg_error_parsing("Light ratio out of range", mrt);
	if (check_light_color(mrt, LIGHT_RATIO))
		mrt->scn.light->color = get_color(mrt->tab[LIGHT_COLOR], mrt);
}

#endif