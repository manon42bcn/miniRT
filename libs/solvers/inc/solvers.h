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

# include "../../lib/inc/libft.h"
# include "../../v3d/inc/v3d.h"
# include "../../rgb/inc/rgb.h"
# include "../../../inc/objects.h"
# include "../../../inc/structs.h"

# ifndef EPSILON
#  define EPSILON 0.00001
# endif

# ifndef SQRT2_2
#  define SQRT2_2 0.7071067811865476
# endif

enum e_array_intersections
{
	IP1,
	IP2,
	C_DIST
};

typedef double	(*t_solver)(t_v3d, t_v3d, t_obj *);
t_solver		get_solver(int index);
double			plane_solver(t_v3d origin, t_v3d dir, t_obj *obj);
double			plane_hit(t_v3d origin, t_v3d dir, t_v3d plane_centre,
					t_v3d plane_dir);
double			cylinder_solver(t_v3d from, t_v3d dir, t_obj *cyl);
double			top_intersect(t_v3d o, t_v3d d, t_obj *lst);
double			sphere_solver(t_v3d origin, t_v3d dir, t_obj *sph);

# ifdef BONUS

double			square_solver(t_v3d origin, t_v3d dir, t_obj *sqr);
double			triangle_solver(t_v3d origin, t_v3d dir, t_obj *trg);
double			pyramid_solver(t_v3d origin, t_v3d dir, t_obj *obj);
double			cube_solver(t_v3d origin, t_v3d dir, t_obj *obj);

# endif

#endif
