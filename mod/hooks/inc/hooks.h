/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:56:17 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/08 11:53:19 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# define BONUS 1
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

//# define MOVE_FACTOR	0.1f
//# define SIZE_FACTOR	1.1f
//# define LIGHT_TRANS	0.5f
//# define BRIGHT_FACTOR	0.1f
# define MOVE_FACTOR	1.0L
# define SIZE_FACTOR	1.2L
# define LIGHT_TRANS	0.5L
# define BRIGHT_FACTOR	0.1L
# define RAD_ANGLE		0.0174533L
# define NORMAL			0
# define TO_SELECT		1
# define TO_TRANSLATE	2
# define TO_ROTATE		3
# define TO_WIDTH		4
# define TO_HEIGHT		5
# define TO_CAMERA		6
# define TO_LIGHT		7
# define TO_EYE			8
//Keys
# define K_D			2
# define K_H			4
# define K_C			8
# define K_E			14
# define K_R			15
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

int			key_main(int key, t_mrt *mrt);
int			mouse_select(int mouse_code, int x, int y, t_mrt *mrt);
int			normal_light(t_mrt *mrt);
int			normal_object(t_mrt *mrt);
int			normal_mode(t_mrt *mrt);
int			selection_mode(t_mrt *mrt);
int			translate_mode(t_mrt *mrt);
int			rotation_mode(t_mrt *mrt);
int			camera_translate_mode(t_mrt *mrt);
int			camera_rotation_mode(t_mrt *mrt);
int			width_mode(t_mrt *mrt);
int			height_mode(t_mrt *mrt);
int			light_mode(t_mrt *mrt);
int			light_behaviour(int key, t_mrt *mrt);
int			cam_rotation(int key, t_mrt *mrt);
int			cam_translate(int key, t_mrt *mrt);
int			object_traslation(int key_dir, t_mrt *mrt);
int			object_rotation(int key, t_mrt *mrt);
int			object_width(int key, t_mrt *mrt);
int			object_height(int key, t_mrt *mrt);
int			change_camera(t_mrt *mrt);
int			window_handler(t_mrt *mrt);

#endif
