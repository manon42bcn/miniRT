/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 23:56:02 by mporras-          #+#    #+#             */
/*   Updated: 2023/09/04 23:56:04 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

typedef enum e_local_pix
{
	E_U=0,
	E_V=1
}			t_local_pix;

# define NORMAL			0
# define TO_SELECT		1
# define SELECTION		2
# define TO_ROTATE		3
# define TO_TRANSLATE	4

// KEY DEFINITIONS
# define NO_HOOK		0
# define K_D			2
# define K_F			3
# define K_H			4
# define K_G			5
# define K_Z			6
# define K_X			7
# define K_C			8
# define K_E			14
# define K_R			15
# define K_Y			16
# define K_T			17
# define K_Q			12
# define K_L			37
# define K_J			38
# define K_U			32
# define K_O			31
# define K_N			45
# define K_M			46
# define K_SPACE		49
# define K_ENTER		36
# define K_ESC			53
# define K_S			1
# define K_UP			126
# define K_DOWN			125
# define K_LEFT			123
# define K_RIGHT		124
# define K_MINUS		78
# define K_PLUS			69

# define EPSILON 0.00001
# define SQRT2_2 0.7071067811865476
# define RAD_ANGLE 0.0174533
# define TO_RENDER 0
# define RENDERED 1
# define RIGHT_CLICK 1
# define LEFT_CLICK 2
# define SEP " \t\n"
# define IDX_ERR	-1
# define IDX_COMMENT -2
# define ERROR 1
# define SUCCESS 0
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

#endif

