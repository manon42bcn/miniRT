#include "minirt.h"

t_solver    get_solver(int index)
{
	static t_solver solve[] = {&sphere_solver, &plane_solver,
	                           &cylinder_solver, &square_solver,
	                           &triangle_solver, &cube_solver,
	                           &pyramid_solver};
	if (index > (int)(sizeof(solve) / sizeof (t_solver)))
		msg_error_exit("object id out of range to get solver");
	return (solve[index]);
}
