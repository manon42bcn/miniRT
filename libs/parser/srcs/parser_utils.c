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

#include "parse.h"

static inline t_bool	check_common(t_mrt *mrt, int last)
{
	int	len;

	len = 0;
	while (mrt->tab[++last])
		len++;
	if (len != LAST_COMMON)
		return (FALSE);
	return (TRUE);
}

#ifdef BONUS

void	get_common(t_mrt *mrt, int last, char *elem)
{
	if (check_common(mrt, last) == FALSE)
		msg_error_parsing(elem, mrt);
	mrt->obj->specular = ft_atolf(mrt->tab[++last]);
	if (!check_range(mrt->obj->specular, 0, INFINITY))
		msg_error_parsing(elem, mrt);
	mrt->obj->reflex = ft_atolf(mrt->tab[++last]);
	if (!check_range(mrt->obj->reflex, 0, INFINITY))
		msg_error_parsing(elem, mrt);
	mrt->obj->refract = ft_atolf(mrt->tab[++last]);
	if (!check_range(mrt->obj->refract, 0, INFINITY))
		msg_error_parsing(elem, mrt);
	mrt->obj->texture = ft_atoi(mrt->tab[++last]);
	if (!check_range(mrt->obj->texture, 0, 5))
		msg_error_parsing(elem, mrt);
	if (mrt->obj->texture == 2)
		mrt->obj->wavelength = ft_atolf(mrt->tab[++last]);
	mrt->obj->color = get_color(mrt->tab[++last], mrt);
}

#else

void	get_common(t_mrt *mrt, int last, char *elem)
{
	if (check_common(mrt, last) == FALSE)
		msg_error_parsing(elem, mrt);
	mrt->obj->color = get_color(mrt->tab[++last], mrt);
}

#endif

t_bool	check_range(double value, double min, double max)
{
	if (value < min || value > max)
		return (FALSE);
	return (TRUE);
}

void	msg_error_parsing(char *message, t_mrt *mrt)
{
	ft_putstr_fd("[miniRT PARSE ERROR]: ", STDERR_FILENO);
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (mrt)
		clear_all(mrt, ERROR, NULL, NULL);
	exit(ERROR);
}
