/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 13:41:46 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/23 13:41:49 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#ifdef BONUS

/**
 * @brief   Parses and initializes a hyperboloid object from the given input.
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
void	inp_hyper(t_mrt *mrt)
{
	t_obj	*hyp;

	if (ft_count_tab(mrt->tab) != ELM_HYP)
		msg_error_parsing("Wrong data elements to build hyperboloid", mrt);
	mrt->obj = object_builder(HYPER, mrt->obj);
	hyp = mrt->obj;
	hyp->elm.hy.centre = get_v3d(mrt, mrt->tab[HYP_CENTRE], V3D_COOR);
	hyp->elm.hy.dir = get_v3d(mrt, mrt->tab[HYP_ORIENTATION], V3D_NORM);
	hyp->normal = hyp->elm.hy.dir;
	hyp->elm.hy.a = ft_atolf(mrt->tab[HYP_RAD_X]);
	if (!check_range(hyp->elm.hy.a, 0, INFINITY))
		msg_error_parsing("Hyperboloid radius x out of range", mrt);
	hyp->elm.hy.b = ft_atolf(mrt->tab[HYP_RAD_Y]);
	if (!check_range(hyp->elm.hy.b, 0, INFINITY))
		msg_error_parsing("Hyperboloid radius y out of range", mrt);
	hyp->elm.hy.c = ft_atolf(mrt->tab[HYP_RAD_Z]);
	if (!check_range(hyp->elm.hy.c, 0, INFINITY))
		msg_error_parsing("Hyperboloid radius z out of range", mrt);
	hyp->elm.hy.height = ft_atolf(mrt->tab[HYP_HEIGHT]);
	if (!check_range(hyp->elm.hy.height, 0, INFINITY))
		msg_error_parsing("Hyperboloid height out of range", mrt);
	get_common(mrt, HYP_HEIGHT, "Hyperboloid");
}

#else

/**
 * @brief Displays an error when trying to parse a hyperboloid in
 * the mandatory version.
 *
 * @param mrt The main structure containing all parsed data.
 */
void	inp_hyper(t_mrt *mrt)
{
	msg_error_parsing("Hyperboloid is not supported at mandatory version", mrt);
}
#endif
