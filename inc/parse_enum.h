/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_enum.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 00:30:09 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/25 23:21:16 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_ENUM_H
# define PARSE_ENUM_H

typedef enum e_fig
{
	CLOSE_OBJ=-1,
	SPHERE=0,
	PLANE=1,
	CYLINDER=2,
	SQUARE=3,
	TRIANGLE=4,
	CUBE=5,
	PYRAMID=6
} t_fig;

typedef enum e_sph_parse
{
	SPH_ID = 0,
	SPH_CENTRE = 1,
	SPH_DIAM = 2
}	t_sph_parse;

typedef enum e_pln_parse
{
	PLN_ID = 0,
	PLN_CENTRE = 1,
	PLN_ORIENTATION = 2
}	t_pln_parse;

typedef enum e_cyl_parse
{
	CYL_ID = 0,
	CYL_CENTRE = 1,
	CYL_ORIENTATION = 2,
	CYL_DIAM = 3,
	CYL_HEIGHT = 4
}	t_cyl_parse;

typedef enum e_sqr_parse
{
	SQR_ID = 0,
	SQR_CENTRE = 1,
	SQR_ORIENT = 2,
	SQR_SIDE = 3
}	t_sqr_parse;

typedef enum e_trg_parse
{
	TRG_ID = 0,
	TRG_VERTEX_1 = 1,
	TRG_VERTEX_2 = 2,
	TRG_VERTEX_3 = 3
}	t_trg_parse;

typedef enum e_cube_parse
{
	CUBE_ID = 0,
	CUBE_CENTRE = 1,
	CUBE_SIDE = 2
}	t_cube_parse;

typedef enum e_pyr_parse
{
	PYR_ID = 0,
	PYR_CENTRE = 1,
	PYR_SIDE = 2
}	t_pyr_parse;

typedef enum e_res_parse
{
	RES_PARSE_ID = 0,
	RES_PARSE_X = 1,
	RES_PARSE_Y = 2
}	t_res_parse;

typedef enum e_amb_parse
{
	AMB_PARSE_ID = 0,
	AMB_LIGHT = 1,
	AMB_COLOR = 2
}	t_amb_parse;

typedef enum e_light_parse
{
	LIGHT_ID = 0,
	LIGHT_CENTRE = 1,
	LIGHT_RATIO = 2,
	LIGHT_COLOR = 3
}	t_light_parse;

typedef enum e_camera_parse
{
	CAM_PARSE_ID = 0,
	CAM_CENTRE = 1,
	CAM_ORIENT = 2,
	CAM_FOV = 3
}	t_camera_parse;

enum e_array_intersections
{
	IP1,
	IP2,
	C_DIST
};

#endif
