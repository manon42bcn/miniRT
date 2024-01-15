/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:26:37 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/15 01:07:37 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# define BONUS 1
#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_obj	t_obj;
typedef int				t_pixel;
typedef struct s_mrt	t_mrt;
# define TO_RENDER 0
# define RENDERED 1
# define RIGHT_CLICK 1
# define LEFT_CLICK 2

typedef struct s_ray
{
	t_v3d	from;
	t_v3d	to;
}				t_ray;

enum e_fig
{
	CLOSE_OBJ=-1,
	SPHERE=0,
	PLANE=1,
	CYLINDER=2,
	RECTANGLE=3,
	TRIANGLE=4,
	BOX=5,
	CONE=6
};

typedef struct s_img
{
	void	*img;
	char	*addr;
	char	*path;
	int		width;
	int		height;
	int		bbp;
	int		ll;
	int		endian;
	int		addr_incr;
}				t_img;

typedef struct s_cmr
{
	t_v3d			position;
	t_v3d			dir;
	int				inp_fov;
	t_dec			fov;
	t_dec			orbit;
	t_dec			ratio;
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
	t_bool			res_init;
	int				w_x;
	int				w_y;
	t_light			*light;
	t_light			*sel_light;
	t_dec			bright;
	t_rgb			amb_rgb;
	t_dec			ratio;
	t_rgb			bgr;
}					t_scene;

typedef struct s_obj
{
	int				type;
	struct s_obj	*next;
	int				id;
	t_rgb			color;
	t_rgb			orig_color;
	t_rgb			sel_color;
	int				specular;
	t_dec			reflex;
	t_dec			refract;
	int				texture;
	t_dec			wavelength;
	t_bool			bump;
	t_img			xpm;
	t_bool			selected;
	union u_figures	elm;
}					t_obj;

typedef struct s_inter
{
	t_ray			ray;
	t_obj			*obj;
	t_dec			dist;
	t_rgb			color;
	t_rgb			ref_color;
	t_bool			specular;
	t_dec			reflex;
	t_dec			refract;
	t_bool			inside;
	t_v3d			normal;
	t_v3d			hit;
	int				face;
}					t_inter;

typedef struct s_mrt
{
	t_bool		to_img;
	t_bool		window;
	void		*mlx;
	void		*mlx_win;
	t_scene		scn;
	t_obj		*obj;
	t_obj		*sel_obj;
	t_cmr		*cmr;
	t_cmr		*main_cam;
	t_pixel		x;
	t_pixel		y;
	char		*aux;
	char		**tab;
	int			fd;
	t_bool		bonus;
	int			mode;
	int			(*clean_window)(void *, void *);
	int			(*clean_image)(void *, void *);
	t_v3d		(*ray_pixel)(int, int, t_mrt *);
	t_dec		(*get_solver)(t_v3d, t_v3d, t_obj *, t_inter *);
}					t_mrt;

typedef	struct s_info
{
	t_mrt	*mrt;
	t_pixel	x;
	t_pixel	y;
	t_pixel	end_y;
	t_pixel	max_y;
}				t_info;



#endif
