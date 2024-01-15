/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 22:28:04 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/14 22:36:03 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# define BONUS 1
#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct s_fig
{
	t_v3d	centre;
	t_v3d	orient;
	t_dec	width;
	t_dec	height;
}				t_fig;

typedef struct s_sphere
{
	t_v3d	centre;
	t_v3d	dir;
	t_dec	radius;
	t_bool	inside;
	t_bool	texture;
}				t_sphere;

typedef struct s_plane
{
	t_v3d	centre;
	t_v3d	orient;
}				t_plane;

typedef struct s_rectangle
{
	t_v3d	centre;
	t_v3d	orient;
	t_dec	width;
	t_dec	height;
}				t_rectangle;

typedef struct s_cylinder
{
	t_v3d	centre;
	t_v3d	dir;
	t_dec	radius;
	t_dec	height;
	t_dec	d1;
	t_dec	d2;
	t_bool	texture;
}				t_cylinder;

typedef struct s_triangle
{
	t_v3d	dir;
	t_v3d	v1;
	t_v3d	v2;
	t_v3d	v3;
}				t_triangle;

typedef struct s_cone
{
	t_v3d	centre;
	t_v3d	dir;
	t_dec	radius;
	t_dec	height;
	t_dec	alpha;
}				t_cone;

typedef struct s_box
{
	t_v3d		centre;
	t_v3d		dir;
	t_dec		width;
	t_dec		height;
	t_dec		depth;
	t_rectangle	faces[6];
	t_bool		hit;
	t_v3d		min;
	t_v3d		max;
}				t_box;

typedef union u_figures
{
	t_sphere	sph;
	t_plane		pl;
	t_cylinder	cyl;
	t_triangle	trg;
	t_cone		con;
	t_box		box;
	t_rectangle	rc;
	t_fig		fig;
}				t_figures;

#endif