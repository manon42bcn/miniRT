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


static int solve_quadratic(double a, double b, double c, double *t0, double *t1)
{
	double discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return 0; // no real roots

	double q = (b > 0) ?
			   -0.5 * (b + sqrt(discriminant)) :
			   -0.5 * (b - sqrt(discriminant));

	*t0 = q / a;
	*t1 = c / q;

	if (*t0 > *t1)
	{
		double temp = *t0;
		*t0 = *t1;
		*t1 = temp;
	}

	return 1;
}

double hyper_solver(t_v3d origin, t_v3d dir, t_obj *obj)
{
	t_hyper hyper = obj->elm.hy;

	double a = (dir.x * dir.x / (hyper.a * hyper.a)) +
			   (dir.y * dir.y / (hyper.b * hyper.b)) -
			   (dir.z * dir.z / (hyper.c * hyper.c));

	double b = 2 * (dir.x * (origin.x - hyper.centre.x) / (hyper.a * hyper.a) +
					dir.y * (origin.y - hyper.centre.y) / (hyper.b * hyper.b) -
					dir.z * (origin.z - hyper.centre.z) / (hyper.c * hyper.c));

	double c = ((origin.x - hyper.centre.x) * (origin.x - hyper.centre.x) / (hyper.a * hyper.a)) +
			   ((origin.y - hyper.centre.y) * (origin.y - hyper.centre.y) / (hyper.b * hyper.b)) -
			   ((origin.z - hyper.centre.z) * (origin.z - hyper.centre.z) / (hyper.c * hyper.c)) - 1.0;

	double t0, t1;
	if (!solve_quadratic(a, b, c, &t0, &t1))
		return INFINITY;

	// Coordenadas de intersección.
	t_v3d point_t0 = ft_plus_v3d(origin, ft_scalar_v3d(t0, dir));
	t_v3d point_t1 = ft_plus_v3d(origin, ft_scalar_v3d(t1, dir));

	double min_val, max_val;

	if (fabs(hyper.dir.x) > EPSILON) {  // Orientado a lo largo del eje X.
		min_val = hyper.centre.y - hyper.height / 2.0;
		max_val = hyper.centre.y + hyper.height / 2.0;

		if (point_t0.y >= min_val && point_t0.y <= max_val) return t0;
		if (point_t1.y >= min_val && point_t1.y <= max_val) return t1;

	} else if (fabs(hyper.dir.y) > EPSILON) {  // Orientado a lo largo del eje Y.
		min_val = hyper.centre.z - hyper.height / 2.0;
		max_val = hyper.centre.z + hyper.height / 2.0;

		if (point_t0.z >= min_val && point_t0.z <= max_val) return t0;
		if (point_t1.z >= min_val && point_t1.z <= max_val) return t1;

	} else {  // Orientado a lo largo del eje Z.
		min_val = hyper.centre.x - hyper.height / 2.0;
		max_val = hyper.centre.x + hyper.height / 2.0;

		if (point_t0.x >= min_val && point_t0.x <= max_val) return t0;
		if (point_t1.x >= min_val && point_t1.x <= max_val) return t1;
	}

	return INFINITY;
}

