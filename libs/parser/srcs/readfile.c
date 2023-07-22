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

void print_all_mrt_parser(const t_mrt *mrt)
{
	printf("POINTER BASIC %p\n", mrt);
	printf("to_img: %d, %p\n", mrt->to_img, &(mrt->to_img));
	printf("mlx: %p, %p\n", mrt->mlx, &(mrt->mlx));
	printf("mlx_win: %p, %p\n", mrt->mlx_win, &(mrt->mlx_win));
	printf("scn: %p, %p\n", &(mrt->scn), &(mrt->scn));
	printf("obj: %p, %p\n", mrt->obj, &(mrt->obj));
	printf("cmr: %p, %p\n", mrt->cmr, &(mrt->cmr));
	printf("main_cam: %p, %p\n", mrt->main_cam, &(mrt->main_cam));
	printf("x: %d, %p\n", mrt->x, &(mrt->x));
	printf("y: %d, %p\n", mrt->y, &(mrt->y));
	printf("aux: %s, %p\n", mrt->aux, &(mrt->aux));
	printf("tab: %p, %p\n", mrt->tab, &(mrt->tab));
	printf("bonus: %d, %p\n", mrt->bonus, &(mrt->bonus));
}

t_mrt	*readfile_parser(char const *filename)
{
	int		fd;
	t_mrt	*rt;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		msg_error_parsing("Loading file error");
	rt = (t_mrt *)ft_sec_calloc(sizeof(t_mrt));
	print_all_mrt_parser(rt);
	rt->fd = fd;
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
	close(rt->fd);
	return (rt);
}
