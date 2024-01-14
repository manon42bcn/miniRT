/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 08:42:41 by mporras-          #+#    #+#             */
/*   Updated: 2023/12/01 21:21:16 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifdef BONUS
#  include <pthread.h>
#  define THREADS	20
# endif

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

# define RFX		0
# define RFRC		1

typedef struct		s_pix
{
	int		limit;
	int		w_x;
	int		w_y;
	int		x;
	int		y;
	int		max_y;
}					t_pix;

t_v3d		ray_from_pixel(int x, int y, t_mrt *mrt);
void		get_hits(t_inter *inter, t_obj *obj, t_mrt *mrt);
//light
t_rgb		light_hit(t_ray ray, t_inter inter, t_mrt *mrt);
//Rays
t_rgb		calc_ray(int n, t_pix pix, t_mrt *mrt);
t_rgb		tracer(t_v3d origin, t_v3d dir, t_mrt *mrt, int depth);
//Render
t_rgb		*create_edges_new(int size);
void		render_main(t_mrt *mrt);
int			to_win(t_mrt *mrt);
//Sampler
int			*sample_pixel(int *edges, int sides[2], t_pix pix, t_info *dta);
t_rgb		supersample(int *color, t_pix pix, t_mrt *mrt);
// utl
void		msg_instructions(void);
void		msg_error_exit(char *message);

# ifdef BONUS

//Texture
void		texturize(t_inter *inter);
t_rgb		bump_texture(t_inter inter, t_v3d hit, t_obj obj, t_mrt *mrt);
t_v3d		reflect_ray(t_v3d ray, t_v3d normal);
double		specular_transform(t_ray ray, t_inter inter, t_light *scn_light);
t_v3d		refraction(t_v3d from, t_v3d dir, t_obj *obj);

# endif
#endif
