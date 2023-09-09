/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 14:43:11 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/23 17:27:12 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Determines if the path between an origin and direction is
 * not get shadowed by objects.
 *
 * Checks whether there's any object blocking the path between the origin
 * and direction by evaluating intersections with objects.
 *
 * @param origin Origin of the ray.
 * @param dir Direction of the ray.
 * @param obj Pointer to the list of objects in the scene.
 * @return TRUE if path is clear, FALSE if shadowed.
 */
static inline t_bool	lighted(t_v3d origin, t_v3d dir, t_obj *obj)
{
	double		evl;
	t_solver	solve;

	while (obj)
	{
		solve = get_solver(obj->type);
		evl = solve(origin, dir, obj);
		if (evl > EPSILON && evl < 1)
			return (FALSE);
		obj = obj->next;
	}
	return (TRUE);
}

/**
 * @brief Adjusts the RGB components based on brightness coefficient.
 *
 * @param rgb Triple of RGB components to be adjusted.
 * @param coef Brightness coefficient.
 * @param color Color value to be added to rgb.
 */
static inline void	brightness(double (*rgb)[3], double coef, int color)
{
	unsigned int	mask;

	mask = RGB_MASK << 16;
	(*rgb)[0] += coef * ((color & mask) >> 16) / RGB_MASK;
	mask >>= 8;
	(*rgb)[1] += coef * ((color & mask) >> 8) / RGB_MASK;
	mask >>= 8;
	(*rgb)[2] += coef * (color & mask) / RGB_MASK;
}

/**
 * @brief Computes the specular reflection brightness for a given ray
 * and intersection point.
 *
 * @param ray Ray of interest.
 * @param inter Intersection information.
 * @param scn Scene settings and information.
 * @param obj The object that the ray has hit.
 * @return Specular reflection brightness value.
 */
double	specular_transform(t_ray ray, t_inter *inter, t_scene scn, t_obj *obj)
{
	double	light;
	t_v3d	direction;
	t_v3d	p_to_cam;
	t_v3d	reflected;

	direction = ft_minus_v3d(scn.light->origin, inter->hit);
	p_to_cam = ft_minus_v3d(ray.from, inter->hit);
	reflected = reflect_ray(direction, inter->normal);
	if (ft_dot_v3d(reflected, p_to_cam) > 0)
		light = scn.light->bright
			* pow(ft_cos_v3d(reflected, p_to_cam), obj->specular);
	else
		light = 0;
	return (light);
}

/**
 * @brief Computes the lighting at a given intersection point.
 *
 * Considers both diffuse and specular components of lighting. Adjusts
 * the intersection color based on the computed lighting.
 *
 * @param ray The ray of interest.
 * @param inter Intersection information, containing details like hit point.
 * @param scn Scene settings and information.
 * @param obj The object that the ray has hit.
 */
void	light_hit(t_ray ray, t_inter *inter, t_scene scn, t_obj *obj)
{
	double			light;
	double			rgb[3];
	t_v3d			direction;

	light = 0.0;
	ft_memset(rgb, 0, 3 * sizeof(double));
	brightness(&rgb, scn.bright, scn.amb_rgb);
	while (scn.light)
	{
		direction = ft_minus_v3d(scn.light->origin, inter->hit);
		if (lighted(inter->hit, direction, obj)
			&& ft_dot_v3d(inter->normal, direction) > 0)
		{
			light = scn.light->bright * ft_cos_v3d(inter->normal, direction);
			brightness(&rgb, light, scn.light->color);
		}
		if (obj->specular)
		{
			light = specular_transform(ray, inter, scn, obj);
			brightness(&rgb, light, scn.light->color);
		}
		scn.light = scn.light->next;
	}
	inter->color = ft_rgb_light(inter->color, rgb);
}

/**
 * @brief Computes the direction of the normal at a hit point.
 *
 * Determines the direction of the surface normal at the hit point,
 * considering the object type. For spheres, it also sets if the hit
 * is inside or outside.
 *
 * @param hitted The hit point in world coordinates.
 * @param dir Direction of the incoming ray.
 * @param normal Output parameter, direction of the normal at the hit point.
 * @param obj The object that has been hit.
 */
void	hit_direction(t_v3d hitted, t_v3d dir, t_v3d *normal, t_obj *obj)
{
	if (obj->type == SPHERE)
	{
		*normal = ft_normal_v3d(ft_minus_v3d(hitted, obj->elm.sph.centre));
		if (ft_cos_v3d(dir, *normal) > 0)
		{
			*normal = ft_scalar_v3d(-1, *normal);
			obj->elm.sph.inside = TRUE;
		}
		else
			obj->elm.sph.inside = FALSE;
	}
	else
	{
		if (ft_cos_v3d(dir, obj->normal) > 0)
			*normal = ft_scalar_v3d(-1, obj->normal);
		else
			*normal = obj->normal;
	}
}
