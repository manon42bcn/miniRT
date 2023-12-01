/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_enum.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:30:09 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/26 22:11:39 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# define BONUS 1
#ifndef PARSE_ENUM_H
# define PARSE_ENUM_H

enum e_sph_parse
{
	SPH_ID = 0,
	SPH_CENTRE = 1,
	SPH_DIAM = 2
};

enum e_pln_parse
{
	PLN_ID = 0,
	PLN_CENTRE = 1,
	PLN_ORIENTATION = 2
};

enum e_cyl_parse
{
	CYL_ID = 0,
	CYL_CENTRE = 1,
	CYL_ORIENTATION = 2,
	CYL_DIAM = 3,
	CYL_HEIGHT = 4
};

enum e_rect_parse
{
	RCT_ID = 0,
	RCT_CENTRE = 1,
	RCT_ORIENT = 2,
	RCT_WIDTH = 3,
	RCT_HEIGHT = 4
};

enum e_trg_parse
{
	TRG_ID = 0,
	TRG_VERTEX_1 = 1,
	TRG_VERTEX_2 = 2,
	TRG_VERTEX_3 = 3
};

enum e_box_parse
{
	BOX_ID = 0,
	BOX_CENTRE = 1,
	BOX_ORIENTATION = 2,
	BOX_WIDTH = 3,
	BOX_HEIGHT = 4,
	BOX_DEPTH = 5
};

enum e_cone_parse
{
	CON_ID = 0,
	CON_CENTRE = 1,
	CON_ORIENTATION = 2,
	CON_DIAM = 3,
	CON_HEIGHT = 4
};

enum e_res_parse
{
	RES_PARSE_ID = 0,
	RES_PARSE_X = 1,
	RES_PARSE_Y = 2
};

enum e_amb_parse
{
	AMB_PARSE_ID = 0,
	AMB_LIGHT = 1,
	AMB_COLOR = 2
};

enum e_light_parse
{
	LIGHT_ID = 0,
	LIGHT_CENTRE = 1,
	LIGHT_RATIO = 2,
	LIGHT_COLOR = 3
};

enum e_camera_parse
{
	CAM_PARSE_ID = 0,
	CAM_CENTRE = 1,
	CAM_ORIENT = 2,
	CAM_FOV = 3
};

#endif
