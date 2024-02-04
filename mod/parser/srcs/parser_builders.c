/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_builders.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaguilar <vaguilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 13:31:38 by mporras-          #+#    #+#             */
/*   Updated: 2024/02/03 18:42:48 by vaguilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief   Creates and initializes a new object with the given type identifier.
 *
 * @param   id    The type identifier of the object to be created.
 * @param   next  Pointer to the next object in the linked list.
 *
 * @return  Pointer to the newly created object.
 */
t_obj	*object_builder(int id, t_obj *next)
{
	t_obj	*rst;

	rst = (t_obj *)ft_sec_calloc(sizeof(t_obj));
	rst->type = id;
	rst->next = next;
	return (rst);
}

/**
 * @brief   Creates and initializes a new light structure.
 *
 * @param   next  Pointer to the next light in the linked list.
 *
 * @return  Pointer to the newly created light structure.
 */
t_light	*light_builder(t_light *next)
{
	t_light	*rst;

	rst = (t_light *)ft_sec_calloc(sizeof(t_light));
	rst->next = next;
	return (rst);
}

/**
 * @brief   Creates and initializes a new camera structure.
 *
 * @return  Pointer to the newly created camera structure.
 */
t_cmr	*camera_builder(void)
{
	t_cmr	*rst;

	rst = (t_cmr *)ft_sec_calloc(sizeof(t_cmr));
	return (rst);
}
