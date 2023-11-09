/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 18:29:07 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 22:01:02 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#ifdef BONUS

/**
 * @brief Parses input to populate a cube triangle's attributes.
 * -BONUS VERSION-
 * This function is responsible for reading the input related to a triangle
 * and populating the corresponding attributes in the `obj` structure.
 * It ensures the triangle's side and are correctly extracted
 * and retrieves common attributes using the `get_common` function.
 *
 * @param mrt  Main structure containing all parsed data.
 */
void	inp_triangle(t_mrt *mrt)
{
	t_mode	mode;

	mode = element_check(TRIANGLE, mrt);
	if (mode == ERROR_MODE)
		msg_error_parsing("Wrong data elements to build triangle", mrt);
	mrt->obj = object_builder(TRIANGLE, mrt->obj);
	mrt->obj->elm.trg.v1 = get_v3d(mrt, mrt->tab[TRG_VERTEX_1],
			V3D_COOR);
	mrt->obj->elm.trg.v2 = get_v3d(mrt, mrt->tab[TRG_VERTEX_2],
			V3D_COOR);
	mrt->obj->elm.trg.v3 = get_v3d(mrt, mrt->tab[TRG_VERTEX_3],
			V3D_COOR);
	get_common(mrt, TRG_VERTEX_3, "Triangle", mode);
	mrt->obj->elm.trg.dir = ft_cross_v3d(
			ft_minus_v3d(mrt->obj->elm.trg.v3, mrt->obj->elm.trg.v1),
			ft_minus_v3d(mrt->obj->elm.trg.v2, mrt->obj->elm.trg.v1));
}

#else

/**
 * @brief Displays an error when trying to parse a triangle in
 * the mandatory version.
 *
 * @param mrt The main structure containing all parsed data.
 */
void	inp_triangle(t_mrt *mrt)
{
	msg_error_parsing("Triangle is not supported at mandatory version", mrt);
}

#endif
