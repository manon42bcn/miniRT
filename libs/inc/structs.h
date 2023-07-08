/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:26:37 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/25 23:52:50 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_obj	t_obj;
typedef int				t_pixel;

enum e_fig
{
	CLOSE_OBJ=-1,
	SPHERE=0,
	PLANE=1,
	CYLINDER=2,
	SQUARE=3,
	TRIANGLE=4,
	CUBE=5,
	PYRAMID=6
};

typedef struct s_cmr
{
	t_v3d			position;
	t_v3d			dir;
	int				inp_fov;
	double			fov;
	double			ratio;
	void			*img_ptr;
	int				*addr;
	int				bpp;
	int				size;
	int				endian;
	struct s_cmr	*next;
}					t_cmr;

typedef struct s_light
{
	t_v3d			origin;
	double			bright;
	t_rgb			color;
	struct s_light	*next;
}					t_light;

typedef struct s_scene
{
	t_bool			parsed;
	int				res_init;
	int				w_x;
	int				w_y;
	t_light			*light;
	double			bright;
	int				amb_rgb;
	double			ratio;
	t_rgb			bgr;
}					t_scene;

typedef struct s_obj
{
	int				type;
	int				id;
	union u_figures	elm;
	t_rgb			color;
	int				specular;
	double			reflex;
	double			refract;
	int				texture;
	t_v3d			normal;
	double			wavelength;
	struct s_obj	*next;
}					t_obj;

typedef struct s_mrt
{
	t_bool		to_img;
	void		*mlx;
	void		*mlx_win;
	t_scene		scn;
	t_obj		*obj;
	t_cmr		*cmr;
	t_cmr		*main_cam;
	t_pixel		x;
	t_pixel		y;
	char		*aux;
	char		**tab;
	t_bool		bonus;
}					t_mrt;

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

#endif