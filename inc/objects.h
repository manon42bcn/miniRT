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
	t_v3d	orient;
}				t_triangle;

typedef union u_figures
{
	t_sphere	sph;
	t_plane		pl;
	t_square	sq;
	t_cylinder	cyl;
	t_triangle	trg;
}				t_figures;

#endif