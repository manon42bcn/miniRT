/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 09:54:21 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/25 23:26:32 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "../../../inc/defines.h"
# include "../../../libs/v3d/inc/v3d.h"
# include "../../../libs/rgb/inc/rgb.h"
# include "../../../libs/lib/inc/libft.h"
# include <fcntl.h>
# include <math.h>
# include "parse_enum.h"
# include "../../../inc/objects.h"
# include "../../../inc/structs.h"

typedef void	(*t_build)(t_mrt *);

// Cleaners
int			clear_all(t_mrt *mrt, int status, int (*win)(void *, void *),
				int (*img)(void *, void *));
// Parsing objects
void		inp_sphere(t_mrt *mrt);
void		inp_plane(t_mrt *mrt);
void		inp_cylinder(t_mrt *mrt);
void		inp_resolution(t_mrt *mrt);
void		inp_ambient(t_mrt *mrt);
void		inp_camera(t_mrt *mrt);
void		inp_light(t_mrt *mrt);
void		inp_square(t_mrt *mrt);
void		inp_triangle(t_mrt *mrt);
void		inp_pyramid(t_mrt *mrt);
void		inp_box(t_mrt *mrt);
void		inp_cone(t_mrt *mrt);
void		inp_hyper(t_mrt *mrt);
void		inp_paraboloid(t_mrt *mrt);
void		inp_ellipsoid(t_mrt *mrt);
void		inp_rectangle(t_mrt *mrt);
// Parser readfile
t_mrt		*readfile_parser(char const *filename);
// Parser common
t_rgb		get_color(char *line, t_mrt *mrt);
t_v3d		get_v3d(t_mrt *mrt, char *line, int mode);
void		get_common(t_mrt *mrt, int last, char *elem);
t_bool		check_range(double value, double min, double max);
void		msg_error_parsing(char *message, t_mrt *mrt);
// Parser builders
t_obj		*object_builder(int id, t_obj *next);
t_light		*light_builder(t_light *next);
t_cmr		*camera_builder(void);
// Errors
int			parser_dict(char *id);
t_build		get_builder(int index, t_mrt *mrt);
void		parse_error(char *message);

# ifdef BONUS

#  define LAST_COMMON 5
#  define ELM_SPH 8
#  define ELM_PL 8
#  define ELM_CYL 10
#  define ELM_RES 3
#  define ELM_AMB 3
#  define ELM_CAM 4
#  define ELM_LGH 4
#  define ELM_SQ 9
#  define ELM_TR 9
#  define ELM_CU 8
#  define ELM_PY 8
#  define ELM_CO 10
#  define ELM_BOX 11
#  define ELM_HYP 12
#  define ELM_PARAB 11
#  define ELM_ELLIP 10
#  define ELM_RECT 10

# else
#  define LAST_COMMON 1

#  define ELM_SPH 4
#  define ELM_PL	4
#  define ELM_CYL 6
#  define ELM_RES 3
#  define ELM_AMB 3
#  define ELM_CAM 4
#  define ELM_LGH 4

# endif

#endif