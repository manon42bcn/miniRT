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

# include "../mlx/mlx.h"
# include "definitions.h"
# include "ggl_mlx_define.h"
# include "libft.h"
# include "rgb.h"
# include "v3d.h"
# include "parse.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

typedef struct		s_ray
{
	t_v3d	from;
	t_v3d	to;
}					t_ray;

typedef struct		s_pix
{
	int		limit;
	int		w_x;
	int		w_y;
	int		x;
	int		y;
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
//hooks
int				mouse_handler(int mouse_code, int x, int y, t_mrt *mrt);
void			cylinder_x_translation(t_mrt *mrt, int x, int y, int mouse_code);
void			cylinder_y_translation(t_mrt *mrt, int x, int y, int mouse_code);
void			cylinder_z_translation(t_mrt *mrt, int x, int y, int mouse_code);
void			cylinder_diam(t_mrt *mrt, int x, int y, int mouse_code);
void			cylinder_height(t_mrt *mrt, int x, int y, int mouse_code);
void			sphere_x_translation(t_mrt *mrt, int x, int y, int mouse_code);
void			sphere_y_translation(t_mrt *mrt, int x, int y, int mouse_code);
void			sphere_z_translation(t_mrt *mrt, int x, int y, int mouse_code);
void			sphere_diam(t_mrt *mrt, int x, int y, int mouse_code);
//intersections
t_solver		get_solver(int index);
double			cube_solver(t_v3d origin, t_v3d dir, t_obj *obj);
double			cylinder_solver(t_v3d from, t_v3d dir, t_obj *cyl);
void			try_all_intersections(t_ray ray, t_obj *obj,
					t_obj *closest_figure, double *closest_intersection);
t_v3d			reflect_ray(t_v3d ray, t_v3d normal);
double			plane_solver(t_v3d origin, t_v3d dir, t_obj *obj);
double			plane_hit(t_v3d origin, t_v3d dir, t_v3d plane_centre, t_v3d plane_dir);
double			pyramid_solver(t_v3d origin, t_v3d dir, t_obj *obj);
double			sphere_solver(t_v3d origin, t_v3d dir, t_obj *sph);
double			square_solver(t_v3d origin, t_v3d dir, t_obj *sqr);
double			triangle_solver(t_v3d origin, t_v3d dir, t_obj *trg);
//light
void			hit_direction(t_v3d hitted, t_v3d dir, t_v3d *normal, t_obj *obj);
void			ligth_hit(t_ray ray, t_inter *inter, t_scene scn, t_obj *obj);
double			specular_transform(t_ray ray, t_inter *inter, t_scene scn, t_obj *obj);
//Rays
t_rgb			calc_ray(int n, t_pix pix, t_mrt *mrt);
t_rgb			tracer(t_v3d origin, t_v3d dir, t_mrt *mrt, int depth);
//Render
void			render_main(t_mrt *mrt);
void			mlx_starter(t_mrt *mrt);
int				to_win(t_mrt *mrt);
int				window_handler(t_mrt *mrt);
int				keys_handler(int key, t_mrt *mrt);
//Sampler
int				*sample_pixel(int *edges, int sides[2], t_pix pix, t_mrt *mrt);
t_rgb			supersample(int *color, t_pix pix, t_mrt *mrt);
// utl
void			msg_instructions(void);
void			msg_error_exit(char *message);
//void 			ft_safe_free(void *ptr);
//int             clear_all(t_mrt *mrt, int status);

# ifdef BONUS

//Texture
void			texturize(int texture, t_inter *inter, t_obj *obj);

# endif
#endif
