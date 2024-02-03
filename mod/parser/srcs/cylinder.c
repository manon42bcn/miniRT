/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:04:12 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/08 18:06:14 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief   Parses and initializes a cylinder object from the given input.
 * This function expects the `mrt` structure to contain valid
 * parsing data, and it initializes the cylinder's properties
 * based on the provided data.
 *
 * Like all builders, first check if the data founded at file has the
 * necessary element to build it.
 * @param   mrt  Pointer to the main Ray Tracer structure containing
 * the parsing data.
 *
 * @note    The function will raise parsing errors and terminate
 *  if invalid data is detected.
 */
void	inp_cylinder(t_mrt *mrt)
{
	t_mode	mode;

	mode = element_check(CYLINDER, mrt);
	if (mode == ERROR_MODE)
		msg_error_parsing("Wrong data elements to build Cylinder", mrt);
	mrt->obj = object_builder(CYLINDER, mrt->obj);
	mrt->obj->elm.cyl.centre = get_v3d(mrt, mrt->tab[CYL_CENTRE],
			V3D_COOR);
	mrt->obj->elm.cyl.dir = get_v3d(mrt, mrt->tab[CYL_ORIENTATION],
			V3D_NORM);
	mrt->obj->elm.cyl.radius = ft_atolf(mrt->tab[CYL_DIAM]) / 2.0f;
	if (!check_range(mrt->obj->elm.cyl.radius, 0, INFINITY))
		msg_error_parsing("Cylinder radius out of range", mrt);
	mrt->obj->elm.cyl.height = ft_atolf(mrt->tab[CYL_HEIGHT]);
	if (!check_range(mrt->obj->elm.cyl.height, 0, INFINITY))
		msg_error_parsing("Cylinder height out of range", mrt);
	get_common(mrt, CYL_HEIGHT, "Cylinder", mode);
	mrt->obj->elm.cyl.texture = mrt->obj->texture;
}
