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
# include "../../v3d/inc/v3d.h"
# include "../../rgb/inc/rgb.h"
# include "../../lib/inc/libft.h"
# include "../../inc/objects.h"
# include "../../inc/structs.h"
# include "../../parser/inc/parse.h"

# define NO_HOOK		0
# define K_D			2
# define K_H			4
# define K_G			5
# define K_Z			6
# define K_X			7
# define K_C			8
# define K_E			14
# define K_R			15
# define K_Y			16
# define K_T			17
# define K_Q			12
# define K_L			37
# define K_J			38
# define K_U			32
# define K_O			31
# define K_N			45
# define K_M			46
# define K_SPACE		49
# define K_ENTER		36
# define K_ESC			53
# define K_S			115
# define K_UP			126
# define K_DOWN			125

t_v3d	rotate_x(t_v3d old, double angle);
t_v3d	rotate_y(t_v3d old, double angle);
t_v3d	rotate_z(t_v3d old, double angle);
void	load_hooks(t_mrt *mrt);
int		window_handler(t_mrt *mrt);
int		mouse_handler(int mouse_code, int mouseX, int mouseY, t_mrt *mrt);
void	cylinder_x_translation(t_mrt *mrt, int mouse_code);
void	cylinder_y_translation(t_mrt *mrt, int mouse_code);
void	cylinder_z_translation(t_mrt *mrt, int mouse_code);
void	cylinder_diam(t_mrt *mrt, int mouse_code);
void	cylinder_height(t_mrt *mrt, int mouse_code);
void	sphere_x_translation(t_mrt *mrt, int mouse_code);
void	sphere_y_translation(t_mrt *mrt, int mouse_code);
void	sphere_z_translation(t_mrt *mrt, int mouse_code);
void	sphere_diam(t_mrt *mrt, int mouse_code);
void	camera_closest_x(t_mrt *mrt, int mouse_code);
void	camera_closest_y(t_mrt *mrt, int mouse_code);
void	camera_closest_z(t_mrt *mrt, int mouse_code);
void	camera_orbit_x(t_mrt *mrt, int mouse_code);
void	camera_orbit_y(t_mrt *mrt, int mouse_code);
void	camera_orbit_z(t_mrt *mrt, int mouse_code);
void	cylinder_rotation_x(t_mrt *mrt, int mouse_code);
void	cylinder_rotation_y(t_mrt *mrt, int mouse_code);
void	cylinder_rotation_z(t_mrt *mrt, int mouse_code);
void	light_rotation_x(t_mrt *mrt, int mouse_code);
void	light_rotation_y(t_mrt *mrt, int mouse_code);
void	light_rotation_z(t_mrt *mrt, int mouse_code);

#endif
