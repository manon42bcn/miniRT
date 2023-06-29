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

#include "parse_enum.h"

typedef struct s_sph
{
	t_v3d	centre;
	double	radius;
	t_bool	inside;
}	t_sph;

typedef struct s_pln
{
	t_v3d	centre;
	t_v3d	orient;
} t_pln;

typedef struct s_cyl
{
	t_v3d	centre;
	t_v3d	dir;
	double	radius;
	double	height;
	double	d1;
	double	d2;
} t_cyl;

typedef struct	s_sqr
{
	t_v3d	centre;
	t_v3d	orient;
	double	side;

}				t_sqr;

typedef struct	s_trg
{
	t_v3d	v1;
	t_v3d	v2;
	t_v3d	v3;
	t_v3d	orient;
}				t_trg;

typedef union u_elem_np
{
	t_sph	sph;
	t_pln	pl;
	t_cyl	cyl;
	t_sqr	sq;
	t_trg	trg;
} t_elem_np;

#endif