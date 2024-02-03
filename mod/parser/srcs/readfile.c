/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:23:35 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/13 22:30:41 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

/**
 * @brief   Validates the parsed data from the scene to check if
 * the mandatory elements are present and call to close_to_cam function
 *
 * @param   mrt     Pointer to the main Ray Tracer structure.
 * @return  TRUE if all checks pass, FALSE otherwise.
 */
static inline t_bool	checking_parse(t_mrt *mrt)
{
	if (!mrt->cmr)
		return (FALSE);
	if (!mrt->obj)
		return (FALSE);
	if (!mrt->scn.parsed)
		return (FALSE);
	if (!mrt->scn.light)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief   Processes a single line from the input to load the appropriate
 * object based on its type.
 *
 * @param   mrt     Pointer to the main Ray Tracer structure.
 * @return  TRUE if the object was loaded successfully, FALSE otherwise.
 */
static inline t_bool	load_object(t_mrt *mrt)
{
	int			type;
	t_build		build;

	ft_clear_tabs(mrt->tab);
	mrt->tab = ft_split_cs(mrt->aux, SEP);
	if (mrt->tab == NULL)
		ft_perror("Split Line error");
	type = parser_dict(mrt->tab[0]);
	if (type == IDX_ERR)
		msg_error_parsing("Element not founded", mrt);
	if (type == IDX_COMMENT)
		return (FALSE);
	build = get_builder(type, mrt);
	build(mrt);
	return (TRUE);
}

/**
 * @brief   Reads and parses the input file to create a scene.
 *
 * @param   filename  Name of the input file.
 * @return  Pointer to the populated Ray Tracer structure.
 */
t_mrt	*readfile_parser(char const *filename)
{
	int		fd;
	t_mrt	*rt;

	if (!ft_myregex((char *)filename, "*.rt"))
		msg_error_parsing("Scene not *.rt format", NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		msg_error_parsing("Loading file error", NULL);
	rt = (t_mrt *)ft_sec_calloc(sizeof(t_mrt));
	rt->scn.parsed = FALSE;
	rt->fd = fd;
	while (TRUE)
	{
		ft_safe_free_char(&rt->aux);
		rt->aux = get_next_line(fd);
		if (!rt->aux)
			break ;
		load_object(rt);
	}
	ft_safe_free_char(&rt->aux);
	close(rt->fd);
	if (!checking_parse(rt))
		msg_error_parsing("Not enough elements to create a scene", rt);
	return (rt);
}
