/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 00:27:44 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/27 00:27:46 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Solves a linear equation of the form Bx + C = 0.
 *
 * @param coef Array containing the coefficients [B, C].
 * @param dist Array where the solution will be stored.
 * @return t_bool Returns TRUE if a solution is found, otherwise returns FALSE.
 */
static inline t_bool	lineal(double *coef, double *dist)
{
	if (fabs(coef[E_B]) < EPSILON)
	{
		dist[T_0] = INFINITY;
		dist[T_1] = INFINITY;
		return (FALSE);
	}
	dist[T_0] = -coef[E_C] / coef[E_B];
	dist[T_1] = INFINITY;
	return (TRUE);
}

/**
 * @brief Swaps the values of dist[T_0] and dist[T_1] if dist[T_0] > dist[T_1].
 *
 * @param dist Array containing the two distance values.
 */
static inline void	quad_swap(double *dist)
{
	double	tmp;

	if (dist[T_0] > dist[T_1])
	{
		tmp = dist[T_0];
		dist[T_0] = dist[T_1];
		dist[T_1] = tmp;
	}
}

/**
 * @brief Solves a quadratic equation defined by the given coefficients.
 *
 * This function attempts to solve a quadratic equation of the form:
 * ax^2 + bx + c = 0, where the coefficients a, b, and c are provided
 * in the `vars` array. If roots exist, they are returned in the `dist` array.
 * If the coefficient A is near zero, it delegates the solution to the lineal
 * function.
 *
 * @param coef An array containing the coefficients of the equation:
 *        - coef[0] (or coef[E_A]) is 'a'
 *        - coef[1] (or coef[E_B]) is 'b'
 *        - coef[2] (or coef[E_C]) is 'c'
 * @param dist An array where the roots (if they exist) will be stored.
 *        - dist[0] (or dist[T_0]) will contain the smaller root
 *        - dist[1] (or dist[T_1]) will contain the larger root
 *        if there is no roots for the equation, both values will
 *        store INFINITY
 *
 * @return Returns TRUE if real roots exist, FALSE otherwise.
 */
t_bool	quadratic(double *coef, double *dist)
{
	double	discriminant;
	double	q;

	if (fabs(coef[E_A]) < EPSILON)
		return (lineal(coef, dist));
	discriminant = (coef[E_B] * coef[E_B]) - 4 * (coef[E_A] * coef[E_C]);
	if (discriminant < 0)
	{
		dist[T_0] = INFINITY;
		dist[T_1] = INFINITY;
		return (FALSE);
	}
	if (coef[E_B] > 0)
		q = -0.5f * (coef[E_B] + sqrt(discriminant));
	else
		q = -0.5f * (coef[E_B] - sqrt(discriminant));
	dist[T_0] = q / coef[E_A];
	dist[T_1] = coef[E_C] / q;
	quad_swap(&dist[0]);
	return (TRUE);
}