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

void	printingv3d(t_v3d *vector, char *msg)
{
	printf("%s - ", msg);
	printf("[%f x %f y %f z]\n", vector->x, vector->y, vector->z);
}

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

//static inline t_v3d	pix_to_win(int x, int y, t_mrt *mrt)
//{
//	t_v3d	p;
//
//	p.x = ((2 * ((float)x / mrt->scn.w_x)) - 1)
//		  * mrt->scn.ratio * mrt->cmr->fov;
//	p.y = (1 - (2 * ((float )y / mrt->scn.w_y))) * mrt->cmr->fov;
//	p.x = -p.x;
//	p.z = mrt->cmr->position.z;
//	return (p);
//}

t_v3d rotateY(t_v3d v, double theta) {
	double cosTheta = cos(theta);
	double sinTheta = sin(theta);
	return (t_v3d){
			cosTheta * v.x + sinTheta * v.z,
			v.y,
			-sinTheta * v.x + cosTheta * v.z
	};
}

void moveCamera(t_cmr *camera, double angle, t_v3d center, double radius) {
	double radianAngle = angle * (M_PI / 180.0);  // convierte grados a radianes

	// calcular la nueva posición de la cámara
	camera->position.x = center.x + radius * cos(radianAngle);
	camera->position.y = center.y + radius * sin(radianAngle);
	camera->position.z = center.z;

	// actualizar la dirección de la cámara para que mire hacia el centro
	camera->dir = ft_normal_v3d(ft_minus_v3d(center, camera->position));
}


int	mouse_handler(int mouse_code, int mouseX, int mouseY, t_mrt *mrt)
{
	printf("%d %d %d\n", mouse_code, mouseX, mouseY);

	t_v3d camaraPosition = mrt->cmr->position; // la posición de la cámara
	t_v3d cameraDirection = mrt->cmr->dir; // el vector de dirección de la cámara (normalizado)

	t_v3d lookAtPoint = ft_plus_v3d(camaraPosition, cameraDirection);
	printingv3d(&lookAtPoint, " Looking at ");
	moveCamera(mrt->cmr, 45, (t_v3d){0, 0, 0}, 50);

//	double angleInDegrees = 90;  // ángulo para rotar en grados.
//	double angleInRadians = angleInDegrees * M_PI / 180.0;  // convierte el ángulo a radianes.
//
//// asumimos que cameraDir es la dirección actual de la cámara.
//	double newX = mrt->cmr->dir.x * cos(angleInRadians) - mrt->cmr->dir.z * sin(angleInRadians);
//	double newZ = mrt->cmr->dir.x * sin(angleInRadians) + mrt->cmr->dir.z * cos(angleInRadians);
//
//// nueva dirección de la cámara.
//	t_v3d newCameraDir = {newX, mrt->cmr->dir.y, newZ};
//
//	mrt->cmr->dir = newCameraDir;

//	printf("%d \n", mouse_code);
//	double x = (2.0 * (double )mouseX / (double )mrt->scn.w_x) - 1.0;
//	double y = 1.0 - (2.0 * (double )mouseY / (double)mrt->scn.w_y);
//	double imageAspectRatio = (double )mrt->scn.w_x / (double)mrt->scn.w_y;
//	double Px = (2 * x - 1) * tan(mrt->cmr->inp_fov/2 * M_PI/180) * imageAspectRatio;
//	double Py = (1 - 2 * y) * tan(mrt->cmr->inp_fov/2 * M_PI/180);
//	t_v3d rayDir = ft_normal_v3d(ft_new_v3d(Px, Py, -1));  // la cámara asume que mira hacia -z
//	printf("%f x - %f - y %f z\n", rayDir.x, rayDir.y, rayDir.z);
//	mrt->cmr->position.x += Px;
//	mrt->cmr->position.y += Py;
	mrt->to_img = FALSE;
	return (TRUE);
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
