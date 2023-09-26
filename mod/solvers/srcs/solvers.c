/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solvers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 13:00:58 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/04 13:01:00 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solvers.h"

/**
 * @brief Outputs an error message to the standard error stream and
 * then exits the program.
 *
 * @param message A pointer to the string message to be displayed.
 */
static inline void	solver_error(char *message)
{
	ft_putstr_fd("miniRT ERROR [solver module]", STDERR_FILENO);
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(ERROR);
}

#ifdef BONUS

/**
 * @brief Returns a pointer to the appropriate solver function for a
 * specified geometric object type (Bonus version).
 *
 * Maps an index representing the type of an object to its corresponding
 * solver function. This solver function is used to determine if and
 * how a ray intersects the object. Includes solvers for advanced
 * geometric shapes.
 *
 * @param index Integer representing the object type.
 * @return A pointer to the solver function corresponding to the given
 * object type.
 */
t_solver	get_solver(int index)
{
	static t_solver	solve[] = {&sphere_solver, &plane_solver,
		&cylinder_solver, &square_solver,
		&triangle_solver, &box_solver,
		&pyramid_solver, &cone_solver, &hyper_solver, &parab_solver,
		&ellipsoid_solver};

	if (index > (int)(sizeof(solve) / sizeof (t_solver)))
		solver_error("object id out of range to get solver");
	return (solve[index]);
}

#else

/**
 * @brief Returns a pointer to the appropriate solver function for a
 * specified geometric object type (Standard version).
 *
 * Similar to the Bonus version, but limited to basic geometric shapes.
 *
 * @param index Integer representing the object type.
 * @return A pointer to the solver function corresponding to the
 * given object type.
 */
t_solver	get_solver(int index)
{
	static t_solver	solve[] = {&sphere_solver, &plane_solver,
		&cylinder_solver};

	if (index > (int)(sizeof(solve) / sizeof (t_solver)))
		solver_error("object id out of range to get solver");
	return (solve[index]);
}

#endif

/**
 * @brief Solves a quadratic equation defined by the given coefficients.
 *
 * This function attempts to solve a quadratic equation of the form:
 * ax^2 + bx + c = 0, where the coefficients a, b, and c are provided
 * in the `vars` array. If roots exist, they are returned in the `dist` array.
 *
 * @param vars An array containing the coefficients of the equation:
 *        - vars[0] (or vars[E_A]) is 'a'
 *        - vars[1] (or vars[E_B]) is 'b'
 *        - vars[2] (or vars[E_C]) is 'c'
 * @param dist An array where the roots (if they exist) will be stored.
 *        - dist[0] (or dist[T_0]) will contain the smaller root
 *        - dist[1] (or dist[T_1]) will contain the larger root
 *        if there is no roots for the equation, both values will
 *        store INFINITY
 *
 * @return Returns TRUE if real roots exist, FALSE otherwise.
 */
t_bool	quadratic(double *vars, double *dist)
{
	double	discriminant;
	double	q;
	double	tmp;

	if (fabs(vars[E_A]) < EPSILON) { // Si E_A es esencialmente cero
		if (fabs(vars[E_B]) < EPSILON) { // Si E_B también es cero, no hay solución válida
			dist[T_0] = INFINITY;
			dist[T_1] = INFINITY;
			return (FALSE);
		}
		dist[T_0] = -vars[E_C] / vars[E_B];
		dist[T_1] = INFINITY;
		return (TRUE);
	}
	discriminant = (vars[E_B] * vars[E_B]) - 4 * (vars[E_A] * vars[E_C]);
	if (discriminant < 0)
	{
		dist[T_0] = INFINITY;
		dist[T_1] = INFINITY;
		return (FALSE);
	}
	if (vars[E_B] > 0)
		q = -0.5f * (vars[E_B] + sqrt(discriminant));
	else
		q = -0.5f * (vars[E_B] - sqrt(discriminant));
	dist[T_0] = q / vars[E_A];
	dist[T_1] = vars[E_C] / q;
	if (dist[T_0] > dist[T_1])
	{
		tmp = dist[T_0];
		dist[T_0] = dist[T_1];
		dist[T_1] = tmp;
	}
	return (TRUE);
}
