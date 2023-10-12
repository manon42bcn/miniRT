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
# define BONUS 1
#ifndef SOLVERS_H
# define SOLVERS_H

# include "../../../libs/lib/inc/libft.h"
# include "../../../libs/v3d/inc/v3d.h"
# include "../../../libs/rgb/inc/rgb.h"
# include "../../../inc/defines.h"
# include "../../../inc/objects.h"
# include "../../../inc/structs.h"

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

typedef t_v3d	(*t_normal)(t_v3d, t_v3d, t_obj *);

t_bool			quadratic(double *vars, double *dist);
typedef double	(*t_solver)(t_v3d, t_v3d, t_obj *);
t_solver		get_solver(int index);
double			plane_solver(t_v3d origin, t_v3d dir, t_obj *obj);
double			plane_hit(t_v3d origin, t_v3d dir, t_v3d plane_centre,
					t_v3d plane_dir);
double			cylinder_solver(t_v3d from, t_v3d dir, t_obj *cyl);
double			top_intersect(t_v3d o, t_v3d d, t_obj *lst);
double			sphere_solver(t_v3d origin, t_v3d dir, t_obj *sph);

# ifdef BONUS

double			triangle_solver(t_v3d origin, t_v3d dir, t_obj *trg);
double			box_solver(t_v3d origin, t_v3d dir, t_obj *obj);
double			cone_solver(t_v3d origin, t_v3d dir, t_obj *obj);
double			ellipsoid_solver(t_v3d origin, t_v3d dir, t_obj *obj);
double			rectangle_solver(t_v3d origin, t_v3d dir, t_obj *obj);

//Normals
t_v3d			get_normal(t_obj *obj, t_v3d dir, t_v3d hit);
t_v3d			box_normal(t_v3d dir, t_v3d hit, t_obj *obj);
t_v3d			cone_normal(t_v3d dir, t_v3d hit, t_obj *obj);
t_v3d			ellipsoid_normal(t_v3d dir, t_v3d hit, t_obj *obj);
t_v3d			sphere_normal(t_v3d dir, t_v3d hit, t_obj *obj);

# endif

#endif
