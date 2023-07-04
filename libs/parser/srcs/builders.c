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
