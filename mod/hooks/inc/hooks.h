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
# include "../../../inc/defines.h"
# include "../../../inc/objects.h"
# include "../../../inc/structs.h"
# include "../../parser/inc/parse.h"
# include "../../../mlx/mlx.h"

t_v3d	rotate_x(t_v3d old, double angle);
t_v3d	rotate_y(t_v3d old, double angle);
t_v3d	rotate_z(t_v3d old, double angle);
int		keys_handler(int key, t_mrt *mrt);
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
