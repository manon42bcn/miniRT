#include "minirt.h"

static int		solve_cylinder(double x[2], t_v3d o, t_v3d d, t_obj *lst)
{
	t_v3d	v;
	t_v3d	u;
	double	a;
	double	b;
	double	c;

	v = ft_scalar_v3d(ft_dot_v3d(d, lst->elm.cyl.dir), lst->elm.cyl.dir);
	v = ft_minus_v3d(d, v);
	u = ft_scalar_v3d(ft_dot_v3d(ft_minus_v3d(o, lst->elm.cyl.centre), lst->elm.cyl.dir),
	               lst->elm.cyl.dir);
	u = ft_minus_v3d(ft_minus_v3d(o, lst->elm.cyl.centre), u);
	a = ft_dot_v3d(v, v);
	b = 2 * ft_dot_v3d(v, u);
	c = ft_dot_v3d(u, u) - pow(lst->elm.cyl.radius, 2);
	x[0] = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	x[1] = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
	if ((x[0] != x[0] && x[1] != x[1]) || (x[0] < EPSILON && x[1] < EPSILON))
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return (0);
	}
	return (1);
}

static t_v3d		calc_cy_normal(double x2[2], t_v3d o, t_v3d d, t_obj *lst)
{
	double	dist;
	double	x;

	if ((lst->elm.cyl.d1 >= 0 && lst->elm.cyl.d1 <= lst->elm.cyl.height
	     && x2[0] > EPSILON) && (lst->elm.cyl.d2 >= 0
	                             && lst->elm.cyl.d2 <= lst->elm.cyl.height && x2[1] > EPSILON))
	{
		dist = x2[0] < x2[1] ? lst->elm.cyl.d1 : lst->elm.cyl.d2;
		x = x2[0] < x2[1] ? x2[0] : x2[1];
	}
	else if (lst->elm.cyl.d1 >= 0 && lst->elm.cyl.d1 <= lst->elm.cyl.height
	         && x2[0] > EPSILON)
	{
		dist = lst->elm.cyl.d1;
		x = x2[0];
	}
	else
	{
		dist = lst->elm.cyl.d2;
		x = x2[1];
	}
	x2[0] = x;
	return (ft_normal_v3d(ft_minus_v3d(ft_minus_v3d(ft_scalar_v3d(x, d),
	                                        ft_scalar_v3d(dist, lst->elm.cyl.dir)), ft_minus_v3d(lst->elm.cyl.centre, o))));
}

static double	cy_intersection(t_v3d o, t_v3d d, t_v3d *normal, t_obj *lst)
{
	double	x2[2];

	if (solve_cylinder(x2, o, d, lst) == 0)
		return (INFINITY);
	lst->elm.cyl.d1 = ft_dot_v3d(lst->elm.cyl.dir, ft_minus_v3d(ft_scalar_v3d(x2[0], d),
	                                                     ft_minus_v3d(lst->elm.cyl.centre, o)));
	lst->elm.cyl.d2 = ft_dot_v3d(lst->elm.cyl.dir, ft_minus_v3d(ft_scalar_v3d(x2[1], d),
	                                                     ft_minus_v3d(lst->elm.cyl.centre, o)));
	if (!((lst->elm.cyl.d1 >= 0 && lst->elm.cyl.d1 <= lst->elm.cyl.height
	       && x2[0] > EPSILON) || (lst->elm.cyl.d2 >= 0
	                               && lst->elm.cyl.d2 <= lst->elm.cyl.height && x2[0] > EPSILON)))
		return (INFINITY);
	*normal = calc_cy_normal(x2, o, d, lst);
	return (x2[0]);
}

static double	caps_intersection(t_v3d o, t_v3d d, t_obj *lst)
{
	double	id1;
	double	id2;
	t_v3d	ip1;
	t_v3d	ip2;
	t_v3d	c2;

	c2 = ft_plus_v3d(lst->elm.cyl.centre, ft_scalar_v3d(lst->elm.cyl.height, lst->elm.cyl.dir));
	id1 = plane_hit(o, d, lst->elm.cyl.centre, lst->elm.cyl.dir);
	id2 = plane_hit(o, d, c2, lst->elm.cyl.dir);
	if (id1 < INFINITY || id2 < INFINITY)
	{
		ip1 = ft_plus_v3d(o, ft_scalar_v3d(id1, d));
		ip2 = ft_plus_v3d(o, ft_scalar_v3d(id2, d));
		if ((id1 < INFINITY && ft_distance_v3d(ip1, lst->elm.cyl.centre) <= lst->elm.cyl.radius)
		    && (id2 < INFINITY && ft_distance_v3d(ip2, c2) <= lst->elm.cyl.radius))
			return (id1 < id2 ? id1 : id2);
		else if (id1 < INFINITY
		         && ft_distance_v3d(ip1, lst->elm.cyl.centre) <= lst->elm.cyl.radius)
			return (id1);
		else if (id2 < INFINITY && ft_distance_v3d(ip2, c2) <= lst->elm.cyl.radius)
			return (id2);
		return (INFINITY);
	}
	return (INFINITY);
}

double			cylinder_solver(t_v3d o, t_v3d d, t_obj *lst)
{
	double	cylinder_inter;
	double	caps_inter;
	t_v3d	cy_normal;

	cylinder_inter = cy_intersection(o, d, &cy_normal, lst);
	if (lst->texture == 4)
		caps_inter = INFINITY;
	else
		caps_inter = caps_intersection(o, d, lst);
	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
	{
		if (cylinder_inter < caps_inter)
		{
			lst->normal = cy_normal;
			return (cylinder_inter);
		}
		lst->normal = lst->elm.cyl.dir;
		return (caps_inter);
	}
	return (INFINITY);
}



//static inline t_bool	cyl_is_hit(double x[2], t_v3d origin, t_v3d d,
//		t_obj *cyl)
//{
//	t_v3d	v;
//	t_v3d	u;
//	double q[3];
//
//	v = ft_scalar_v3d(ft_dot_v3d(d, cyl->elm.cyl.dir), cyl->elm.cyl.dir);
//	v = ft_minus_v3d(d, v);
//	u = ft_scalar_v3d(ft_dot_v3d(ft_minus_v3d(origin, cyl->elm.cyl.centre),
//		cyl->elm.cyl.dir), cyl->elm.cyl.dir);
//	u = ft_minus_v3d(ft_minus_v3d(origin, cyl->elm.cyl.centre), u);
//	q[0] = ft_dot_v3d(v, v);
//	q[1] = 2 * ft_dot_v3d(v, u);
//	q[2] = ft_dot_v3d(u, u) - (cyl->elm.cyl.radius * cyl->elm.cyl.radius);
//	x[0] = (-q[1] + sqrt((q[1] * q[1]) - 4 * q[0] * q[2])) / (2 * q[0]);
//	x[1] = (-q[1] - sqrt((q[1] * q[1]) - 4 * q[0] * q[2])) / (2 * q[0]);
//	if ((x[0] != x[0] && x[1] != x[1]) || (x[0] < EPSILON && x[1] < EPSILON))
//	{
//		x[0] = INFINITY;
//		x[1] = INFINITY;
//		return (FALSE);
//	}
//	return (TRUE);
//}
//
//static inline t_v3d	cylinder_orient(double x2[2], t_v3d origin, t_v3d dir, t_obj *cyl)
//{
//	double	dist;
//	double	x;
//
//	if ((cyl->elm.cyl.d1 >= 0 && cyl->elm.cyl.d1 <= cyl->elm.cyl.height
//				&& x2[0] > EPSILON) && (cyl->elm.cyl.d2 >= 0
//				&& cyl->elm.cyl.d2 <= cyl->elm.cyl.height && x2[1] > EPSILON))
//	{
//		dist = x2[0] < x2[1] ? cyl->elm.cyl.d1 : cyl->elm.cyl.d2;
//		x = x2[0] < x2[1] ? x2[0] : x2[1];
//	}
//	else if (cyl->elm.cyl.d1 >= 0 && cyl->elm.cyl.d1 <= cyl->elm.cyl.height
//														&& x2[0] > EPSILON)
//	{
//		dist = cyl->elm.cyl.d1;
//		x = x2[0];
//	}
//	else
//	{
//		dist = cyl->elm.cyl.d2;
//		x = x2[1];
//	}
//	x2[0] = x;
//	return (ft_normal_v3d(ft_minus_v3d(ft_minus_v3d(ft_scalar_v3d(x, dir),
//			ft_scalar_v3d(dist, cyl->elm.cyl.dir)), ft_minus_v3d(cyl->elm.cyl.centre, origin))));
//}
//
//static inline double	cylinder_hit(t_v3d origin, t_v3d dir, t_v3d *normal, t_obj *cyl)
//{
//	double	x2[2];
//
//	if (cyl_is_hit(x2, origin, dir, cyl) == 0)
//		return (INFINITY);
//	cyl->elm.cyl.d1 = ft_dot_v3d(cyl->elm.cyl.dir, ft_minus_v3d(ft_scalar_v3d(x2[0], dir),
//												ft_minus_v3d(cyl->elm.cyl.centre, origin)));
//	cyl->elm.cyl.d2 = ft_dot_v3d(cyl->elm.cyl.dir, ft_minus_v3d(ft_scalar_v3d(x2[1], dir),
//												ft_minus_v3d(cyl->elm.cyl.centre, origin)));
//	if (!((cyl->elm.cyl.d1 >= 0 && cyl->elm.cyl.d1 <= cyl->elm.cyl.height
//					&& x2[0] > EPSILON) || (cyl->elm.cyl.d2 >= 0
//					&& cyl->elm.cyl.d2 <= cyl->elm.cyl.height && x2[0] > EPSILON)))
//		return (INFINITY);
//	*normal = cylinder_orient(x2, origin, dir, cyl);
//	return (x2[0]);
//}
//
//static inline double	top_intersection(t_v3d origin, t_v3d dir, t_obj *cyl)
//{
//	double	dist[2];
//	t_v3d	p[3];
//
//	p[TOP_CENTRE] = ft_plus_v3d(cyl->elm.cyl.centre, ft_scalar_v3d(cyl->elm.cyl.height, cyl->elm.cyl.dir));
//	dist[0] = plane_hit(origin, dir, cyl->elm.cyl.centre, cyl->elm.cyl.dir);
//	dist[1] = plane_hit(origin, dir, p[TOP_CENTRE], cyl->elm.cyl.dir);
//	if (dist[0] < INFINITY || dist[1] < INFINITY)
//	{
//		p[IP1] = ft_plus_v3d(origin, ft_scalar_v3d(dist[0], dir));
//		p[IP2] = ft_plus_v3d(origin, ft_scalar_v3d(dist[1], dir));
//		if ((dist[0] < INFINITY && ft_distance_v3d(p[IP1], p[TOP_CENTRE]) <= cyl->elm.cyl.radius)
//				&& (dist[1] < INFINITY && ft_distance_v3d(p[IP2], p[TOP_CENTRE]) <= cyl->elm.cyl.radius))
//			return (dist[0] < dist[1] ? dist[0] : dist[1]);
//		else if (dist[0] < INFINITY
//						&& ft_distance_v3d(p[IP1], cyl->elm.cyl.centre) < cyl->elm.cyl.radius)
//			return (dist[0]);
//		else if (dist[1] < INFINITY && ft_distance_v3d(p[IP2], p[TOP_CENTRE]) < cyl->elm.cyl.radius)
//			return (dist[1]);
//		return (INFINITY);
//	}
//	return (INFINITY);
//}
//
//double			cylinder_solver(t_v3d origin, t_v3d dir, t_obj *cyl)
//{
//	double	cylinder_inter;
//	double	caps_inter;
//	t_v3d	cy_normal;
//
//	cylinder_inter = cylinder_hit(origin, dir, &cy_normal, cyl);
//	if (cyl->texture == 4)
//		caps_inter = INFINITY;
//	else
//		caps_inter = top_intersection(origin, dir, cyl);
//	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
//	{
//		if (cylinder_inter < caps_inter)
//		{
//			cyl->normal = cy_normal;
//			return (cylinder_inter);
//		}
//		cyl->normal = cyl->elm.cyl.dir;
//		return (caps_inter);
//	}
////	printf("%f inter\n", cylinder_inter);
//	return (INFINITY);
//}
