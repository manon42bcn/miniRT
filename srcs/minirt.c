/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 08:39:55 by mgarcia-          #+#    #+#             */
/*   Updated: 2023/06/26 00:27:24 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	printVector(t_v3d *vector)
{
	printf("[%f x %f y %f z]\n", vector->x, vector->y, vector->z);
}

void	objPnt(t_obj *obj)
{
	while (obj)
	{
		printf("%p\n", obj);
		obj = obj->next;
	}
}

/**
 * @brief The main entry point for the miniRT application.
 *
 * Validates the command-line arguments and initializes the program.
 * Parses the scene from the input file, processes it, renders
 * the scene, and opens a MiniLibX window to display the rendered
 * image. It also sets up various event handlers for the window.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return Returns SUCCESS if the program executed without errors.
 */
int	main(int argc, char const *argv[])
{
	t_mrt	*mrt;

	if (argc < 2 || argc > 3)
		msg_error_exit("Args error. Type --help for instructions.");
	if (argc == 3)
		msg_error_exit("invalid argument\n");
	mrt = readfile_parser(argv[1]);
	after_parse_process(mrt);
	objPnt(mrt->obj);
	if (pthread_mutex_init(&mrt->gethits, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&mrt->getnormal, NULL) != 0)
		return (ERROR);
	if (pthread_mutex_init(&mrt->getlight, NULL) != 0)
		return (ERROR);
	render_main(mrt);
	mrt->mlx_win = mlx_new_window(mrt->mlx, mrt->scn.w_x,
			mrt->scn.w_y, "miniRT");
	mlx_key_hook(mrt->mlx_win, key_main, mrt);
	mlx_hook(mrt->mlx_win, 17, 0L, window_handler, mrt);
	mlx_hook(mrt->mlx_win, 4, 1L << 2, mouse_select, mrt);
	mlx_hook(mrt->mlx_win, 5, 1L << 3, mouse_select, mrt);
//	mlx_hook(mrt->mlx_win, 4, 1L << 2, mouse_handler, mrt);
//	mlx_hook(mrt->mlx_win, 5, 1L << 3, mouse_handler, mrt);
	mlx_loop_hook(mrt->mlx, to_win, mrt);
	mlx_loop(mrt->mlx);
	clear_all(mrt, SUCCESS, NULL, NULL);
	return (SUCCESS);
}
