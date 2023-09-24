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
		&pyramid_solver, &cone_solver, &hyper_solver};

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
