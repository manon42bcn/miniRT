/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:30:53 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/25 19:30:55 by mporras-         ###   ########.fr       */
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

double ellipsoid_solver(t_v3d origin, t_v3d dir, t_obj *obj)
{
	// Extracción de información específica del ellipsoide desde el objeto.
	t_ellip ellip = obj->elm.elp;

	t_v3d O = ft_minus_v3d(origin, ellip.centre); // Offset del origen del rayo.

	double A = (dir.x * dir.x / (ellip.rx * ellip.rx)) +
			   (dir.y * dir.y / (ellip.ry * ellip.ry)) +
			   (dir.z * dir.z / (ellip.rz * ellip.rz));

	double B = 2 * (O.x * dir.x / (ellip.rx * ellip.rx)) +
			   2 * (O.y * dir.y / (ellip.ry * ellip.ry)) +
			   2 * (O.z * dir.z / (ellip.rz * ellip.rz));

	double C = (O.x * O.x / (ellip.rx * ellip.rx)) +
			   (O.y * O.y / (ellip.ry * ellip.ry)) +
			   (O.z * O.z / (ellip.rz * ellip.rz)) - 1;

	double t0, t1;
	if (!solve_quadratic(A, B, C, &t0, &t1))
		return INFINITY;

	// Retorna la intersección más cercana que esté en frente de la cámara.
	if (t0 > 0)
		return t0;
	if (t1 > 0)
		return t1;
	return INFINITY;
}



