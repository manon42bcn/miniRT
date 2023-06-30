/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:57:47 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/12 12:57:49 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static inline void	check_color_range(t_rgb color[3])
{
	if (color[R_I] < 0 || color[R_I] > 255)
		msg_error_parsing("Color R range should be 0-255");
	if (color[G_I] < 0 || color[G_I] > 255)
		msg_error_parsing("Color G range should be 0-255");
	if (color[B_I] < 0 || color[B_I] > 255)
		msg_error_parsing("Color B range should be 0-255");
}

t_rgb	get_color(char *line)
{
	char	**tmp;
	t_rgb	rgb[3];

	tmp = ft_split(line, ',');
	if (tmp == NULL || ft_count_tab(tmp) != 3)
	{
		ft_clear_tabs(tmp);
		ft_perror("Error getting color");
	}
	rgb[R_I] = ft_atoi(tmp[R_I]);
	rgb[G_I] = ft_atoi(tmp[G_I]);
	rgb[B_I] = ft_atoi(tmp[B_I]);
	ft_clear_tabs(tmp);
	check_color_range(rgb);
	rgb[R_I] <<= 16;
	rgb[G_I] <<= 8;
	return (rgb[R_I] | rgb[G_I] | rgb[B_I]);
}
