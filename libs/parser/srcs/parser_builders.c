/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_builders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:31:38 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/25 23:26:35 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_obj	*object_builder(int id, t_obj *next)
{
	t_obj	*rst;

	rst = (t_obj *)ft_sec_calloc(sizeof(t_obj));
	rst->type = id;
	rst->next = next;
	return (rst);
}

t_light	*light_builder(t_light *next)
{
	t_light	*rst;

	rst = (t_light *)ft_sec_calloc(sizeof(t_light));
	rst->next = next;
	return (rst);
}

t_cmr	*camera_builder(void)
{
	t_cmr	*rst;

	rst = (t_cmr *)ft_sec_calloc(sizeof(t_cmr));
	return (rst);
}
