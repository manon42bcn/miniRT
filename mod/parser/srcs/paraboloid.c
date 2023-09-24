/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 13:42:02 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/23 13:42:04 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#ifdef BONUS

/**
 * @brief   Parses and initializes a paraboloid object from the given input.
 * This function expects the `mrt` structure to contain valid
 * parsing data, and it initializes the paraboloid's properties
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
void	inp_paraboloid(t_mrt *mrt)
{
	t_obj	*prb;

	if (ft_count_tab(mrt->tab) != ELM_PARAB)
		msg_error_parsing("Wrong data elements to build paraboloid", mrt);
	mrt->obj = object_builder(BOX, mrt->obj);
	prb = mrt->obj;
	prb->elm.prb.centre = get_v3d(mrt, mrt->tab[PRB_CENTRE], V3D_COOR);
	prb->elm.prb.dir = get_v3d(mrt, mrt->tab[PRB_ORIENTATION], V3D_NORM);
	prb->normal = prb->elm.prb.dir;
	prb->elm.prb.focal_dist = ft_atolf(mrt->tab[PRB_FOCAL]);
	if (!check_range(prb->elm.prb.focal_dist, 0, INFINITY))
		msg_error_parsing("Paraboloid focus distance out of range", mrt);
	prb->elm.prb.height = ft_atolf(mrt->tab[PRB_HEIGHT]);
	if (!check_range(prb->elm.prb.height, 0, INFINITY))
		msg_error_parsing("Paraboloid height of range", mrt);
	prb->elm.prb.min_height = ft_atolf(mrt->tab[PRB_M_HEIGHT]);
	if (!check_range(prb->elm.prb.min_height, 0, INFINITY))
		msg_error_parsing("Paraboloid min height out of range", mrt);
	get_common(mrt, PRB_M_HEIGHT, "Paraboloid");
}

#else

/**
 * @brief Displays an error when trying to parse a Paraboloid in
 * the mandatory version.
 *
 * @param mrt The main structure containing all parsed data.
 */
void	inp_paraboloid(t_mrt *mrt)
{
	msg_error_parsing("Paraboloid is not supported at mandatory version", mrt);
}

#endif