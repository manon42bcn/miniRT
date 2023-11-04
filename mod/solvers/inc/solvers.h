/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solvers.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 17:04:06 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/30 17:04:11 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLVERS_H
# define SOLVERS_H

# include "../../../libs/lib/inc/libft.h"
# include "../../../libs/v3d/inc/v3d.h"
# include "../../../libs/rgb/inc/rgb.h"
# include "defines.h"
# include "objects.h"
# include "structs.h"

enum e_array_intersections
{
	IP1,
	IP2,
	C_DIST
};

enum e_coef
{
	E_A = 0,
	E_B = 1,
	E_C = 2
};

enum e_dist
{
	T_0=0,
	T_1=1
};

typedef t_v3d	(*t_normal)(t_v3d, t_v3d, t_inter *);

t_bool			quadratic(double *vars, double *dist);
double			get_solver(t_v3d origin, t_v3d dir, t_obj *obj, t_inter *inter);
double			plane_solver(t_v3d origin, t_v3d dir, t_plane pl);
double			plane_hit(t_v3d origin, t_v3d dir, t_v3d plane_centre,
					t_v3d plane_dir);
double			cylinder_solver(t_v3d from, t_v3d dir, t_cylinder cyl,
					t_inter *inter);
double			top_intersect(t_v3d o, t_v3d d, t_cylinder lst);
double			sphere_solver(t_v3d origin, t_v3d dir, t_sphere sph);
t_v3d			get_normal(t_inter *inter, t_v3d dir, t_v3d hit);
t_v3d			sphere_normal(t_v3d dir, t_v3d hit, t_inter *inter);
t_v3d			cylinder_normal(t_v3d dir, t_v3d hit, t_inter *inter);
double			rectangle_solver(t_v3d origin, t_v3d dir, t_rectangle rc);

# ifdef BONUS

double			triangle_solver(t_v3d origin, t_v3d dir, t_triangle trg);
double			box_solver(t_v3d origin, t_v3d dir, t_box box, t_inter *inter);
double			cone_solver(t_v3d origin, t_v3d dir, t_cone con);
double			ellipsoid_solver(t_v3d origin, t_v3d dir, t_ellip elp);

t_v3d			box_normal(t_v3d dir, t_v3d hit, t_inter *obj);
t_v3d			cone_normal(t_v3d dir, t_v3d hit, t_inter *obj);
t_v3d			ellipsoid_normal(t_v3d dir, t_v3d hit, t_inter *obj);
t_v3d			common_normal(t_v3d dir, t_v3d hit, t_inter *inter);

# endif

#endif
