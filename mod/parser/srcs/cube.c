/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:03:40 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 21:57:12 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#ifdef BONUS

/**
 * @brief Parses input to populate a cube object's attributes.
 * -BONUS VERSION-
 * This function is responsible for reading the input related to a cube
 * and populating the corresponding attributes in the `obj` structure.
 * It ensures the cube's side and are correctly extracted
 * and retrieves common attributes using the `get_common` function.
 *
 * @param mrt  Main structure containing all parsed data.
 */
void	inp_cube(t_mrt *mrt)
{
	if (ft_count_tab(mrt->tab) != ELM_CU)
		msg_error_parsing("Wrong data elements to build cube", mrt);
	mrt->obj = object_builder(CUBE, mrt->obj);
	mrt->obj->elm.sq.centre = get_v3d(mrt, mrt->tab[CUBE_CENTRE], V3D_COOR);
	mrt->obj->elm.sq.side = ft_atolf(mrt->tab[CUBE_SIDE]);
	if (!check_range(mrt->obj->elm.sq.side, 0, INFINITY))
		msg_error_parsing("Cube side out of range", mrt);
	get_common(mrt, CUBE_SIDE, "Cube");
}

#else

/**
 * @brief Displays an error when trying to parse a cube in
 * the mandatory version.
 *
 * @param mrt The main structure containing all parsed data.
 */
void	inp_cube(t_mrt *mrt)
{
	msg_error_parsing("Cube is not supported at mandatory version", mrt);
}

#endif
