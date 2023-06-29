/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:05:30 by mgarcia-          #+#    #+#             */
/*   Updated: 2023/06/26 00:22:24 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	msg_instructions(void)
{
	ft_putendl_fd("\x1b[35m------------------------------------------", STDIN_FILENO);
	ft_putendl_fd("\e[1m\e[34mHELP - OPTIONS\x1b[0m", STDIN_FILENO);
	ft_putstr_fd("\e[44m[fractal]\e[0m\e[49m: mandelbrot, julia, ", STDIN_FILENO);
	ft_putendl_fd(" burningship, drop, bird, worm, spider, hiper.", STDIN_FILENO);
	ft_putendl_fd("\e[44m[options]\e[0m\e[49m: color, mono, bw, full.", STDIN_FILENO);
	ft_putendl_fd("\e[44m[params] (julia set only)\e[0m\e[49m: ", STDIN_FILENO);
	ft_putendl_fd("write two constant values for julia set.	", STDIN_FILENO);
	ft_putendl_fd("format: rC iC (default: -0.8350 -0.2321)", STDIN_FILENO);
	ft_putendl_fd("\x1b[35m------------------------------------------", STDIN_FILENO);
	ft_putendl_fd("\e[34mUSE:\x1b[0m", STDIN_FILENO);
	ft_putstr_fd("Zoom in: mouse scroll up | ", STDIN_FILENO);
	ft_putendl_fd(" Zoom out: mouse scroll down. | Q: reset zoom.", STDIN_FILENO);
	ft_putendl_fd("Up - down - left - right: move current view.", STDIN_FILENO);
	ft_putendl_fd("Mouse second button: change Julia set values.", STDIN_FILENO);
	ft_putstr_fd("(+) and (-): increases and reduces max iteration.", STDIN_FILENO);
	ft_putstr_fd("I and ): increases and reduces escape point.", STDIN_FILENO);
	ft_putstr_fd(" More iterations means more details and lag.", STDIN_FILENO);
	ft_putendl_fd("C: swich to color mode.", STDIN_FILENO);
	ft_putendl_fd("M: swich to mono mode.", STDIN_FILENO);
	ft_putendl_fd("B: swich to black and white.", STDIN_FILENO);
	ft_putendl_fd("F: swich to full mode (laggy, but interesting).", STDIN_FILENO);
	ft_putendl_fd("SPACE BAR: change color scheme.", STDIN_FILENO);
	ft_putendl_fd("ESC: exit fract-ol.", STDIN_FILENO);
}

void	msg_error_exit(char *message)
{
	ft_putstr_fd("miniRT ERROR ", STDERR_FILENO);
	if (message)
		ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(ERROR);
}

