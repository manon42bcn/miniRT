/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 19:20:45 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/27 19:20:47 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#ifdef BONUS

/**
 * @brief Parses input to populate a rectangle object's attributes.
 * -BONUS VERSION-
 * This function is responsible for reading the input related to a rectangle
 * and populating the corresponding attributes in the `obj` structure.
 * It ensures the rectangle's side and are correctly extracted
 * and also retrieves common attributes using the `get_common` function.
 *
 * @param mrt  Main structure containing all parsed data.
 */
void	inp_rectangle(t_mrt *mrt)
{
	t_mode	mode;

	mode = element_check(RECTANGLE, mrt);
	if (mode == ERROR_MODE)
		msg_error_parsing("Wrong data elements to build rectangle", mrt);
	mrt->obj = object_builder(RECTANGLE, mrt->obj);
	mrt->obj->elm.rc.centre = get_v3d(mrt, mrt->tab[RCT_CENTRE], V3D_COOR);
	mrt->obj->elm.rc.orient = get_v3d(mrt, mrt->tab[RCT_ORIENT], V3D_NORM);
	mrt->obj->elm.rc.width = ft_atolf(mrt->tab[RCT_WIDTH]);
	if (!check_range(mrt->obj->elm.rc.width, 0, INFINITY))
		msg_error_parsing("Rectangle width out of range", mrt);
	mrt->obj->elm.rc.height = ft_atolf(mrt->tab[RCT_HEIGHT]);
	if (!check_range(mrt->obj->elm.rc.height, 0, INFINITY))
		msg_error_parsing("Rectangle height out of range", mrt);
	get_common(mrt, RCT_HEIGHT, "Rectangle", mode);
}

#else

/**
 * @brief Displays an error when trying to parse a rectangle in
 * the mandatory version.
 *
 * @param mrt The main structure containing all parsed data.
 */
void	inp_rectangle(t_mrt *mrt)
{
	msg_error_parsing("Rectangle is not supported at mandatory version", mrt);
}

#endif
