/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 00:04:10 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/11 03:09:55 by mporras-         ###   ########.fr       */
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
 * @param mode Parse mode, based on the number of elements founded.
 * @return TRUE if there is not more info to parse. FALSE otherwise
 */
static inline t_bool	get_obj_color(t_mrt *mrt, int last, int mode)
{
	mrt->obj->color = get_color(mrt->tab[last], mrt);
	mrt->obj->orig_color = mrt->obj->color;
	mrt->obj->sel_color = ft_invert_color(mrt->obj->orig_color);
	if (mode == MANDATORY)
		return (TRUE);
	return (FALSE);
}

/**
 * @brief Parse and extract bonus features from a line in the scene file.
 *
 * This function takes a line from the scene file, which is expected to
 * contain bonus features, and parses it to extract the relevant information.
 * It checks the format and title of the special feature, ensuring it matches
 * the expected format. If the parsing encounters errors, it raises
 * appropriate error messages.
 *
 * @param line The line from the scene file containing bonus features.
 * @param mrt A pointer to the ray tracer structure.
 * @return An array of strings containing the parsed bonus features.
 */
static inline char	**line_bonus(char *line, t_mrt *mrt, int last)
{
	char	**evl;
	char	**bonus;

	evl = ft_split(line, ':');
	if (ft_count_tab(evl) == 1)
		msg_error_parsing("Special feature wrong format", mrt);
	if (ft_match_cmp(evl[0], "xpm"))
	{
		get_bump(mrt, last);
		ft_clear_tabs(evl);
		if (mrt->tab[last + 1])
			return (line_bonus(mrt->tab[last + 1], mrt, last + 1));
		else
			return (NULL);
	}
	if (!ft_match_cmp(evl[0], "BNS"))
		msg_error_parsing("Special feature wrong title", mrt);
	bonus = ft_split(evl[1], ';');
	if (ft_count_tab(bonus) < 4 || ft_count_tab(bonus) > 5)
		msg_error_parsing("Not enough bonus features", mrt);
	ft_clear_tabs(evl);
	return (bonus);
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
 * @return this function always return true, to make skips viable.
 */
t_bool	get_common(t_mrt *mrt, int last, char *elem, t_mode mode)
{
	char	**bns;
	int		i;

	if (get_obj_color(mrt, ++last, mode))
		return (FALSE);
	i = -1;
	last++;
	bns = line_bonus(mrt->tab[last], mrt, last);
	if (bns == NULL)
		return (FALSE);
	mrt->obj->specular = ft_atoi(bns[++i]);
	mrt->obj->reflex = (double)ft_atolf(bns[++i]);
	mrt->obj->refract = (double )ft_atolf(bns[++i]);
	mrt->obj->texture = ft_atoi(bns[++i]);
	if (!check_range(mrt->obj->refract, 0, INFINITY)
		|| !check_range(mrt->obj->reflex, 0, INFINITY)
		|| !check_range(mrt->obj->specular, 0, INFINITY)
		|| !check_range(mrt->obj->texture, 0, 5))
		msg_error_parsing(elem, mrt);
	if (mrt->obj->texture == 2 && ft_count_tab(bns) == 5)
		mrt->obj->wavelength = (double )ft_atolf(bns[++i]);
	ft_clear_tabs(bns);
	if (mrt->tab[last + 1])
		get_bump(mrt, ++last);
	return (TRUE);
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
