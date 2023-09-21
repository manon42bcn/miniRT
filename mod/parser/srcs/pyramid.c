/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:18:06 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 21:55:25 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#ifdef BONUS

/**
 * @brief Parses input to populate a cube pyramid's attributes.
 * -BONUS VERSION-
 * This function is responsible for reading the input related to a pyramid
 * and populating the corresponding attributes in the `obj` structure.
 * It ensures the pyramid's side and are correctly extracted
 * and retrieves common attributes using the `get_common` function.
 *
 * @param mrt  Main structure containing all parsed data.
 */
void	inp_pyramid(t_mrt *mrt)
{
	if (ft_count_tab(mrt->tab) != ELM_PY)
		msg_error_parsing("Wrong data elements to build pyramid", mrt);
	mrt->obj = object_builder(PYRAMID, mrt->obj);
	mrt->obj->elm.sq.centre = get_v3d(mrt, mrt->tab[PYR_CENTRE],
			V3D_COOR);
	mrt->obj->elm.sq.side = ft_atolf(mrt->tab[PYR_SIDE]);
	if (!check_range(mrt->obj->elm.sq.side, 0, INFINITY))
		msg_error_parsing("Pyramid side out of range", mrt);
	get_common(mrt, PYR_SIDE, "Cube");
}

#else

/**
 * @brief Displays an error when trying to parse a pyramid in
 * the mandatory version.
 *
 * @param mrt The main structure containing all parsed data.
 */
void	inp_pyramid(t_mrt *mrt)
{
	msg_error_parsing("Pyramid is not supported at mandatory version", mrt);
}

#endif