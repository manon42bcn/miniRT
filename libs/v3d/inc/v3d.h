/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v3d.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:00:05 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/19 00:06:49 by mporras-         ###   ########.fr       */
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
	X_C,
	Y_C,
	Z_C,
	T_C
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

typedef int		t_bool;

typedef struct s_v3d
{
	double	x;
	double	y;
	double	z;
}				t_v3d;

typedef t_v3d	t_point;

//v3d_algebra.c
double	ft_length_v3d(t_v3d vec);
double	ft_mag_v3d(t_v3d vector);
double	ft_cos_v3d(t_v3d a, t_v3d b);
double	ft_sin_v3d(t_v3d a, t_v3d b);
t_v3d	ft_cross_v3d(t_v3d a, t_v3d b);
//v3d_arithmetics.c
t_v3d	ft_plus_v3d(t_v3d a, t_v3d b);
t_v3d	ft_minus_v3d(t_v3d a, t_v3d b);
double	ft_dot_v3d(t_v3d a, t_v3d b);
t_v3d	ft_scalar_v3d(double scalar, t_v3d vec);
t_v3d	ft_div_v3d(t_v3d vec, double real);
//v3d_extra.c
t_v3d	ft_subs_real(t_v3d vec, double real);
t_v3d	ft_plus_real(t_v3d vec, double real);
double	ft_distance_v3d(t_v3d a, t_v3d b);
t_bool	ft_is_normal_v3d(t_v3d *v);
//v3d_utils.c
void	ft_normalize_v3d(t_v3d *vec);
t_v3d	ft_normal_v3d(t_v3d vec);
t_v3d	ft_copy_v3d(t_v3d *vec);
t_v3d	ft_new_v3d(double x, double y, double z);
t_v3d	ft_v3d_identity(int axis);
//v3d_tools.c
t_v3d	ft_rotate_v3d(t_v3d vec, t_v3d axis);
t_v3d	ft_rotate_normal_v3d(t_v3d vec, t_v3d axis);
t_v3d	ft_perp_v3d(t_v3d vec);
t_v3d	ft_rot_v3d_x(t_v3d vec, double angle);
t_v3d	ft_rot_v3d_y(t_v3d vec, double angle);
t_v3d	ft_rot_v3d_z(t_v3d vec, double angle);

#endif
