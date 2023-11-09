/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 22:28:44 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/08 22:02:26 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Allocates memory for an array of RGB values to represent edges.
 *
 * Uses secure memory allocation to prevent unexpected behaviors.
 * This function serves as a utility for preparing edge data structures
 * in the rendering process.
 *
 * @param size Number of RGB values required (often corresponds to
 * screen width + 2).
 * @return Pointer to the newly allocated array of RGB values.
 */
t_rgb	*create_edges_new(int size)
{
	t_rgb	*rst;

	rst = (t_rgb *)ft_sec_calloc(sizeof(t_rgb) * size);
	return (rst);
}
