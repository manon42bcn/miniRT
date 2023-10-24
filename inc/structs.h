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
typedef struct s_mrt	t_mrt;
typedef void			(*t_hook)(t_mrt *, int);
# define TO_RENDER 0
# define RENDERED 1
# define RIGHT_CLICK 1
# define LEFT_CLICK 2
# define RAD_ANGLE 0.0174533

typedef double	(*t_solver)(t_v3d, t_v3d, t_obj *);
enum e_fig
{
	CLOSE_OBJ=-1,
	SPHERE=0,
	PLANE=1,
	CYLINDER=2,
	RECTANGLE=3,
	TRIANGLE=4,
	BOX=5,
	CONE=6,
	ELLIPS=7
};

typedef	struct s_img
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
	int		antialiasing_on;
}				t_img;

typedef struct s_cmr
{
	t_v3d			position;
	t_v3d			dir;
	int				inp_fov;
	double			fov;
	double			orbit;
	double			ratio;
	double			angle_new[3];
	double			angle;
	t_obj			*close_obj;
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
	double			angle;
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
	double			bright;
	int				amb_rgb;
	double			ratio;
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
	double			angle;
	int				specular;
	double			reflex;
	double			refract;
	int				texture;
	t_v3d			position;
	t_v3d			normal;
	double			wavelength;
	t_bool			bump;
	t_img			xpm;
	t_bool			selected;
	union u_figures	elm;
}					t_obj;

typedef struct s_hooks
{
	int				keys;
	t_hook			fnc;
	struct t_hooks	*next;
}				t_hooks;

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
	int			behaviour;
	int			key_press;
	t_hook		hooks[256];
	char		*aux;
	char		**tab;
	int			fd;
	t_bool		bonus;
	int			mode;
	int			(*clean_window)(void *, void *);
	int			(*clean_image)(void *, void *);
	t_solver	(*get_solver)(int);
}					t_mrt;

typedef	struct s_thr
{
	t_mrt	*mrt;
	t_pixel	start_y;
	t_pixel	end_y;
}				t_thr;

#endif

#ifndef RAYER
# define RAYER
static int rayer=0;
#endif