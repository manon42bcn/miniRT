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

# include "definitions.h"
# include "../mlx/mlx.h"
# include "ggl_mlx_define.h"
# include "libft.h"
# include "rgb.h"
# include "v3d.h"
# include "figures.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>

# include "structs.h"
# include "parse.h"


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

typedef struct		s_sq
{
	t_v3d			half_size;
	t_v3d			floor;
	t_v3d			center_to_ip;
}					t_sq;

typedef struct		s_cube
{
	t_obj			sq;
	t_v3d			center;
	t_v3d			normal[6];
}					t_cube;

typedef struct		s_pyramid
{
	t_obj		sq;
	t_obj		trg;
	t_v3d		tr_center;
	t_v3d		normal[5];
	t_v3d		corner[4];
	double		closest;
	double		intersection;
}					t_pyr;

//intersections
double			cube_solver(t_v3d origin, t_v3d dir, t_obj *obj);
double			cylinder_solver(t_v3d from, t_v3d dir, t_obj *cyl);
void		    try_all_intersections(t_ray ray, t_obj *obj,
                                  t_obj *closest_figure, double *closest_intersection);
t_v3d		    reflect_ray(t_v3d ray, t_v3d normal);
double			plane_solver(t_v3d origin, t_v3d dir, t_obj *obj);
double			plane_hit(t_v3d origin, t_v3d dir, t_v3d plane_centre, t_v3d plane_dir);
double			pyramid_solver(t_v3d origin, t_v3d dir, t_obj *obj);
double			sphere_solver(t_v3d origin, t_v3d dir, t_obj *sph);
double			square_solver(t_v3d origin, t_v3d dir, t_obj *sqr);
double			triangle_solver(t_v3d origin, t_v3d dir, t_obj *trg);
//light
void	        hit_direction(t_v3d hitted, t_v3d dir, t_v3d *normal, t_obj *obj);
void	        ligth_hit(t_ray ray, t_inter *inter, t_scene scn, t_obj *lst);
double	        specular_transform(t_ray ray, t_inter *inter, t_scene scn, t_obj *lst);
//Rays
t_rgb			calc_ray(int n, t_pix pix, t_mrt *mrt);
t_rgb			tracer(t_v3d origin, t_v3d dir, t_mrt *mrt, int depth);
//Render
void	        render_main(t_mrt *mrt);
//Sampler
int				*sample_pixel(int *edges, int sides[2], t_pix pix, t_mrt *mrt);
t_rgb	        supersample(int *color, t_pix pix, t_mrt *mrt);
//Texture
void		    texturize(int texture, t_inter *inter, t_obj *obj);
// utl
void			msg_instructions(void);
void			msg_error_exit(char *message);
void			*ft_sec_malloc(size_t size);
void			*ft_sec_calloc(size_t size);
void 			ft_safe_free(void *ptr);
void			ft_perror(char *msg);
#endif
