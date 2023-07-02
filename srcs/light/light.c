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

static inline t_bool	lighted(t_v3d origin, t_v3d dir, t_obj *obj)
{
	double			evl;
	static t_solver solve[] = {&sphere_solver, &plane_solver,
	                           &cylinder_solver, &square_solver,
	                           &triangle_solver, &cube_solver,
	                           &pyramid_solver};
	while (obj)
	{
		evl = solve[obj->type](origin, dir, obj);
		if (evl > EPSILON && evl < 1)
			return (FALSE);
		obj = obj->next;
	}
	return (TRUE);
}

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

double	specular_transform(t_ray ray, t_inter *inter, t_scene scn, t_obj *lst)
{
	double	light;
	t_v3d	direction;
	t_v3d	p_to_cam;
	t_v3d	reflected;

	direction = ft_minus_v3d(scn.light->origin, inter->hit);
	p_to_cam = ft_minus_v3d(ray.from, inter->hit);
	reflected = reflect_ray(direction, inter->normal);
	if (ft_dot_v3d(reflected, p_to_cam) > 0)
		light = scn.light->bright *
                pow(ft_cos_v3d(reflected, p_to_cam), lst->specular);
	else
		light = 0;
	return (light);
}

void	ligth_hit(t_ray ray, t_inter *inter, t_scene scn, t_obj *lst)
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
		if (lighted(inter->hit, direction, lst)
			&& ft_dot_v3d(inter->normal, direction) > 0)
		{
			light = scn.light->bright * ft_cos_v3d(inter->normal, direction);
			brightness(&rgb, light, scn.light->color);
		}
		if (lst->specular)
		{
			light = specular_transform(ray, inter, scn, lst);
			brightness(&rgb, light, scn.light->color);
		}
		scn.light = scn.light->next;
	}
	inter->color = ft_rgb_light(inter->color, rgb);
}

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