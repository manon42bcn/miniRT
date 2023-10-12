/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:24:47 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/25 16:24:52 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

t_v3d	parab_normal(t_v3d dir, t_v3d hit, t_obj *obj)
{
	t_v3d normal;

	(void)dir;
	normal.x = 2 * hit.x;
	normal.y = -4 * obj->elm.prb.focal_dist;
	normal.z = 2 * hit.z;
	return (ft_normal_v3d(normal));
}

static int solve_quadratic(double a, double b, double c, double *t0, double *t1) {
	double discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
		return 0; // no real roots

	double q = (b > 0) ?
			   -0.5 * (b + sqrt(discriminant)) :
			   -0.5 * (b - sqrt(discriminant));

	*t0 = q / a;
	*t1 = c / q;

	if (*t0 > *t1) {
		double temp = *t0;
		*t0 = *t1;
		*t1 = temp;
	}

	return 1;
}

double parab_solver(t_v3d origin, t_v3d dir, t_obj *obj) {
	t_parab parab = obj->elm.prb;

	// Primero, vamos a trasladar el sistema de coordenadas al centro del paraboloide.
	t_v3d p0 = ft_minus_v3d(origin, parab.centre);

	double k = 1.0 / (4.0 * parab.focal_dist);

	double a = dir.x * dir.x + dir.y * dir.y;
	double b = 2.0 * p0.x * dir.x + 2.0 * p0.y * dir.y - dir.z;
	double c = p0.x * p0.x + p0.y * p0.y - 4.0 * k * p0.z;

	double t0, t1;

	if (!solve_quadratic(a, b, c, &t0, &t1))
		return INFINITY;

	// Ahora, vamos a verificar si las intersecciones están dentro de las alturas deseadas.
	double z0 = p0.z + t0 * dir.z;
	double z1 = p0.z + t1 * dir.z;

	double z_min = -parab.height / 2.0;
	double z_max = parab.height / 2.0;

	if (z0 < z_min || z0 > z_max) {
		if (z1 < z_min || z1 > z_max) {
			return INFINITY;  // Ambas intersecciones están fuera de los límites.
		} else {
			return t1;
		}
	}

	return t0;  // La primera intersección es válida y más cercana.
}

