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

/**
 * @brief Initialize hooks for various input commands.
 *
 * This function maps a set of keys to their corresponding transformations.
 * Each transformation affects an attribute of a shape or camera.
 *
 * @param mrt The main struct containing hooks.
 * @return void
 */
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
	mrt->hooks[52] = &camera_orbit_y;
	mrt->hooks[61] = &camera_orbit_x;
	mrt->hooks[51] = &camera_orbit_z;
	mrt->hooks[39] = &cylinder_rotation_y;
	mrt->hooks[30] = &cylinder_rotation_x;
	mrt->hooks[29] = &cylinder_rotation_z;
	mrt->hooks[68] = &light_rotation_y;
	mrt->hooks[59] = &light_rotation_x;
	mrt->hooks[58] = &light_rotation_z;
}

/**
 * @brief Handle the window exit operations.
 *
 * This function is called to safely close the window, ensuring
 * that all resources are appropriately freed.
 *
 * @param mrt The main struct with cleanup routines.
 * @return int Always returns 0.
 */
int	window_handler(t_mrt *mrt)
{
	exit(clear_all(mrt, 0, mrt->clean_window, mrt->clean_image));
}
