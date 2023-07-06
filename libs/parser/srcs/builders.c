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

#ifdef BONUS

int	parser_dict(char *id)
{
	int			i;
	static char	*dictionary[] = {
		"sp", "pl", "cy", "sq", "tr", "cu",
		"py", "R", "A", "c", "l", NULL};

	i = 0;
	if (ft_match_cmp(id, "#"))
		return (IDX_COMMENT);
	while (dictionary[i])
	{
		if (ft_match_cmp(dictionary[i], id))
			return (i);
		i++;
	}
	return (IDX_ERR);
}

t_build	get_builder(int index)
{
	static t_build	builder[] = {&inp_sphere, &inp_plane,
		&inp_cylinder, &inp_square,
		&inp_triangle, &inp_cube,
		&inp_pyramid, &inp_resolution,
		&inp_ambient, &inp_camera,
		&inp_light};

	if (index > (int)(sizeof(builder) / sizeof(t_build)) || index < 0)
		ft_my_perror("[MiniRT]", "[Parser]: builder out of index");
	return (builder[index]);
}

#else

int	parser_dict(char *id)
{
	int			i;
	static char	*dictionary[] = {
		"sp", "pl", "cy", "R",
		"A", "c", "l", NULL};

	i = 0;
	if (ft_match_cmp(id, "#"))
		return (IDX_COMMENT);
	while (dictionary[i])
	{
		if (ft_match_cmp(dictionary[i], id))
			return (i);
		i++;
	}
	return (IDX_ERR);
}

t_build	get_builder(int index)
{
	static t_build	builder[] = {&inp_sphere, &inp_plane,
		&inp_cylinder, &inp_resolution,
		&inp_ambient, &inp_camera,
		&inp_light};

	if (index > (int)(sizeof(builder) / sizeof(t_build)) || index < 0)
		ft_my_perror("[MiniRT]", "[Parser]: builder out of index");
	return (builder[index]);
}

#endif

