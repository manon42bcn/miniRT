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

/**
 * @brief Checks if the number of elements in the tab after the "last"
 * index matches LAST_COMMON.
 *
 * @param mrt  Main structure containing the parsed data.
 * @param last The index after which to start checking in the tab.
 * @return     TRUE if the number of elements matches LAST_COMMON,
 * FALSE otherwise.
 */
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

/**
 * @brief Retrieves common object properties in BONUS VERSION.
 *
 * This function checks for specular, reflex, refract, texture, and color
 * properties of the object and populates them accordingly.
 * In case of any issues, a parsing error is thrown.
 *
 * @param mrt  Main structure containing the parsed data.
 * @param last The index in the tab where common properties start.
 * @param elem The element name for error reporting.
 */
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

/**
 * @brief Retrieves common object properties in MANDATORY VERSION.
 *
 * In non-BONUS mode, this function only fetches the color
 * property for the object.
 *
 * @param mrt  Main structure containing the parsed data.
 * @param last The index in the tab where common properties start.
 * @param elem The element name for error reporting.
 */
void	get_common(t_mrt *mrt, int last, char *elem)
{
	if (check_common(mrt, last) == FALSE)
		msg_error_parsing(elem, mrt);
	mrt->obj->color = get_color(mrt->tab[++last], mrt);
}

#endif

/**
 * @brief Validates if a given value falls within a specified range.
 *
 * @param value The number to be checked.
 * @param min   The lower bound of the range.
 * @param max   The upper bound of the range.
 * @return      TRUE if the value is within the range, FALSE otherwise.
 */
t_bool	check_range(double value, double min, double max)
{
	if (value < min || value > max)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief Displays a parsing error message and exits the program.
 *
 * This function displays the error message to the standard error output.
 * If the mrt structure is provided, it will also clear all resources
 * associated with it.
 *
 * @param message The error message to be displayed.
 * @param mrt     The main structure containing all parsed data (optional).
 */
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
