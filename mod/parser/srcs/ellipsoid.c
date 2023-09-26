/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 13:42:35 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/23 13:42:37 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#ifdef BONUS

/**
 * @brief   Parses and initializes a ellipsoid object from the given input.
 * This function expects the `mrt` structure to contain valid
 * parsing data, and it initializes the byperboloid's properties
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
void	inp_ellipsoid(t_mrt *mrt)
{
	t_obj	*elp;

	if (ft_count_tab(mrt->tab) != ELM_ELLIP)
		msg_error_parsing("Wrong data elements to build ellipsoid", mrt);
	mrt->obj = object_builder(ELLIPS, mrt->obj);
	elp = mrt->obj;
	elp->elm.elp.centre = get_v3d(mrt, mrt->tab[ELP_CENTRE], V3D_COOR);
	elp->elm.elp.rx = ft_atolf(mrt->tab[ELP_RAD_X]);
	if (!check_range(elp->elm.elp.rx, 0, INFINITY))
		msg_error_parsing("Ellipsoid radius x out of range", mrt);
	elp->elm.elp.ry = ft_atolf(mrt->tab[ELP_RAD_Y]);
	if (!check_range(elp->elm.elp.ry, 0, INFINITY))
		msg_error_parsing("Ellipsoid radius y out of range", mrt);
	elp->elm.elp.rz = ft_atolf(mrt->tab[ELP_RAD_Z]);
	if (!check_range(elp->elm.elp.rz, 0, INFINITY))
		msg_error_parsing("Ellipsoid radius z out of range", mrt);
	get_common(mrt, ELP_RAD_Z, "Ellipsoid");
}

#else

/**
 * @brief Displays an error when trying to parse a ellipsoid in
 * the mandatory version.
 *
 * @param mrt The main structure containing all parsed data.
 */
void	inp_ellipsoid(t_mrt *mrt)
{
	msg_error_parsing("Hyperboloid is not supported at mandatory version", mrt);
}
#endif