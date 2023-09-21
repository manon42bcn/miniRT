/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 17:44:32 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 22:00:44 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#ifdef BONUS

/**
 * @brief Parses input to populate a square object's attributes.
 * -BONUS VERSION-
 * This function is responsible for reading the input related to a square
 * and populating the corresponding attributes in the `obj` structure.
 * It ensures the square's side and are correctly extracted
 * and also retrieves common attributes using the `get_common` function.
 *
 * @param mrt  Main structure containing all parsed data.
 */
void	inp_square(t_mrt *mrt)
{
	if (ft_count_tab(mrt->tab) != ELM_SQ)
		msg_error_parsing("Wrong data elements to build square", mrt);
	mrt->obj = object_builder(SQUARE, mrt->obj);
	mrt->obj->elm.sq.centre = get_v3d(mrt, mrt->tab[SQR_CENTRE], V3D_COOR);
	mrt->obj->elm.sq.orient = get_v3d(mrt, mrt->tab[SQR_ORIENT], V3D_NORM);
	mrt->obj->elm.sq.side = ft_atolf(mrt->tab[SQR_SIDE]);
	if (!check_range(mrt->obj->elm.sq.side, 0, INFINITY))
		msg_error_parsing("Square side out of range", mrt);
	get_common(mrt, SQR_SIDE, "Square");
	mrt->obj->normal = mrt->obj->elm.sq.orient;
}

#else

/**
 * @brief Displays an error when trying to parse a square in
 * the mandatory version.
 *
 * @param mrt The main structure containing all parsed data.
 */
void	inp_square(t_mrt *mrt)
{
	msg_error_parsing("Square is not supported at mandatory version", mrt);
}

#endif
