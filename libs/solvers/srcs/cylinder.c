#include "solvers.h"

static t_bool	cyl_is_hit(double x[2], t_v3d origin, t_v3d dir, t_obj *cyl)
{
	t_v3d	v;
	t_v3d	u;
	double	qr[3];

	v = ft_scalar_v3d(ft_dot_v3d(dir, cyl->elm.cyl.dir), cyl->elm.cyl.dir);
	v = ft_minus_v3d(dir, v);
	u = ft_scalar_v3d(ft_dot_v3d(ft_minus_v3d(origin, cyl->elm.cyl.centre),
				cyl->elm.cyl.dir),cyl->elm.cyl.dir);
	u = ft_minus_v3d(ft_minus_v3d(origin, cyl->elm.cyl.centre), u);
	qr[0] = ft_dot_v3d(v, v);
	qr[1] = 2 * ft_dot_v3d(v, u);
	qr[2] = ft_dot_v3d(u, u) - (cyl->elm.cyl.radius * cyl->elm.cyl.radius);
	x[0] = (-qr[1] + sqrt((qr[1] * qr[1]) - 4 * qr[0] * qr[2])) / (2 * qr[0]);
	x[1] = (-qr[1] - sqrt((qr[1] * qr[1]) - 4 * qr[0] * qr[2])) / (2 * qr[0]);
	if ((x[0] != x[0] && x[1] != x[1]) || (x[0] < EPSILON && x[1] < EPSILON))
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return (FALSE);
	}
	return (TRUE);
}

static t_v3d	cyl_orientation(double x2[2], t_v3d from, t_v3d to, t_obj *cyl)
{
	double	dist;
	double	x;

	if ((cyl->elm.cyl.d1 >= 0 && cyl->elm.cyl.d1 <= cyl->elm.cyl.height
			&& x2[0] > EPSILON) && (cyl->elm.cyl.d2 >= 0
			&& cyl->elm.cyl.d2 <= cyl->elm.cyl.height && x2[1] > EPSILON))
	{
		dist = x2[0] < x2[1] ? cyl->elm.cyl.d1 : cyl->elm.cyl.d2;
		x = x2[0] < x2[1] ? x2[0] : x2[1];
	}
	else if (cyl->elm.cyl.d1 >= 0 && cyl->elm.cyl.d1 <= cyl->elm.cyl.height
			&& x2[0] > EPSILON)
	{
		dist = cyl->elm.cyl.d1;
		x = x2[0];
	}
	else
	{
		dist = cyl->elm.cyl.d2;
		x = x2[1];
	}
	x2[0] = x;
	return (ft_normal_v3d(ft_minus_v3d(ft_minus_v3d(ft_scalar_v3d(x, to),
					ft_scalar_v3d(dist, cyl->elm.cyl.dir)), ft_minus_v3d(cyl->elm.cyl.centre, from))));
}

static double	body_intersect(t_v3d o, t_v3d d, t_v3d *normal, t_obj *lst)
{
	double	x2[2];

	if (cyl_is_hit(x2, o, d, lst) == FALSE)
		return (INFINITY);
	lst->elm.cyl.d1 = ft_dot_v3d(lst->elm.cyl.dir, ft_minus_v3d(ft_scalar_v3d(x2[0], d),
				ft_minus_v3d(lst->elm.cyl.centre, o)));
	lst->elm.cyl.d2 = ft_dot_v3d(lst->elm.cyl.dir, ft_minus_v3d(ft_scalar_v3d(x2[1], d),
				ft_minus_v3d(lst->elm.cyl.centre, o)));
	if (!((lst->elm.cyl.d1 >= 0 && lst->elm.cyl.d1 <= lst->elm.cyl.height
		&& x2[0] > EPSILON) || (lst->elm.cyl.d2 >= 0
		&& lst->elm.cyl.d2 <= lst->elm.cyl.height && x2[0] > EPSILON)))
		return (INFINITY);
	*normal = cyl_orientation(x2, o, d, lst);
	return (x2[0]);
}

static double	top_intersect(t_v3d o, t_v3d d, t_obj *lst)
{
	double	id1;
	double	id2;
	t_v3d	p[3];

	p[C_DIST] = ft_plus_v3d(lst->elm.cyl.centre, ft_scalar_v3d(lst->elm.cyl.height, lst->elm.cyl.dir));
	id1 = plane_hit(o, d, lst->elm.cyl.centre, lst->elm.cyl.dir);
	id2 = plane_hit(o, d, p[C_DIST], lst->elm.cyl.dir);
	if (id1 < INFINITY || id2 < INFINITY)
	{
		p[IP1] = ft_plus_v3d(o, ft_scalar_v3d(id1, d));
		p[IP2] = ft_plus_v3d(o, ft_scalar_v3d(id2, d));
		if ((id1 < INFINITY && ft_distance_v3d(p[IP1], lst->elm.cyl.centre) <= lst->elm.cyl.radius)
			&& (id2 < INFINITY && ft_distance_v3d(p[IP2], p[C_DIST]) <= lst->elm.cyl.radius))
			if (id1 < id2)
				return (id1);
			else
				return (id2);
		else if (id1 < INFINITY
			&& ft_distance_v3d(p[IP1], lst->elm.cyl.centre) <= lst->elm.cyl.radius)
			return (id1);
		else if (id2 < INFINITY && ft_distance_v3d(p[IP2], p[C_DIST]) <= lst->elm.cyl.radius)
			return (id2);
		return (INFINITY);
	}
	return (INFINITY);
}

double	cylinder_solver(t_v3d from, t_v3d dir, t_obj *cyl)
{
	double	cylinder_inter;
	double	caps_inter;
	t_v3d	cy_normal;

	cylinder_inter = body_intersect(from, dir, &cy_normal, cyl);
	if (cyl->texture == 4)
		caps_inter = INFINITY;
	else
		caps_inter = top_intersect(from, dir, cyl);
	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
	{
		if (cylinder_inter < caps_inter)
		{
			cyl->normal = cy_normal;
			return (cylinder_inter);
		}
		cyl->normal = cyl->elm.cyl.dir;
		return (caps_inter);
	}
	return (INFINITY);
}
