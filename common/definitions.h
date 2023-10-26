/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 23:17:00 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/25 23:24:37 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# define BONUS 1
#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# ifndef EPSILON
#  define EPSILON 0.00001
# endif

# ifndef SQRT2_2
#  define SQRT2_2 0.7071067811865476
# endif

# define ROTATE_X 0
# define ROTATE_Y 1
# define ROTATE_Z 2
# define TRUE	1
# define FALSE	0
# define MATCH	0

# define CHECKBOARD 1
# define WAVES 2
# define RAINBOW 3
# define REFLECTION_LIMIT 3
# define ERROR 1
# define SUCCESS 0

typedef int				t_bool;
typedef struct s_mrt	t_mrt;
typedef int				t_pixel;

#endif