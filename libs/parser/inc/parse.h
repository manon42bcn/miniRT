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

# ifndef V3D_H
#  include "../../v3d/inc/v3d.h"
# endif

# ifndef RGB_H
#  include "../../rgb/inc/rgb.h"
# endif

# ifndef LIBFT_H
#  include "../../lib/inc/libft.h"
# endif

# include <fcntl.h>
# include "parse_enum.h"
# include "objects.h"
# include "structs.h"
# define SEP " \t\n"
# define IDX_ERR	-1
# define IDX_COMMENT -2
# define ERROR 1
# define SUCCESS 0

// Cleaners
t_bool      parse_clean_all(t_mrt *mrt, int status);
// Parsing objects
void		inp_sphere(t_mrt *mrt);
void		inp_plane(t_mrt *mrt);
void		inp_cylinder(t_mrt *mrt);
void		inp_square(t_mrt *mrt);
void		inp_triangle(t_mrt *mrt);
void		inp_cube(t_mrt *mrt);
void		inp_pyramid(t_mrt *mrt);
void		inp_resolution(t_mrt *mrt);
void		inp_ambient(t_mrt *mrt);
void		inp_camera(t_mrt *mrt);
void		inp_light(t_mrt *mrt);
// Parser readfile
int			readfile_parser(char const *filename, t_mrt *rt);
// Parser common
t_rgb		get_color(char *line);
t_v3d		get_v3d(char *line, int mode);
void		get_common(t_mrt *mrt, int last, char *elem);
void		check_range(double value, double min, double max, char *msg);
void		msg_error_parsing(char *message);
// Parser builders
t_obj		*object_builder(int id, t_obj *next);
t_light		*light_builder(t_light *next);
t_cmr		*camera_builder(void);
// Errors
void		parse_error(char *message);
#endif