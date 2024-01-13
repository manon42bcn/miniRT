/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 17:04:05 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/21 17:04:07 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#ifdef BONUS

/**
 * @brief   Parses and initializes a cone object from the given input.
 * This function expects the `mrt` structure to contain valid
 * parsing data, and it initializes the cone's properties
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
void	inp_cone(t_mrt *mrt)
{
	double	diam;
	t_mode	mode;

	mode = element_check(CONE, mrt);
	if (mode == ERROR_MODE)
		msg_error_parsing("Wrong data elements to build cone", mrt);
	mrt->obj = object_builder(CONE, mrt->obj);
	mrt->obj->elm.con.centre = get_v3d(mrt, mrt->tab[CON_CENTRE],
			V3D_COOR);
	mrt->obj->elm.con.dir = get_v3d(mrt, mrt->tab[CON_ORIENTATION],
			V3D_NORM);
	diam = ft_atolf(mrt->tab[CON_DIAM]);
	mrt->obj->elm.con.radius = diam / 2.0L;
	if (!check_range(mrt->obj->elm.con.radius, 0, INFINITY))
		msg_error_parsing("Cone radius out of range", mrt);
	mrt->obj->elm.con.height = ft_atolf(mrt->tab[CON_HEIGHT]);
	if (!check_range(mrt->obj->elm.con.height, 0, INFINITY))
		msg_error_parsing("Cone height out of range", mrt);
	get_common(mrt, CON_HEIGHT, "Cone", mode);
	mrt->obj->elm.con.alpha = diam / (2.0L * mrt->obj->elm.con.height);
}

#else

/**
 * @brief Displays an error when trying to parse a triangle in
 * the mandatory version.
 *
 * @param mrt The main structure containing all parsed data.
 */
void	inp_cone(t_mrt *mrt)
{
	msg_error_parsing("Cone is not supported at mandatory version", mrt);
}

#endif