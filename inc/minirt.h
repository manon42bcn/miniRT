/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 08:42:41 by mgarcia-          #+#    #+#             */
/*   Updated: 2023/06/26 00:25:09 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <pthread.h>

# include "../mlx/mlx.h"
# include "defines.h"
# include "../libs/lib/inc/libft.h"
# include "../libs/rgb/inc/rgb.h"
# include "../libs/v3d/inc/v3d.h"
# include "parse.h"
# include "solvers.h"
# include "hooks.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# define THREADS	10

typedef struct		s_pix
{
	int		limit;
	int		w_x;
	int		w_y;
	int		x;
	int		y;
	int 	max_y;
}					t_pix;

typedef struct		s_inter
{
	t_rgb			color;
	t_rgb			ref_color;
	t_v3d			normal;
	t_v3d			hit;
	t_ray			ray;
}					t_inter;

typedef double	(*t_solver)(t_v3d, t_v3d, t_obj *);
void		printVector(t_v3d *vector);
t_v3d		ray_from_pixel(int x, int y, t_mrt *mrt);

//double		cube_solver(t_v3d origin, t_v3d dir, t_obj *obj);
//double		cylinder_solver(t_v3d from, t_v3d dir, t_obj *cyl);
void		try_all_intersections(t_ray ray, t_obj *obj,
				t_obj *closest_figure, double *closest_intersection);
t_v3d		reflect_ray(t_v3d ray, t_v3d normal);
//light
void		hit_direction(t_v3d hitted, t_v3d dir, t_v3d *normal, t_obj *obj);
void		light_hit(t_ray ray, t_inter *inter, t_scene scn, t_obj *obj);
double		specular_transform(t_ray ray, t_inter *inter, t_scene scn, t_obj *obj);
//Rays
t_rgb		calc_ray(int n, t_pix pix, t_mrt *mrt);
t_rgb		tracer(t_v3d origin, t_v3d dir, t_mrt *mrt, int depth);
//Render
t_rgb		*create_edges_new(int size);
void		render_main(t_mrt *mrt);
void		mlx_starter(t_mrt *mrt);
int			to_win(t_mrt *mrt);
//Sampler
int			*sample_pixel(int *edges, int sides[2], t_pix pix, t_info *dta);
t_rgb		supersample(int *color, t_pix pix, t_mrt *mrt);
// utl
void		msg_instructions(void);
void		msg_error_exit(char *message);

# ifdef BONUS
//Texture
void		texturize(int texture, t_inter *inter, t_obj *obj);
t_rgb		bump_texture(t_v3d hit, t_obj *obj);
# endif
#endif
