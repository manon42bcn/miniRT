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

// minilibx esta generando leaks, ya que no estamos liberando bien la memoria
// de las imagenes y la ventana. No lo he visto en detalle, pero creo que es
// el unico punto de leaks so far...

int main(int argc, char const *argv[])
{
	t_mrt	*mrt;

	mrt = (t_mrt *) ft_sec_calloc(sizeof(t_mrt));
	// Hace poco cambiaron el subject, lo que me dejó un poco movido...
	// La cosa es que es relativamente fácil encontrar archivos 
	// para probar los viejos, no tanto los nuevos. Por esta razón 
	// el parseo esta para admitir archivos viejos, cuando tengamos varios
	// nuevos, es cuestion de cambiar dos tontadas
	if (argc < 2 || argc > 3)
		msg_error_exit("Args error. Type --help for instructions.");
	if (argc == 3)
		msg_error_exit("invalid argument\n");
	// Incluir la opción de --help para mostrar mensaje de ayuda.
	mrt->mlx = mlx_init();
	my_mlx_getScreenSize(&(mrt->scn.w_x), &(mrt->scn.w_y));
	readfile_parser(argv[1], mrt);
	mlx_starter(mrt);
	render_main(mrt);
	printf("%d TOIMG\n", mrt->to_img);
	mrt->mlx_win = mlx_new_window(mrt->mlx, mrt->scn.w_x, mrt->scn.w_y,"miniRT");
	mlx_key_hook(mrt->mlx_win, keys_handler, mrt);
	mlx_hook(mrt->mlx_win, 17, 0L, window_handler, mrt);
	mlx_loop_hook(mrt->mlx, to_win, mrt);
	mlx_loop(mrt->mlx);
	// Crear funcion para limpiar todo al salir...
	return (SUCCESS);
}
