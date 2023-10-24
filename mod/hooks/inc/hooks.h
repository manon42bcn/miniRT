/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/13 15:56:17 by mporras-          #+#    #+#             */
/*   Updated: 2023/08/13 15:56:19 by mporras-         ###   ########.fr       */
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
