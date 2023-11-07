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
 * @brief Retrieve and initialize the color properties of the current object.
 *
 * This function is responsible for fetching and setting the color attributes
 * of the current object, based on the information provided in the data table.
 * The original and selected colors are stored in the object for later
 * reference.
 *
 * @param mrt Pointer to the main data structure containing the scene and
 * objects.
 * @param last Index of the last processed value in the data table.
 */
static inline void	get_obj_color(t_mrt *mrt, int last)
{
	mrt->obj->color = get_color(mrt->tab[last], mrt);
	mrt->obj->orig_color = mrt->obj->color;
	mrt->obj->sel_color = ft_invert_color(mrt->obj->orig_color);
}

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
 * @param mode Parse mode to check num of elements to parse from file
 */
void	get_common(t_mrt *mrt, int last, char *elem, t_mode mode)
{
	if (mode == MANDATORY)
	{
		get_obj_color(mrt, ++last);
		return ;
	}
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
	get_obj_color(mrt, ++last);
	if (mode == BUMP_MODE)
		get_bump(mrt, ++last);
}

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
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (mrt)
		clear_all(mrt, ERROR, NULL, NULL);
	exit(ERROR);
}
