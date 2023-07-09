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

static inline void	parse_fix(t_mrt *mrt)
{
	t_cmr	*node;

	node = mrt->cmr;
	if (mrt->scn.parsed == FALSE)
		my_mlx_getScreenSize(&(mrt->scn.w_x), &(mrt->scn.w_y));
	printf("%d width - %d height\n", mrt->scn.w_x, mrt->scn.w_y);
	mrt->scn.ratio = (double)mrt->scn.w_x / (double)mrt->scn.w_y;
	while (node)
	{
		node->ratio = mrt->scn.ratio;
		node = node->next;
	}
	mrt->main_cam = mrt->cmr;
	mrt->window = FALSE;
}

void print_all_mrt(const t_mrt *mrt)
{
	printf("to_img: %d, %p\n", mrt->to_img, &(mrt->to_img));
	printf("mlx: %p, %p\n", mrt->mlx, &(mrt->mlx));
	printf("mlx_win: %p, %p\n", mrt->mlx_win, &(mrt->mlx_win));
	printf("scn: %p, %p\n", &(mrt->scn), &(mrt->scn));
	printf("obj: %p, %p\n", mrt->obj, &(mrt->obj));
	printf("cmr: %p, %p\n", mrt->cmr, &(mrt->cmr));
	printf("main_cam: %p, %p\n", mrt->main_cam, &(mrt->main_cam));
	printf("x: %d, %p\n", mrt->x, &(mrt->x));
	printf("y: %d, %p\n", mrt->y, &(mrt->y));
	printf("aux: %s, %p\n", mrt->aux, &(mrt->aux));
	printf("tab: %p, %p\n", mrt->tab, &(mrt->tab));
	printf("bonus: %d, %p\n", mrt->bonus, &(mrt->bonus));
}

int	mouse_handler(int mouse_code, int x, int y, t_mrt *mrt)
{
	int x_c;
	int y_c;

	mlx_mouse_get_pos(mrt->mlx_win, &x_c, &y_c);
	printf("%d %d code %d x %d y [%d - %d]\n", mrt->to_img, mouse_code, x, y, x_c, y_c);
	return (TRUE);
}

int main(int argc, char const *argv[])
{
	t_mrt	*mrt;

	// Hace poco cambiaron el subject, lo que me dejó un poco movido...
	// La cosa es que es relativamente fácil encontrar archivos 
	// para probar los viejos, no tanto los nuevos. Por esta razón 
	// el parseo esta para admitir archivos viejos, cuando tengamos varios
	// nuevos, es cuestion de cambiar dos tontadas
	if (argc < 2 || argc > 3)
		msg_error_exit("Args error. Type --help for instructions.");
	if (argc == 3)
		msg_error_exit("invalid argument\n");
	mrt = readfile_parser(argv[1]);
	parse_fix(mrt);
	// Incluir la opción de --help para mostrar mensaje de ayuda.
	mrt->mlx = mlx_init();
	mlx_starter(mrt);
	print_all_mrt(mrt);
	render_main(mrt);
	mrt->mlx_win = mlx_new_window(mrt->mlx, mrt->scn.w_x, mrt->scn.w_y,"miniRT");
	mlx_key_hook(mrt->mlx_win, keys_handler, mrt);
	mlx_hook(mrt->mlx_win, 17, 0L, window_handler, mrt);
	mlx_hook(mrt->mlx_win, 4, 1L << 2, mouse_handler, mrt);
	mlx_hook(mrt->mlx_win, 5, 1L << 3, mouse_handler, mrt);
	mlx_loop_hook(mrt->mlx, to_win, mrt);
	mlx_loop(mrt->mlx);
	return (SUCCESS);
}
