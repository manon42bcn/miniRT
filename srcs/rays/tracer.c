/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 11:41:32 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 17:35:40 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Resets the reflection and refraction properties of the closest
 * object if not a CLOSE_OBJ.
 *
 * @param closest Pointer to the closest object to the ray.
 */
static inline void	clean_rgb_interactions(t_obj *closest)
{
	if (closest->type != CLOSE_OBJ)
		return ;
	closest->reflex = 0;
	closest->refract = 0;
}

/**
 * @brief Computes the intersection point of a ray with all objects in the scene.
 *
 * Identifies the closest intersection point of a given ray with objects in the
 * scene.
 *
 * @param inter Struct containing information about the ray being cast.
 * @param obj Pointer to the list of objects in the scene.
 * @param closest Pointer to the closest intersected object.
 * @return A 3D vector representing the intersection point in world coordinates.
 */
static inline t_v3d	get_hits(t_inter inter, t_obj *obj, t_obj *closest)
{
	double	close_dist;
	t_v3d	origin;
	t_v3d	dir;

	close_dist = INFINITY;
	origin = inter.ray.from;
	dir = inter.ray.to;
	closest->type = CLOSE_OBJ;
	try_all_intersections(inter.ray, obj, closest, &close_dist);
	return (ft_plus_v3d(origin, ft_scalar_v3d(close_dist, dir)));
}

#ifdef BONUS

/**
 * @brief Computes the refracted direction given an incident direction and
 * the object's properties.
 *
 * @param from Incident direction.
 * @param dir Direction of the ray.
 * @param obj Object through which refraction occurs.
 * @return A 3D vector representing the refracted direction.
 */
static inline t_v3d	refraction(t_v3d from, t_v3d dir, t_obj *obj)
{
	double	cos_theta;
	double	refr_coef;
	double	refr_transmitted;
	double	refr_relative;
	double	coef_disc;

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
			ft_scalar_v3d(refr_relative * cos_theta - sqrt(coef_disc), dir)));
}

/**
 * @brief Computes the color of a pixel by casting rays into the scene
 * and handling interactions.
 *
 * This is the main ray tracing function at bonus version.
 * It handles object intersections, shading, reflection, and refraction.
 * The function is recursive, with the depth indicating the number of
 * recursive steps for reflection and refraction.
 *
 * @param origin Origin of the ray.
 * @param dir Direction of the ray.
 * @param mrt Main structure containing scene and rendering information.
 * @param depth Current recursion depth.
 * @return RGB color value for the given ray.
 */
t_rgb	tracer(t_v3d origin, t_v3d dir, t_mrt *mrt, int depth)
{
	t_obj		close_obj;
	t_inter		inter;

	depth = depth * 2;
	inter.ray.from = origin;
	inter.ray.to = dir;
	inter.hit = get_hits(inter, mrt->obj, &close_obj);
	hit_direction(inter.hit, dir, &(inter.normal), &close_obj);
	if (close_obj.type != CLOSE_OBJ)
		inter.color = close_obj.color;
	if (close_obj.type == SPHERE && close_obj.bump == TRUE)
		inter.color = bump_texture(inter.hit, &close_obj);
	texturize(close_obj.texture, &inter, mrt->obj);
	light_hit(inter.ray, &inter, mrt->scn, mrt->obj);
	clean_rgb_interactions(&close_obj);
	if (close_obj.refract > 0)
		inter.color = tracer(inter.hit,
				refraction(dir, inter.normal, &close_obj), mrt, depth);
	if (close_obj.reflex > 0 && depth > 0)
		inter.ref_color = tracer(inter.hit,
				reflect_ray(ft_scalar_v3d(-1, dir), inter.normal),
				mrt, depth - 1);
	return (ft_rgb_add(ft_rgb_dot(inter.color, 1 - close_obj.reflex),
			ft_rgb_dot(inter.ref_color, close_obj.reflex)));
}

#else

/**
 * @brief Computes the color of a pixel by casting rays into the scene and
 * handling interactions.
 *
 * This version of the tracer function handles object intersections and shading
 * but does not handle reflection or refraction. (Mandatory version)
 *
 * @param origin Origin of the ray.
 * @param dir Direction of the ray.
 * @param mrt Main structure containing scene and rendering information.
 * @param depth Current recursion depth (unused in this version).
 * @return RGB color value for the given ray.
 */
t_rgb	tracer(t_v3d origin, t_v3d dir, t_mrt *mrt, int depth)
{
	t_obj		close_obj;
	t_inter		inter;

	depth = depth * 2;
	inter.ray.from = origin;
	inter.ray.to = dir;
	inter.hit = get_hits(inter, mrt->obj, &close_obj);
	hit_direction(inter.hit, dir, &(inter.normal), &close_obj);
	if (close_obj.type != CLOSE_OBJ)
		inter.color = close_obj.color;
	else
		inter.color = mrt->scn.bgr;
	light_hit(inter.ray, &inter, mrt->scn, mrt->obj);
	clean_rgb_interactions(&close_obj);
	return (ft_rgb_add(ft_rgb_dot(inter.color, 1 - close_obj.reflex),
			ft_rgb_dot(inter.ref_color, close_obj.reflex)));
}

#endif