/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 01:09:05 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/24 01:09:07 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

void	hyper_quad(double *coef, t_obj *obj, t_v3d origin, t_v3d dir)
{
	t_hyper	hyper;

	hyper = obj->elm.hy;
	coef[E_A] = (dir.x * dir.x / (hyper.a * hyper.a))
		+ (dir.y * dir.y / (hyper.b * hyper.b))
		- (dir.z * dir.z / (hyper.c * hyper.c));
	coef[E_B] = 2 * (dir.x * (origin.x - hyper.centre.x) / (hyper.a * hyper.a)
			+ dir.y * (origin.y - hyper.centre.y) / (hyper.b * hyper.b)
			- dir.z * (origin.z - hyper.centre.z) / (hyper.c * hyper.c));
	coef[E_C] = ((origin.x - hyper.centre.x)
			* (origin.x - hyper.centre.x) / (hyper.a * hyper.a))
		+ ((origin.y - hyper.centre.y) * (origin.y - hyper.centre.y)
			/ (hyper.b * hyper.b))
		- ((origin.z - hyper.centre.z) * (origin.z - hyper.centre.z)
			/ (hyper.c * hyper.c)) - 1.0;
}

double	hyper_solver(t_v3d origin, t_v3d dir, t_obj *obj)
{
	double	coef[3];
	double	t[2];

	hyper_quad(&coef[0], obj, origin, dir);
	if (!quadratic(&coef[0], &t[0]))
		return (INFINITY);
	return (t[0]);
}
