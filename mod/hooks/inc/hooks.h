/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:56:17 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/17 23:19:08 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include <math.h>
# include "../../../libs/v3d/inc/v3d.h"
# include "../../../libs/rgb/inc/rgb.h"
# include "../../../libs/lib/inc/libft.h"
# include "defines.h"
# include "objects.h"
# include "structs.h"
# include "../../parser/inc/parse.h"
# include "../../../mlx/mlx.h"

# define MOVE_FACTOR	0.2L
# define SIZE_FACTOR	1.1L
# define LIGHT_TRANS	0.5L
# define BRIGHT_FACTOR	0.1L
# define RAD_ANGLE		0.0174533L
//Keys
# define K_D			2
# define K_E			14
# define K_R			15
# define K_H			4
# define K_C			8
# define K_T			17
# define K_Q			12
# define K_L			37
# define K_SPACE		49
# define K_ESC			53
# define K_S			1
# define K_UP			126
# define K_DOWN			125
# define K_LEFT			123
# define K_RIGHT		124
# define K_MINUS		78
# define K_PLUS			69
# define K_B			11
# define K_V			9

enum e_hooks_mode
{
	NORMAL,
	TO_SELECT,
	TO_SELECTED,
	TO_TRANSLATE,
	TO_ROTATE,
	TO_WIDTH,
	TO_HEIGHT,
	TO_CAMERA,
	TO_LIGHT,
	TO_EYE
};

t_bool	key_main(int key, t_mrt *mrt);
t_bool	mouse_select(int mouse_code, int x, int y, t_mrt *mrt);
t_bool	normal_light(t_mrt *mrt);
t_bool	normal_object(t_mrt *mrt);
t_bool	normal_mode(t_mrt *mrt);
t_bool	selection_mode(t_mrt *mrt);
t_bool	translate_mode(t_mrt *mrt);
t_bool	rotation_mode(t_mrt *mrt);
t_bool	camera_translate_mode(t_mrt *mrt);
t_bool	camera_rotation_mode(t_mrt *mrt);
t_bool	width_mode(t_mrt *mrt);
t_bool	height_mode(t_mrt *mrt);
t_bool	light_mode(t_mrt *mrt);
t_bool	light_behaviour(int key, t_mrt *mrt);
t_bool	cam_rotation(int key, t_mrt *mrt);
t_bool	cam_translate(int key, t_mrt *mrt);
t_bool	object_traslation(int key_dir, t_mrt *mrt);
t_bool	object_rotation(int key, t_mrt *mrt);
t_bool	object_width(int key, t_mrt *mrt);
t_bool	object_height(int key, t_mrt *mrt);
t_bool	change_camera(t_mrt *mrt);
t_bool	window_handler(t_mrt *mrt);

#endif
