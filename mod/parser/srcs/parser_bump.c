/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:20:28 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/12 23:47:15 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief Check if the file is a valid xpm file.
 *
 * This function checks if the given file is a valid xpm file by attempting to
 * open it. If the file cannot be opened, an error is displayed using ft_perror.
 * The function returns TRUE if the file is valid and FALSE otherwise.
 *
 * @param file The path of the xpm file to check.
 * @return TRUE if the file is valid, FALSE otherwise.
 */
t_bool	valid_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_perror("Invalid xpm file");
	close(fd);
	return (TRUE);
}

/**
 * @brief Parse and set the bump texture information for the object.
 *
 * This function parses and sets the bump texture information for the object
 * at the specified index. It checks if the object type is a sphere and if the
 * provided texture information is in the correct format. If successful, it
 * sets the xpm path, marks the object with bump mapping, and performs
 * additional validations.
 *
 * @param mrt A pointer to the MiniRT structure.
 * @param index The index in the tab array corresponding to the bump texture
 * 				information.
 * @return TRUE if the bump texture information is successfully parsed and set,
 * 				FALSE otherwise.
 */
t_bool	get_bump(t_mrt *mrt, int index)
{
	char	**tmp;

	if (!mrt->tab[index])
		return (FALSE);
	if (mrt->obj->type != SPHERE)
		return (FALSE);
	tmp = ft_split(mrt->tab[index], ':');
	if (tmp == NULL || ft_count_tab(tmp) != 2)
		ft_perror("Split texture info error");
	if (!ft_match_cmp(tmp[0], "xpm"))
		msg_error_parsing("Bump texture wrong format", mrt);
	if (!ft_myregex(tmp[1], "*.xpm"))
		msg_error_parsing("Texture file wrong format", mrt);
	valid_file(tmp[1]);
	ft_memset(&mrt->obj->xpm, 0, sizeof(t_img));
	mrt->obj->xpm.path = ft_strdup(tmp[1]);
	mrt->obj->bump = TRUE;
	ft_clear_tabs(tmp);
	return (TRUE);
}
