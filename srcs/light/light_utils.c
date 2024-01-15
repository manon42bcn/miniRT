/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 10:40:43 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/15 01:34:08 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#ifdef BONUS

/**
 * @brief Calculate the refracted ray direction based on Snell's law.
 *
 * This function computes the refracted ray direction using Snell's law.
 * It takes the incident ray direction, the point of intersection, and the
 * refractive properties of the object. The refractive index is adjusted based
 * on whether the ray is inside or outside the object. If the refraction is not
 * possible (total internal reflection), the function returns the reflected ray.
 *
 * @param from The point of intersection.
 * @param dir The incident ray direction.
 * @param obj A pointer to the object.
 * @return The refracted ray direction.
 */
t_v3d	refraction(t_v3d from, t_v3d dir, t_obj *obj)
{
	t_dec	cos_theta;
	t_dec	refr_coef;
	t_dec	refr_transmitted;
	t_dec	refr_relative;
	t_dec	coef_disc;

	cos_theta = ft_dot_v3d(from, dir);
	refr_coef = 1;
	refr_transmitted = obj->refract;
	if (obj->elm.sph.inside == 1)
	{
		coef_disc = refr_coef;
		refr_coef = refr_transmitted;
		refr_transmitted = coef_disc;
	}
	refr_relative = refr_coef / refr_transmitted;
	coef_disc = 1 - refr_relative * refr_relative * (1 - cos_theta * cos_theta);
	if (coef_disc < 0)
		return (reflect_ray(ft_scalar_v3d(-1, from), dir));
	return (ft_plus_v3d(ft_scalar_v3d(refr_relative, from),
			ft_scalar_v3d(refr_relative * cos_theta - sqrtl(coef_disc),
				dir)));
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
t_dec	specular_transform(t_ray ray, t_inter inter, t_light *scn_light)
{
	t_dec	light;
	t_v3d	direction;
	t_v3d	p_to_cam;
	t_v3d	reflected;

	direction = ft_minus_v3d(scn_light->origin, inter.hit);
	p_to_cam = ft_minus_v3d(ray.from, inter.hit);
	reflected = reflect_ray(direction, inter.normal);
	light = 0.0L;
	if (ft_dot_v3d(reflected, p_to_cam) > 0)
		light = scn_light->bright
			* powl(ft_cos_v3d(reflected, p_to_cam), inter.specular);
	return (light);
}

#endif