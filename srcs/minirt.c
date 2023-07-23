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

static inline void	parse_fix(t_mrt *mrt)
{
	t_cmr	*node;

	node = mrt->cmr;
	if (mrt->scn.res_init == FALSE)
		my_mlx_getScreenSize(&(mrt->scn.w_x), &(mrt->scn.w_y));
// Para el debug, 1/3 de screen size
	mrt->scn.w_x /= 3;
	mrt->scn.w_y /= 3;
	printf("%d %d\n", mrt->scn.w_x, mrt->scn.w_y);
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

static inline t_v3d	pix_to_win(int n, t_pix pix, t_mrt *mrt)
{
	double	x_ofs;
	double	y_ofs;
	t_v3d	p;

	x_ofs = ((n % 3) * 0.5);
	y_ofs = ((n / 3) * 0.5);
	p.x = ((2 * ((pix.x + x_ofs) / pix.w_x)) - 1)
		  * mrt->scn.ratio * mrt->cmr->fov;
	p.y = (1 - (2 * ((pix.y + y_ofs) / pix.w_y))) * mrt->cmr->fov;
	p.x = -p.x;
	p.z = 1;
	return (p);
}


int	mouse_handler(int mouse_code, int x, int y, t_mrt *mrt)
{
	int x_c;
	int y_c;
	t_pix	to_pix;
	t_v3d	to_img;

	to_pix.x = x;
	to_pix.y = y;
	to_pix.w_x = mrt->scn.w_x;
	to_pix.w_y = mrt->scn.w_y;
	to_img = pix_to_win(8, to_pix, mrt);
	printf("[%f x] [%f y]\n", to_img.x, to_img.y);
	mlx_mouse_get_pos(mrt->mlx_win, &x_c, &y_c);
	printf("%d %d code %d x %d y [%d - %d]\n", mrt->to_img, mouse_code, x, y, x_c, y_c);
	mrt->cmr->position.x = to_img.x;
	mrt->cmr->position.y = to_img.y;
	mrt->to_img = FALSE;
	return (to_win(mrt));
}

int main(int argc, char const *argv[])
{
	t_mrt	*mrt;

	if (argc < 2 || argc > 3)
		msg_error_exit("Args error. Type --help for instructions.");
	if (argc == 3)
		msg_error_exit("invalid argument\n");
	mrt = readfile_parser(argv[1]);
	parse_fix(mrt);
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
	clear_all(mrt, SUCCESS, NULL, NULL);
	return (SUCCESS);
}
