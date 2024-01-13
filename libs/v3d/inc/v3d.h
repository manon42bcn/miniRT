/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:00:05 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/10 22:45:17 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# define BONUS 1
#ifndef V3D_H
# define V3D_H

# include <math.h>

# ifndef E_COOR
#  define E_COOR

typedef enum e_coor
{
	X_C = 0,
	Y_C = 1,
	Z_C = 2
}	t_coor;

#  define V3D_COOR	0
#  define V3D_NORM   1

# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef NO_MATCH
#  define NO_MATCH -1
# endif

typedef int			t_bool;
typedef long double	t_dec;

typedef struct s_v3d
{
	t_dec	x;
	t_dec	y;
	t_dec	z;
}				t_v3d;

typedef t_v3d	t_point;

//v3d_algebra.c
t_dec	ft_length_v3d(t_v3d vec);
t_dec	ft_mag_v3d(t_v3d vector);
t_dec	ft_cos_v3d(t_v3d a, t_v3d b);
t_dec	ft_sin_v3d(t_v3d a, t_v3d b);
t_v3d	ft_cross_v3d(t_v3d a, t_v3d b);
//v3d_arithmetics.c
t_v3d	ft_plus_v3d(t_v3d a, t_v3d b);
t_v3d	ft_minus_v3d(t_v3d a, t_v3d b);
t_dec	ft_dot_v3d(t_v3d a, t_v3d b);
t_v3d	ft_scalar_v3d(t_dec	scalar, t_v3d vec);
t_v3d	ft_div_v3d(t_v3d vec, t_dec real);
//v3d_extra.c
t_v3d	ft_subs_real(t_v3d vec, t_dec real);
t_v3d	ft_plus_real(t_v3d vec, t_dec real);
t_dec	ft_distance_v3d(t_v3d a, t_v3d b);
t_bool	ft_is_normal_v3d(t_v3d *v);
//v3d_utils.c
void	ft_normalize_v3d(t_v3d *vec);
t_v3d	ft_normal_v3d(t_v3d vec);
t_v3d	ft_copy_v3d(t_v3d *vec);
t_v3d	ft_new_v3d(t_dec x, t_dec y, t_dec z);
t_v3d	ft_v3d_identity(int axis);
//v3d_tools.c
t_v3d	ft_rot_v3d(t_v3d vec, int axis, t_dec angle);
t_v3d	ft_perp_v3d(t_v3d vec);
t_bool	ft_is_idt_v3d(t_v3d vec);
t_v3d	ft_next_id_v3d(t_v3d vec);

#endif
