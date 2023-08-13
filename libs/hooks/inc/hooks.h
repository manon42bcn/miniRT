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

# include "../../v3d/inc/v3d.h"
# include "../../rgb/inc/rgb.h"
# include "../../lib/inc/libft.h"
# include "../../inc/objects.h"
# include "../../inc/structs.h"

void	load_hooks(t_mrt *mrt);
int		mouse_handler(int mouse_code, int x, int y, t_mrt *mrt);
void	cylinder_x_translation(t_mrt *mrt, int x, int y, int mouse_code);
void	cylinder_y_translation(t_mrt *mrt, int x, int y, int mouse_code);
void	cylinder_z_translation(t_mrt *mrt, int x, int y, int mouse_code);
void	cylinder_diam(t_mrt *mrt, int x, int y, int mouse_code);
void	cylinder_height(t_mrt *mrt, int x, int y, int mouse_code);
void	sphere_x_translation(t_mrt *mrt, int x, int y, int mouse_code);
void	sphere_y_translation(t_mrt *mrt, int x, int y, int mouse_code);
void	sphere_z_translation(t_mrt *mrt, int x, int y, int mouse_code);
void	sphere_diam(t_mrt *mrt, int x, int y, int mouse_code);
void	camera_closest_x(t_mrt *mrt, int x, int y, int mouse_code);
void	camera_closest_y(t_mrt *mrt, int x, int y, int mouse_code);
void	camera_closest_z(t_mrt *mrt, int x, int y, int mouse_code);
void	camera_orbit_x(t_mrt *mrt, int x, int y, int mouse_code);
void	camera_orbit_y(t_mrt *mrt, int x, int y, int mouse_code);
void	camera_orbit_z(t_mrt *mrt, int x, int y, int mouse_code);
void	cylinder_rotation_x(t_mrt *mrt, int x, int y, int mouse_code);
void	cylinder_rotation_y(t_mrt *mrt, int x, int y, int mouse_code);
void	cylinder_rotation_z(t_mrt *mrt, int x, int y, int mouse_code);
void	light_rotation_x(t_mrt *mrt, int x, int y, int mouse_code);
void	light_rotation_y(t_mrt *mrt, int x, int y, int mouse_code);
void	light_rotation_z(t_mrt *mrt, int x, int y, int mouse_code);

#endif

