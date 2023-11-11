/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:20:28 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/11 02:31:40 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

t_bool	valid_file(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_perror("Invalid xpm file");
	close(fd);
	return (TRUE);
}

t_bool	get_bump(t_mrt *mrt, int index)
{
	char	**tmp;

	if (!mrt->tab[index])
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
