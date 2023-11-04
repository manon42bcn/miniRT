/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builders.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:58:19 by mporras-          #+#    #+#             */
/*   Updated: 2023/07/04 16:58:22 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief   Maps an identifier string to its corresponding index based on
 * the dictionary of elements -BONUS VERSION-.
 *
 * @param   id  The identifier string.
 * @return  Index of the element if found; IDX_COMMENT for comments;
 * IDX_ERR for unknown elements.
 */
int	parser_dict(char *id)
{
	int			i;
	static char	*dictionary[] = {
		"sp", "pl", "cy", "rc", "tr", "bx",
		"co", "el", "R", "A", "c", "l", NULL};

	i = 0;
	if (!id || id[0] == '#')
		return (IDX_COMMENT);
	while (dictionary[i])
	{
		if (ft_match_cmp(dictionary[i], id))
			return (i);
		i++;
	}
	return (IDX_ERR);
}

/**
 * @brief   Retrieves the appropriate builder function based on the given index.
 * -BONUS VERSION-
 *
 * @param   index  Index of the builder function.
 * @param   mrt    Pointer to the main Ray Tracer structure.
 * @return  Function pointer to the builder function.
 */
t_build	get_builder(int index, t_mrt *mrt)
{
	static t_build	builder[] = {&inp_sphere, &inp_plane,
		&inp_cylinder, &inp_rectangle,
		&inp_triangle, &inp_box,
		&inp_cone, &inp_ellipsoid,
		&inp_resolution, &inp_ambient,
		&inp_camera, &inp_light};

	if (index > (int)(sizeof(builder) / sizeof(t_build)) || index < 0)
		msg_error_parsing("builder out of index", mrt);
	return (builder[index]);
}
