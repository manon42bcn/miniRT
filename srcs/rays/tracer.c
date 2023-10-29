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

static inline void	get_hits(t_inter *inter, t_obj *obj, t_mrt *mrt)
{
	get_inter(inter, obj, mrt);
	if (inter->obj)
	{
		inter->hitted = TRUE;
		inter->color = inter->obj->color;
		inter->hit = ft_plus_v3d(inter->ray.from, ft_scalar_v3d(inter->dist, inter->ray.to));
		inter->reflex = inter->obj->reflex;
		inter->refract = inter->obj->refract;
	}
	else
	{
		inter->hitted = FALSE;
		inter->color = mrt->scn.bgr;
		inter->reflex = 0.0;
		inter->refract = 0.0;
	}
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
static inline t_v3d	refraction(t_inter inter, t_obj *obj)
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
			ft_scalar_v3d(refr_relative * cos_theta - sqrt(coef_disc), inter.ray.to)));
}


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
	inter.color = bump_texture(inter, inter.hit, inter.obj, mrt);
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
	inter.hit = get_hits(&inter, mrt->obj, &close_obj);
	inter.normal = get_normal(&close_obj,dir, inter.hit);
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