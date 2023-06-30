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


void mlx_starter(t_mrt *mrt)
{
	t_cmr *node;

	node = mrt->cmr;
	while (node)
	{
		node->img_ptr = mlx_new_image(mrt->mlx, mrt->scn.w_x, mrt->scn.w_y);
		node->addr = (int *)mlx_get_data_addr(node->img_ptr,
			&node->bpp, &node->size, &node->endian);
		node = node->next;
	}
}

void		my_loop(t_mrt *mrt)
{
	//Limpiar y mejorar loop, incluir las funciones para cambiar
	// de camaras usando una tecla
	if (mrt->to_img == FALSE)
	{
		mrt->mlx_win = mlx_new_window(mrt->mlx, mrt->scn.w_x, mrt->scn.w_y,"miniRT");
		mlx_put_image_to_window(mrt->mlx, mrt->mlx_win, mrt->cmr->img_ptr, 0, 0);
		mrt->to_img = TRUE;
	}
	mlx_loop(mrt->mlx);
}

int main(int argc, char const *argv[])
{
	t_mrt	mrt;

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
	ft_memset(&mrt, 0, sizeof(t_mrt));
	mrt.mlx = mlx_init();
	my_mlx_getScreenSize(&(mrt.scn.w_x), &(mrt.scn.w_y));
	printf("%d - %d \n", mrt.scn.w_x, mrt.scn.w_y);
	printf("BONUS %d\n", BONUS);
	readfile_parser(argv[1], &mrt);
	mlx_starter(&mrt);
	render_main(&mrt);
	my_loop(&mrt);
	// Crear funcion para limpiar todo al salir...
	return (SUCCESS);
}
