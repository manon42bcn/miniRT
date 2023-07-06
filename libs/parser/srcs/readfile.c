/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:23:35 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/25 23:26:36 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static inline t_bool	load_object(t_mrt *mrt)
{
	int			type;
	t_build		build;

	if (ft_match_cmp(mrt->aux, "\n"))
		return (FALSE);
	ft_clear_tabs(mrt->tab);
	mrt->tab = ft_split_cs(mrt->aux, SEP);
	if (mrt->tab == NULL)
		ft_perror("Split Line error");
	type = parser_dict(mrt->tab[0]);
	if (type == IDX_ERR)
		ft_perror("element not founded");
	if (type == IDX_COMMENT)
		return (FALSE);
	build = get_builder(type);
	build(mrt);
	return (TRUE);
}

static inline void	parse_fix(t_mrt *rt)
{
	t_cmr	*node;

	node = rt->cmr;
	while (node)
	{
		node->ratio = (double)rt->scn.w_x / (double)rt->scn.w_y;
		node = node->next;
	}
	rt->main_cam = rt->cmr;
}

t_mrt	*readfile_parser(char const *filename)
{
	int		fd;
	t_mrt	*rt;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_perror("Loading file error");
	rt = (t_mrt *)ft_sec_calloc(sizeof(t_mrt));
	while (TRUE)
	{
		ft_safe_free_char(&rt->aux);
		rt->aux = get_next_line(fd);
		if (!rt->aux)
			break ;
		if (rt->aux[0] != '#')
			load_object(rt);
	}
	ft_safe_free_char(&rt->aux);
	close(fd);
	parse_fix(rt);
	return (rt);
}
