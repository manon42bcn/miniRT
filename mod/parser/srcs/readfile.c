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

/**
 * @brief   Determines the closest object to the camera from a given
 * list of objects.
 *
 * @param   camera  Pointer to the camera structure.
 * @param   obj     Pointer to the linked list of objects.
 * @return  Pointer to the closest object.
 */
static inline t_obj	*closer_object(t_cmr *camera, t_obj *obj)
{
	double	dist;
	double	target;
	t_obj	*rst;

	target = 0;
	rst = NULL;
	while (obj)
	{
		dist = fabs(ft_distance_v3d(camera->position, obj->position));
		if (rst == NULL)
		{
			rst = obj;
			target = dist;
		}
		if (dist < target)
		{
			rst = obj;
			target = dist;
		}
		obj = obj->next;
	}
	return (rst);
}

/**
 * @brief   Iterate over each cam to find the object closest to
 * each camera in the list.
 *
 * @param   mrt     Pointer to the main Ray Tracer structure.
 */
static inline void	close_to_cam(t_mrt *mrt)
{
	t_cmr	*node;

	node = mrt->cmr;
	mrt->main_cam = node;
	while (node)
	{
		node->close_obj = closer_object(node, mrt->obj);
		node->orbit = ft_distance_v3d(node->position,
				node->close_obj->position);
		node = node->next;
	}
}

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
	close_to_cam(mrt);
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
	if (type == IDX_ERR) {
		printf("%s %s here?\n", mrt->tab[0], mrt->aux);
		ft_perror("element not founded");
	}
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
		printf("%s read?\n", rt->aux);
		if (!rt->aux)
			break ;
		if (rt->aux[0] != '#' && rt->aux[0] != '\n')
			load_object(rt);
	}
	ft_safe_free_char(&rt->aux);
	close(rt->fd);
	if (!checking_parse(rt))
		msg_error_parsing("Not enough elements to create a scene", rt);
	return (rt);
}
