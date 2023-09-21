/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 00:37:40 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 22:00:18 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief Parses input to populate a plane object's attributes.
 *
 * This function is responsible for reading the input related to a plane
 * and populating the corresponding attributes in the `obj` structure.
 * It ensures the plane's center and orientation are correctly extracted
 * and also retrieves common attributes using the `get_common` function.
 *
 * Like all builders, first check if the data founded at file has the
 * necessary element to build it.
 * @param mrt  Main structure containing all parsed data.
 */
void	inp_plane(t_mrt *mrt)
{
	if (ft_count_tab(mrt->tab) != ELM_PL)
		msg_error_parsing("Wrong data elements to build plane", mrt);
	mrt->obj = object_builder(PLANE, mrt->obj);
	mrt->obj->elm.pl.centre = get_v3d(mrt, mrt->tab[PLN_CENTRE],
			V3D_COOR);
	mrt->obj->elm.pl.orient = get_v3d(mrt, mrt->tab[PLN_ORIENTATION],
			V3D_NORM);
	get_common(mrt, PLN_ORIENTATION, "Plane");
	mrt->obj->normal = mrt->obj->elm.pl.orient;
	mrt->obj->position = ft_copy_v3d(&mrt->obj->elm.pl.centre);
}
