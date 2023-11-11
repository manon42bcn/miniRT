/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:41:32 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/11 13:22:47 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#ifdef BONUS

/**
 * @brief Trace rays and calculate pixel color for ray tracing.
 * -BONUS VERSION-
 *
 * This function traces rays from the camera into the scene and calculates the
 * pixel color. It performs intersection tests with objects in the scene,
 * computes lighting, reflections, and refractions. The result is the color of
 * the pixel seen from the camera.
 *
 * @param origin The origin point of the ray (camera position).
 * @param dir The direction of the ray (normalized direction vector).
 * @param mrt The main ray tracing structure containing scene and object data.
 * @param depth The recursion depth for reflection and refraction (set to 0
 * for primary rays).
 * @return The color of the pixel in the scene.
 */
t_rgb	tracer(t_v3d origin, t_v3d dir, t_mrt *mrt, int depth)
{
	t_inter		inter;

	depth = depth * 2;
	inter.ray.from = origin;
	inter.ray.to = dir;
	get_hits(&inter, mrt->obj, mrt);
	if (inter.obj == NULL)
		return (mrt->scn.bgr);
	inter.normal = get_normal(&inter, dir, inter.hit);
	inter.color = bump_texture(inter, inter.hit, *inter.obj, mrt);
	texturize(&inter);
	inter.color = light_hit(inter.ray, inter, mrt);
	if (inter.refract > 0)
		inter.color = tracer(inter.hit,
				refraction(inter, inter.obj), mrt, depth);
	if (inter.reflex > 0 && depth > 0)
		inter.ref_color = tracer(inter.hit,
				reflect_ray(ft_scalar_v3d(-1, dir), inter.normal),
				mrt, depth - 1);
	return (ft_rgb_add(ft_rgb_dot(inter.color, 1 - inter.reflex),
			ft_rgb_dot(inter.ref_color, inter.reflex)));
}

#else

/**
 * @brief Trace rays and calculate pixel color for ray tracing.
 * -MANDATORY VERSION-
 *
 * This function traces rays from the camera into the scene and calculates the
 * pixel color. It performs intersection tests with objects in the scene,
 * and computes lighting. The result is the color of
 * the pixel seen from the camera.
 *
 * @param origin The origin point of the ray (camera position).
 * @param dir The direction of the ray (normalized direction vector).
 * @param mrt The main ray tracing structure containing scene and object data.
 * @param depth Unused at mandatory version.
 * @return The color of the pixel in the scene.
 */
t_rgb	tracer(t_v3d origin, t_v3d dir, t_mrt *mrt, int depth)
{
	t_inter		inter;

	(void)depth;
	inter.ray.from = origin;
	inter.ray.to = dir;
	get_hits(&inter, mrt->obj, mrt);
	if (inter.obj == NULL)
		return (mrt->scn.bgr);
	inter.normal = get_normal(&inter, dir, inter.hit);
	inter.color = light_hit(inter.ray, inter, mrt);
	return (inter.color);
}

#endif