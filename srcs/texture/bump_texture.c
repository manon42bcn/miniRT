/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:28:10 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/15 01:40:27 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Perform UV mapping for a sphere object.
 *
 * This function calculates the UV coordinates for a point on a sphere's surface
 * based on its local normal vector. It's used for texture mapping on spherical
 * objects.
 *
 * @param local The local normal vector of the point on the sphere's surface.
 * @param uv An array to store the resulting UV coordinates
 * 			 (uv[0] = U, uv[1] = V).
 */
static inline void	uv_mapping(t_v3d local, t_dec *uv)
{
	t_dec	phi;
	t_dec	theta;

	phi = atan2l(local.x, local.z);
	theta = asinl(local.y);
	uv[E_U] = 0.5 + phi / (2 * M_PI);
	uv[E_V] = 0.5 - theta / M_PI;
}

/**
 * @brief Apply bump mapping to an intersection point on a textured sphere.
 *
 * This function applies bump mapping to an intersection point on a textured
 * sphere based on the sphere's UV mapping. It reads the texture color at the
 * corresponding UV coordinates and returns the modified color. If the object
 * doesn't have a texture or is not a sphere, the original color is returned.
 *
 * @param inter The intersection information, including the color and UV
 * 					coordinates.
 * @param hit The intersection point.
 * @param obj The object that was intersected.
 * @param mrt The main ray tracing structure.
 * @return The color of the intersection point with bump mapping applied.
 */
t_rgb	bump_texture(t_inter inter, t_v3d hit, t_obj obj, t_mrt *mrt)
{
	t_v3d	local;
	t_dec	uv[2];
	int		pix[2];
	t_rgb	bump;

	if (obj.bump == FALSE)
		return (inter.color);
	local = ft_normal_v3d(ft_minus_v3d(hit, obj.elm.fig.centre));
	uv_mapping(local, &uv[0]);
	pix[X_C] = uv[E_U] * (obj.xpm.width - 1);
	pix[Y_C] = uv[E_V] * (obj.xpm.height - 1);
	if (pix[X_C] < 0)
		pix[X_C] = 0;
	if (pix[X_C] >= obj.xpm.width)
		pix[X_C] = obj.xpm.width - 1;
	if (pix[Y_C] < 0)
		pix[Y_C] = 0;
	if (pix[Y_C] >= obj.xpm.height)
		pix[Y_C] = obj.xpm.height - 1;
	bump = (*(int *)(obj.xpm.addr + (pix[Y_C]
					* obj.xpm.ll + pix[X_C] * (obj.xpm.bbp / 8))));
	if (mrt->sel_obj && mrt->sel_obj->color == obj.color)
		return (ft_invert_color(bump));
	return (bump);
}
