/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 23:56:02 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/10 22:14:56 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

typedef enum e_local_pix
{
	E_U=0,
	E_V=1
}			t_local_pix;

# define EPSILON 0.00001
# define TO_RENDER 0
# define RENDERED 1
# define TRUE	1
# define FALSE	0
# define MATCH	0
# define NO_INDEX -1

# define CHECKBOARD 1
# define WAVES 2
# define RAINBOW 3
# define REFLECTION_LIMIT 3
# define HALF_SPHERE 4
# define NO_CAPS 4
# define ERROR 1
# define SUCCESS 0

typedef int				t_bool;
typedef struct s_mrt	t_mrt;
typedef int				t_pixel;

#endif
