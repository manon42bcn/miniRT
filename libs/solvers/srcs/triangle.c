#include "solvers.h"

static inline t_bool triangle_hit(t_v3d v1, t_v3d v2, t_v3d v3, t_v3d inter_point)
{
	t_v3d	point1;
	t_v3d	point2;
	t_v3d	point3;

	point1 = ft_minus_v3d(v2, v1);
	point2 = ft_minus_v3d(v3, v1);
	point3 = ft_minus_v3d(inter_point, v1);
	if (ft_cos_v3d(ft_cross_v3d(point1, point2), ft_cross_v3d(point1, point3)) < 0)
		return (TRUE);
	return (FALSE);
}

double			triangle_solver(t_v3d origin, t_v3d dir, t_obj *trg)
{
	double	inter_dist;
	t_v3d	inter_point;

	inter_dist = plane_hit(origin, dir, trg->elm.trg.v1, trg->normal);
	inter_point = ft_plus_v3d(origin, ft_scalar_v3d(inter_dist, dir));
	if (triangle_hit(trg->elm.trg.v1, trg->elm.trg.v2, trg->elm.trg.v3, inter_point))
		return (INFINITY);
	if (triangle_hit(trg->elm.trg.v2, trg->elm.trg.v3, trg->elm.trg.v1, inter_point))
		return (INFINITY);
	if (triangle_hit(trg->elm.trg.v3, trg->elm.trg.v1, trg->elm.trg.v2, inter_point))
		return (INFINITY);
	return (inter_dist);
}
