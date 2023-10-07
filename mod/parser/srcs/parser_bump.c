/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:20:28 by mporras-          #+#    #+#             */
/*   Updated: 2023/10/07 18:20:30 by mporras-         ###   ########.fr       */
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

void	get_bump(t_mrt *mrt, int index)
{
	char	**tmp;

	index++;
	tmp = ft_split(mrt->tab[index], ':');
	if (tmp == NULL || ft_count_tab(tmp) != 2)
		ft_perror("Split texture info error");
	if (ft_match_cmp(tmp[0], "xpm") == FALSE)
		msg_error_parsing("Bump texture wrong format", mrt);

}