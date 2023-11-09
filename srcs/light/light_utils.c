/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:40:43 by mporras-          #+#    #+#             */
/*   Updated: 2023/10/30 10:40:45 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#ifdef BONUS

/**
 * @brief Calculate the refracted ray direction based on Snell's law.
 *
 * This function computes the direction of the refracted ray after it passes
 * through an interface with a change in refractive index. It uses Snell's law
 * to determine the refracted ray direction. The function takes into account the
 * relative refractive indices of the materials on either side of the interface.
 *
 * @param inter The intersection data containing the incident ray and properties.
 * @param obj The object containing the refractive index for the material.
 * @return The direction of the refracted ray.
 */
t_v3d	refraction(t_inter inter, t_obj *obj)
{
	double	cos_theta;
	double	refr_coef;
	double	refr_transmitted;
	double	refr_relative;
	double	coef_disc;

	cos_theta = ft_dot_v3d(inter.ray.from, inter.ray.to);
	refr_coef = 1;
	refr_transmitted = obj->refract;
	if (inter.inside == TRUE)
	{
		coef_disc = refr_coef;
		refr_coef = refr_transmitted;
		refr_transmitted = coef_disc;
	}
	refr_relative = refr_coef / refr_transmitted;
	coef_disc = 1 - refr_relative * refr_relative * (1 - cos_theta * cos_theta);
	if (coef_disc < 0)
		return (reflect_ray(ft_scalar_v3d(-1, inter.ray.from), inter.ray.to));
	return (ft_plus_v3d(ft_scalar_v3d(refr_relative, inter.ray.from),
			ft_scalar_v3d(refr_relative * cos_theta
				- sqrt(coef_disc), inter.ray.to)));
}

/**
 * @brief Calculate the reflection of a ray off a surface.
 *
 * This function calculates the reflection direction of a ray off a surface
 * based on the surface normal. It follows the law of reflection, returning the
 * reflected ray direction.
 *
 * @param ray The incident ray direction.
 * @param normal The surface normal.
 * @return The direction of the reflected ray.
 */
t_v3d	reflect_ray(t_v3d ray, t_v3d normal)
{
	return (ft_minus_v3d(ft_scalar_v3d(2
				* ft_dot_v3d(normal, ray), normal), ray));
}

/**
 * @brief Compute the contribution of specular reflection to the lighting.
 *
 * This function computes the contribution of specular reflection to the overall
 * lighting of a point on the surface. It calculates the intensity of the
 * reflection using the Blinn-Phong reflection model and returns the result.
 *
 * @param ray The incident ray direction.
 * @param inter The intersection data containing the surface normal and other
 * properties.
 * @param scn_light The light source parameters.
 * @return The intensity of the specular reflection.
 */
double	specular_transform(t_ray ray, t_inter inter, t_light *scn_light)
{
	double	light;
	t_v3d	direction;
	t_v3d	p_to_cam;
	t_v3d	reflected;

	direction = ft_minus_v3d(scn_light->origin, inter.hit);
	p_to_cam = ft_minus_v3d(ray.from, inter.hit);
	reflected = reflect_ray(direction, inter.normal);
	if (ft_dot_v3d(reflected, p_to_cam) > 0)
		light = scn_light->bright
			* pow(ft_cos_v3d(reflected, p_to_cam), inter.specular);
	else
		light = 0;
	return (light);
}

#endif