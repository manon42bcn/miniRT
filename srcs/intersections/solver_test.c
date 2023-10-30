#include "minirt.h"

t_v3d	cylinder_normal_test(t_v3d dir, t_v3d hit, t_inter *inter)
{
	t_v3d	normal;
	t_v3d	local_hit;
	double	dot;

	local_hit = ft_minus_v3d(hit, inter->obj->elm.cyl.centre);
	dot = ft_dot_v3d(local_hit, inter->obj->elm.cyl.dir);
	if (dot < EPSILON || fabs(dot - inter->obj->elm.cyl.height) < EPSILON)
	{
		if (ft_cos_v3d(dir, inter->obj->elm.cyl.dir) > 0)
			return (ft_scalar_v3d(-1, inter->obj->elm.cyl.dir));
		else
			return (inter->obj->elm.cyl.dir);
	}
	else
	{
		normal = ft_minus_v3d(local_hit,
							  ft_scalar_v3d(dot, inter->obj->elm.cyl.dir));
		normal = ft_normal_v3d(normal);
	}
	return (normal);
}

/**
 * @brief Compute the intersection points given the intersection distances.
 *
 * @param p[] Array to store computed intersection points.
 * @param o_d[] Array containing starting point of the ray (o_d[0])
 * and its direction (o_d[1]).
 * @param id1 Intersection distance for the first intersection.
 * @param id2 Intersection distance for the second intersection.
 */
static inline void	compute_p_values(t_v3d p[], t_v3d o_d[],
									   double id1, double id2)
{
	p[IP1] = ft_plus_v3d(o_d[0], ft_scalar_v3d(id1, o_d[1]));
	p[IP2] = ft_plus_v3d(o_d[0], ft_scalar_v3d(id2, o_d[1]));
}

/**
 * @brief Check if a point is within a given distance from the cylinder center.
 *
 * @param id Intersection distance.
 * @param point Intersection point.
 * @param centre Center of the cylinder.
 * @param radius Radius of the cylinder.
 * @return Returns 1 if within range, 0 otherwise.
 */
static inline int	is_within_range(double id, t_v3d point,
									 t_v3d centre, double radius)
{
	return (id < INFINITY && ft_distance_v3d(point, centre) <= radius);
}

/**
 * @brief Determine the appropriate intersection distance.
 *
 * Given two potential intersections, determine which is the correct one.
 * The function will also ensure the intersection is within the
 * cylinder's bounds.
 *
 * @param id1 Intersection distance for the first intersection.
 * @param id2 Intersection distance for the second intersection.
 * @param p[] Intersection points.
 * @param lst The list of objects in the scene.
 * @return The correct intersection distance, or INFINITY if
 * no valid intersection.
 */
static inline double	handle_intersection(double id1, double id2,
											t_v3d p[], t_cylinder cyl)
{
	if (is_within_range(id1, p[IP1], cyl.centre, cyl.radius)
		&& is_within_range(id2, p[IP2], p[C_DIST], cyl.radius))
	{
		if (id1 < id2)
			return (id1);
		else
			return (id2);
	}
	if (is_within_range(id1, p[IP1], cyl.centre, cyl.radius))
		return (id1);
	if (is_within_range(id2, p[IP2], p[C_DIST], cyl.radius))
		return (id2);
	return (INFINITY);
}

/**
 * @brief Main solver function for intersections with the top of the cylinder.
 *
 * Computes intersections against the top cap of the cylinder.
 * Uses helper functions to calculate and validate intersection points.
 *
 * @param o Starting point of the ray.
 * @param d Direction of the ray.
 * @param lst The list of objects in the scene.
 * @return The distance from the ray's origin to the intersection point,
 * or INFINITY if no intersection.
 */
double	top_intersect_test(t_v3d o, t_v3d d, t_cylinder cyl)
{
	double	id1;
	double	id2;
	t_v3d	p[3];
	t_v3d	o_d[2];

	p[C_DIST] = ft_plus_v3d(cyl.centre,ft_scalar_v3d(cyl.height, cyl.dir));
	o_d[0] = o;
	o_d[1] = d;
	id1 = plane_hit(o, d, cyl.centre, cyl.dir);
	id2 = plane_hit(o, d, p[C_DIST], cyl.dir);
	if (id1 < INFINITY || id2 < INFINITY)
	{
		compute_p_values(p, o_d, id1, id2);
		return (handle_intersection(id1, id2, p, cyl));
	}
	return (INFINITY);
}

static inline t_bool	cyl_is_hit(double x[2], t_v3d origin,
								   t_v3d dir, t_cylinder cyl)
{
	t_v3d	v;
	t_v3d	u;
	double	qr[3];

	v = ft_scalar_v3d(ft_dot_v3d(dir, cyl.dir), cyl.dir);
	v = ft_minus_v3d(dir, v);
	u = ft_scalar_v3d(ft_dot_v3d(ft_minus_v3d(origin, cyl.centre),
				cyl.dir), cyl.dir);
	u = ft_minus_v3d(ft_minus_v3d(origin, cyl.centre), u);
	qr[0] = ft_length_v3d(v);
	qr[1] = 2 * ft_dot_v3d(v, u);
	qr[2] = ft_dot_v3d(u, u) - (cyl.radius * cyl.radius);
	if (!quadratic(&qr[0], &x[0]))
		return (FALSE);
	if (x[0] < EPSILON && x[1] < EPSILON)
	{
		x[0] = INFINITY;
		x[1] = INFINITY;
		return (FALSE);
	}
	return (TRUE);
}

/**
 * @brief Computes the correct distance and intersection point from
 * the two potential intersections.
 *
 * @param cyl The cylinder object.
 * @param x2[2] Intersection points.
 * @param dist Pointer to store the chosen distance.
 * @param x Pointer to store the chosen intersection point.
 */
//static inline void	compute_dist_x(t_cylinder cyl, double x2[2],
//									 double *dist, double *x)
//{
//	*x = x2[1];
//	if ((cyl.d1 >= 0 && cyl.d1 <= cyl.height && x2[0] > EPSILON)
//		&& (cyl.d2 >= 0 && cyl.d2 <= cyl.height && x2[1] > EPSILON))
//	{
//		if (x2[0] < x2[1])
//		{
//			*dist = cyl.d1;
//			*x = x2[0];
//		}
//		else
//			*dist = cyl.d2;
//	}
//	else if (cyl.d1 >= 0 && cyl.d1 <= cyl.height && x2[0] > EPSILON)
//	{
//		*dist = cyl.d1;
//		*x = x2[0];
//	}
//	else
//		*dist = cyl.d2;
//}

//static inline t_v3d	cyl_orientation(double x2[2], t_v3d from,
//									   t_v3d to, t_cylinder cyl)
//{
//	double	dist;
//	double	x;
//
//	compute_dist_x(cyl, x2, &dist, &x);
//	x2[0] = x;
//	return (ft_normal_v3d(ft_minus_v3d(ft_minus_v3d
//											   (ft_scalar_v3d(x, to),
//												ft_scalar_v3d(dist, cyl.dir)),
//									   ft_minus_v3d(cyl.centre, from))));
//}

/**
 * @brief Computes the intersection of the ray with the body of the cylinder.
 *
 * @param o Starting point of the ray.
 * @param d Direction of the ray.
 * @param normal Vector to store the normal at the intersection point.
 * @param lst The list of objects in the scene.
 * @return The distance from the ray's origin to the intersection point,
 * or INFINITY if no intersection.
 */
static inline double	body_intersect(t_v3d o, t_v3d d, t_cylinder cyl)
{
	double	x2[2];

	if (cyl_is_hit(x2, o, d, cyl) == FALSE)
		return (INFINITY);
	cyl.d1 = ft_dot_v3d(cyl.dir,
			ft_minus_v3d(ft_scalar_v3d(x2[0], d),
				ft_minus_v3d(cyl.centre, o)));
	cyl.d2 = ft_dot_v3d(cyl.dir,
			ft_minus_v3d(ft_scalar_v3d(x2[1], d),
				ft_minus_v3d(cyl.centre, o)));
	if (!((cyl.d1 >= 0 && cyl.d1 <= cyl.height && x2[0] > EPSILON)
			|| (cyl.d2 >= 0 && cyl.d2 <= cyl.height && x2[0] > EPSILON)))
		return (INFINITY);
	return (x2[0]);
}

double	cylinder_solver_test(t_v3d from, t_v3d dir, t_cylinder cyl)
{
	double	cylinder_inter;
	double	caps_inter;

	cylinder_inter = body_intersect(from, dir, cyl);
//	if (cyl->texture == 4)
//		caps_inter = INFINITY;
//	else
	caps_inter = top_intersect_test(from, dir, cyl);
	if (cylinder_inter < INFINITY || caps_inter < INFINITY)
	{
		if (cylinder_inter < caps_inter)
			return (cylinder_inter);
		return (caps_inter);
	}
	return (INFINITY);
}

double	get_solver_test(t_v3d from, t_v3d to, int type, t_figures fig)
{
	if (type == CYLINDER)
		return (cylinder_solver_test(from, to, fig.cyl));
	else
		return (INFINITY);
}

t_v3d	get_normal_test(t_inter *inter, t_v3d dir, t_v3d hit)
{
	if (inter->obj->type == SPHERE)
		return (sphere_normal(dir, hit, inter));
	if (inter->obj->type == CYLINDER)
		return (cylinder_normal_test(dir, hit, inter));
	else
		return (common_normal(dir, hit, inter));
}