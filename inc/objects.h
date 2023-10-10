/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:28:04 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/21 22:32:42 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# define BONUS 1
#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct s_sphere
{
	t_v3d	centre;
	double	radius;
	int		inside;
}				t_sphere;

typedef struct s_plane
{
	t_v3d	centre;
	t_v3d	orient;
}				t_plane;

typedef struct s_square
{
	t_v3d	centre;
	t_v3d	orient;
	double	side;

}				t_square;

typedef struct	s_rectangle
{
	t_v3d	centre;
	t_v3d	orient;
	double	width;
	double	height;
}				t_rectangle;

typedef struct s_cylinder
{
	t_v3d	centre;
	t_v3d	dir;
	double	radius;
	double	height;
	double	d1;
	double	d2;
}				t_cylinder;

typedef struct s_triangle
{
	t_v3d	v1;
	t_v3d	v2;
	t_v3d	v3;
}				t_triangle;

typedef struct s_cone
{
	t_v3d	centre;
	t_v3d	dir;
	double	radius;
	double	height;
	double	alpha;
}				t_cone;

typedef struct s_box
{
	t_v3d		centre;
	t_v3d		dir;
	double		width;
	double		height;
	double		depth;
	t_rectangle	faces[6];
	t_v3d		min;
	t_v3d		max;
}				t_box;

typedef struct s_hyper
{
	t_v3d	centre;
	t_v3d	dir;
	double	a;
	double	b;
	double	c;
	double	height;
}				t_hyper;


typedef struct s_parab
{
	t_v3d	centre;
	t_v3d	dir;
	double	focal_dist;
	double	height;
	double	min_height;
}				t_parab;

typedef struct	s_ellip
{
	t_v3d	centre;
	double	rx;
	double	ry;
	double	rz;
}				t_ellip;

typedef union u_figures
{
	t_sphere	sph;
	t_plane		pl;
	t_square	sq;
	t_cylinder	cyl;
	t_triangle	trg;
	t_cone		con;
	t_box		box;
	t_hyper		hy;
	t_parab		prb;
	t_ellip		elp;
	t_rectangle	rc;
}				t_figures;

#endif