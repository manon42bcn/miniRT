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

/**
 * @brief Validates the RGB values to ensure they fall within the
 * acceptable range.
 *
 * The function checks each component (Red, Green, and Blue) to verify
 * they are between 0 and 255. If any component is out of range,
 * it raises a parsing error.
 *
 * @param color Array containing the R, G, and B values.
 * @param mrt   The main structure containing all parsed data.
 */
static inline void	check_color_range(t_rgb color[3], t_mrt *mrt)
{
	if (color[R_I] < 0 || color[R_I] > 255)
		msg_error_parsing("Color R range should be 0-255", mrt);
	if (color[G_I] < 0 || color[G_I] > 255)
		msg_error_parsing("Color G range should be 0-255", mrt);
	if (color[B_I] < 0 || color[B_I] > 255)
		msg_error_parsing("Color B range should be 0-255", mrt);
}

/**
 * @brief Parses a string to extract RGB values and returns the combined color.
 *
 * The function splits the string based on commas and expects three values
 * corresponding to the Red, Green, and Blue components. After extraction,
 * the function validates each RGB value's range and then combines them
 * into a single RGB value for return.
 *
 * @param line The string containing the RGB values in "R,G,B" format.
 * @param mrt  The main structure containing all parsed data.
 * @return     The combined RGB color value.
 */
t_rgb	get_color(char *line, t_mrt *mrt)
{
	char	**tmp;
	t_rgb	rgb[3];

	tmp = ft_split(line, ',');
	if (tmp == NULL || ft_count_tab(tmp) != 3)
		ft_perror("Error getting color");
	rgb[R_I] = ft_atoi(tmp[R_I]);
	rgb[G_I] = ft_atoi(tmp[G_I]);
	rgb[B_I] = ft_atoi(tmp[B_I]);
	ft_clear_tabs(tmp);
	check_color_range(rgb, mrt);
	rgb[R_I] <<= 16;
	rgb[G_I] <<= 8;
	return (rgb[R_I] | rgb[G_I] | rgb[B_I]);
}
