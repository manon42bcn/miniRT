/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 00:00:47 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 21:53:17 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief Parses input to populate a sphere object's attributes.
 *
 * This function is responsible for reading the input related to a sphere
 * and populating the corresponding attributes in the `obj` structure.
 * It ensures the sphere's center and radius are correctly extracted
 * and also retrieves common attributes using the `get_common` function.
 *
 * Like all builders, first check if the data founded at file has the
 * necessary element to build it.
 * @param mrt  Main structure containing all parsed data.
 */
void	inp_sphere(t_mrt *mrt)
{
	t_obj	*current;
	size_t	elems;

	elems = ft_count_tab(mrt->tab);
	if (elems < ELM_SPH && elems > ELM_SPH + 1)
		msg_error_parsing("Wrong data elements to build sphere", mrt);
	current = mrt->obj;
	mrt->obj = object_builder(SPHERE, mrt->obj);
	mrt->obj->elm.sph.centre = get_v3d(mrt, mrt->tab[SPH_CENTRE],
			V3D_COOR);
	mrt->obj->elm.sph.radius = ft_atolf(mrt->tab[SPH_DIAM]) / 2.0f;
	if (!check_range(mrt->obj->elm.sph.radius, 0, INFINITY))
		msg_error_parsing("Sphere radius out of range", mrt);
	get_common(mrt, SPH_DIAM, "Sphere");
	mrt->obj->position = ft_copy_v3d(&mrt->obj->elm.sph.centre);
	mrt->obj->next = current;
}
