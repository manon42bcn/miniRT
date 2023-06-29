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

#include "minirt.h"

static inline int	parser_dict(char *id)
{
	int			i;
	static char	*dictionary[] = {
		"sp", "pl", "cy", "sq", "tr", "cu",
		"py", "R", "A", "c", "l", NULL};

	i = 0;
	if (ft_match_cmp(id, "#"))
		return (IDX_COMMENT);
	while (dictionary[i])
	{
		if (ft_match_cmp(dictionary[i], id))
			return (i);
		i++;
	}
	return (IDX_ERR);
}

static inline t_bool	load_object(t_mrt *mrt)
{
	int			type;
	static int	bonus = FALSE;
	static void	(*build[])(t_mrt *) = {
		inp_sphere, inp_plane, inp_cylinder, inp_square, inp_triangle, inp_cube,
		inp_pyramid, inp_resolution, inp_ambient, inp_camera, inp_light};

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
	build[type](mrt);
	return (TRUE);
}

static inline void	parse_fix(t_mrt *rt)
{
	t_cmr *node;

	node = rt->cmr;
	while (node)
	{
		node->ratio = (double)rt->scn.w_x / (double)rt->scn.w_y;
		node = node->next;
	}
	rt->main_cam = rt->cmr;
}

int	readfile_parser(char const *filename, t_mrt *rt)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_perror("Loading file error");
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
	return (TRUE);
}
