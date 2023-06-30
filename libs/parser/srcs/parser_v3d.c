/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_v3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 13:00:01 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/12 13:00:04 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_v3d	get_v3d(char *line, int mode)
{
	char	**tmp;
	t_v3d	rst;

	tmp = ft_split(line, ',');
	if (tmp == NULL || ft_count_tab(tmp) != 3)
	{
		ft_clear_tabs(tmp);
		ft_perror("Error getting vector");
	}
	rst.x = ft_atolf(tmp[X_C]);
	rst.y = ft_atolf(tmp[Y_C]);
	rst.z = ft_atolf(tmp[Z_C]);
	ft_clear_tabs(tmp);
	if (mode == V3D_NORM && ft_is_normal_v3d(&rst) == FALSE)
		msg_error_parsing("v3d is not normal.");
	return (rst);
}
