/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:28:10 by mporras-          #+#    #+#             */
/*   Updated: 2023/10/10 10:28:17 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	sphere_uv_mapping(t_v3d local, double *uv)
{
	double	phi;
	double	theta;

	phi = atan2(local.y, local.x);
	theta = asin(local.z);
	uv[E_U] = 0.5 + phi / (2 * M_PI);
	uv[E_V] = 0.5 - theta / M_PI;
}

t_rgb	bump_texture(t_inter inter, t_v3d hit, t_obj *obj, t_mrt *mrt)
{
	t_v3d	local;
	double	uv[2];
	int		pix[2];
	t_rgb	bump;

	if (!inter.hitted || obj->type != SPHERE || obj->bump == FALSE)
		return (inter.color);
	local = ft_normal_v3d(ft_minus_v3d(hit, obj->elm.sph.centre));
	sphere_uv_mapping(local, &uv[0]);
	pix[X_C] = uv[E_U] * (obj->xpm.width - 1);
	pix[Y_C] = uv[E_V] * (obj->xpm.height - 1);
	if (pix[X_C] < 0)
		pix[X_C] = 0;
	if (pix[X_C] >= obj->xpm.width)
		pix[X_C] = obj->xpm.width - 1;
	if (pix[Y_C] < 0)
		pix[Y_C] = 0;
	if (pix[Y_C] >= obj->xpm.height)
		pix[Y_C] = obj->xpm.height - 1;
	bump = (*(int *)(obj->xpm.addr + (pix[Y_C]
					* obj->xpm.ll + pix[X_C] * (obj->xpm.bbp / 8))));
	if (mrt->sel_obj && mrt->sel_obj->color == obj->color)
		return (ft_invert_color(bump));
	return (bump);
}
