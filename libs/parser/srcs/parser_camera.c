/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:06:22 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/25 23:26:36 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#ifdef BONUS

void	inp_camera(t_mrt *mrt)
{
	static t_cmr	*last = NULL;
	t_cmr			*new;

	new = camera_builder();
	if (last == NULL)
		mrt->cmr = new;
	else
		last->next = new;
	new->position = get_v3d(mrt, mrt->tab[CAM_CENTRE], V3D_COOR);
	new->dir = get_v3d(mrt, mrt->tab[CAM_ORIENT], V3D_NORM);
	new->inp_fov = ft_atoi(mrt->tab[CAM_FOV]);
	if (!check_range(mrt->cmr->inp_fov, 0, 180))
		msg_error_parsing("Camera fov out of range", mrt);
	new->fov = tan((new->inp_fov * M_PI / 180) / 2);
	last = new;
}

#else

void	inp_camera(t_mrt *mrt)
{
	if (mrt->cmr != NULL)
		msg_error_parsing("Only one camera can be declared", mrt);
	mrt->cmr = camera_builder();
	mrt->cmr->position = get_v3d(mrt, mrt->tab[CAM_CENTRE], V3D_COOR);
	mrt->cmr->dir = get_v3d(mrt, mrt->tab[CAM_ORIENT], V3D_NORM);
	mrt->cmr->inp_fov = ft_atoi(mrt->tab[CAM_FOV]);
	if (!check_range(mrt->cmr->inp_fov, 0, 180))
		msg_error_parsing("Camera fov out of range", mrt);
	mrt->cmr->fov = tan((mrt->cmr->inp_fov * M_PI / 180) / 2);
}

#endif


