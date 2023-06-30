/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 00:04:10 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 17:36:23 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_common(t_mrt *mrt, int last, char *elem)
{
	mrt->obj->specular = ft_atolf(mrt->tab[++last]);
	check_range(mrt->obj->specular, 0, INFINITY, elem);
	mrt->obj->reflex = ft_atolf(mrt->tab[++last]);
	check_range(mrt->obj->reflex, 0, INFINITY, elem);
	mrt->obj->refract = ft_atolf(mrt->tab[++last]);
	check_range(mrt->obj->refract, 0, INFINITY, elem);
	mrt->obj->texture = ft_atoi(mrt->tab[++last]);
	check_range(mrt->obj->texture, 0, 5, elem);
	if (mrt->obj->texture == 2)
		mrt->obj->wavelength = ft_atolf(mrt->tab[++last]);
	mrt->obj->color = get_color(mrt->tab[++last]);
}

void	check_range(double value, double min, double max, char *msg)
{
	if (value < min || value > max)
		msg_error_parsing(msg);
}

void	msg_error_parsing(char *message)
{
	ft_putstr_fd("miniRT PARSE ERROR: ", STDERR_FILENO);
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(ERROR);
}
