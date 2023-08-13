/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 22:20:20 by mporras-          #+#    #+#             */
/*   Updated: 2023/08/06 22:20:23 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

void	load_hooks(t_mrt *mrt)
{
	mrt->hooks[41] = &cylinder_y_translation;
	mrt->hooks[32] = &cylinder_x_translation;
	mrt->hooks[31] = &cylinder_z_translation;
	mrt->hooks[46] = &cylinder_diam;
	mrt->hooks[48] = &cylinder_height;
	mrt->hooks[148] = &sphere_y_translation;
	mrt->hooks[139] = &sphere_x_translation;
	mrt->hooks[138] = &sphere_z_translation;
	mrt->hooks[153] = &sphere_diam;
	mrt->hooks[75] = &camera_closest_y;
	mrt->hooks[66] = &camera_closest_x;
	mrt->hooks[65] = &camera_closest_z;
	mrt->hooks[58] = &camera_orbit_y;
	mrt->hooks[61] = &camera_orbit_x;
	mrt->hooks[51] = &camera_orbit_z;
	mrt->hooks[39] = &cylinder_rotation_y;
	mrt->hooks[30] = &cylinder_rotation_x;
	mrt->hooks[29] = &cylinder_rotation_z;
	mrt->hooks[68] = &light_rotation_y;
	mrt->hooks[59] = &light_rotation_x;
	mrt->hooks[58] = &light_rotation_z;
}

int	window_handler(t_mrt *mrt)
{
	exit(clear_all(mrt, 0, mrt->clean_window, mrt->clean_image));
}
