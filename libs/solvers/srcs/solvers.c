#include "solvers.h"

static inline void	solver_error(char *message)
{
	ft_putstr_fd("miniRT ERROR [solver module]", STDERR_FILENO);
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(ERROR);
}

t_solver    get_solver(int index)
{
	static t_solver solve[] = {&sphere_solver, &plane_solver,
	                           &cylinder_solver, &square_solver,
	                           &triangle_solver, &cube_solver,
	                           &pyramid_solver};

	if (index > (int)(sizeof(solve) / sizeof (t_solver)))
		solver_error("object id out of range to get solver");
	return (solve[index]);
}
