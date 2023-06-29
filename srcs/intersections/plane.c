#include "minirt.h"

double			plane_hit(t_v3d origin, t_v3d dir, t_v3d plane_centre, t_v3d plane_dir)
{
	double	point;
	double	base;

	base = ft_dot_v3d(plane_dir, dir);
	if (fabs(base) < EPSILON)
		return (INFINITY);
	point = (ft_dot_v3d(plane_dir, ft_minus_v3d(plane_centre, origin))) / base;
	if (point > 0)
		return (point);
	return (INFINITY);
}

double			plane_solver(t_v3d origin, t_v3d dir, t_obj *obj)
{
	return (plane_hit(origin, dir, obj->elm.pl.centre, obj->normal));
}
