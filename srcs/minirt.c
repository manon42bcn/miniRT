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

t_obj	*closer_object(t_cmr *camera, t_obj *obj)
{
	double	dist;
	double	target;
	t_obj	*rst;

	target = 0;
	rst = NULL;
	while (obj)
	{
		dist = fabs(ft_distance_v3d(camera->position, obj->position));
		if (rst == NULL)
		{
			rst = obj;
			target = dist;
		}
		if (dist < target)
		{
			rst = obj;
			target = dist;
		}
		obj = obj->next;
	}
	return (rst);
}

void	printingv3d(t_v3d *vector, char *msg)
{
	printf("%s - ", msg);
	printf("[%f x %f y %f z]\n", vector->x, vector->y, vector->z);
}

void	close_to_cam(t_mrt *mrt)
{
	t_cmr	*node;

	node = mrt->cmr;
	while (node)
	{
		printf("%p previous pointer\n", node->close_obj);
		node->close_obj = closer_object(node, mrt->obj);
		printf("%p post check pointer\n", node->close_obj);
		node->orbit = sqrt(node->position.x * node->position.x
						   + node->position.y * node->position.y
						   + node->position.z * node->position.z);
		printf("%f why??\n", node->position.x * node->position.x
							 + node->position.y * node->position.y
							 + node->position.z * node->position.z);
		node = node->next;
	}
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
	close_to_cam(mrt);
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

void moveCamera(t_cmr *camera, double radianAngle, t_v3d center, double radius)
{
//	double radianAngle = angle * (M_PI / 180.0);  // convierte grados a radianes

	// calcular la nueva posición de la cámara
//	camera->position.x = center.x + radius * cos(radianAngle);
//	camera->position.y = center.y + radius * sin(radianAngle);
//	camera->position.z = center.z;

//	camera->position.x = center.x;
//	camera->position.y = center.y + radius * cos(radianAngle);
//	camera->position.z = center.z + radius * sin(radianAngle);

//	camera->position.x = center.x + radius * cos(radianAngle);
//	camera->position.y = center.y;
//	camera->position.z = center.z + radius * sin(radianAngle);

	camera->position.x = center.x + radius * cos(radianAngle);
	camera->position.y = center.y;
	camera->position.z = center.z + radius * sin(radianAngle);

	// actualizar la dirección de la cámara para que mire hacia el centro
	printingv3d(&camera->position, "New position");
	camera->dir = ft_normal_v3d(ft_minus_v3d(center, camera->position));
	printingv3d(&camera->dir, "New direction");
}
// Implementar:
// primero key y luego mouse, para rotar camara...
// rotar sobre objeto o sobre el centro del los ejes cartesianos...

int	mouse_handler(int mouse_code, int mouseX, int mouseY, t_mrt *mrt)
{
//	printf("%d %d %d\n", mouse_code, mouseX, mouseY);
//	static double angle = 0;
//
//	t_v3d camaraPosition = mrt->cmr->position; // la posición de la cámara
//	t_v3d cameraDirection = mrt->cmr->dir; // el vector de dirección de la cámara (normalizado)
//
//	t_v3d lookAtPoint = ft_plus_v3d(camaraPosition, cameraDirection);
//	printingv3d(&lookAtPoint, " Looking at ");
//	if (mouse_code == RIGHT_CLICK)
//		angle += RAD_ANGLE;
//	else
//		angle -= RAD_ANGLE;
//	double rad = sqrt(mrt->cmr->position.x * mrt->cmr->position.x + mrt->cmr->position.y * mrt->cmr->position.y + mrt->cmr->position.z * mrt->cmr->position.z);
//	printf("%f distance? %f orbit?\n", rad, mrt->cmr->orbit);
//	moveCamera(mrt->cmr, angle, mrt->cmr->close_obj->position, 25);
	t_hook	changes;

	changes = mrt->hooks[mrt->behaviour];
	if (changes)
		changes(mrt, mouseX, mouseY, mouse_code);
	mrt->to_img = TO_RENDER;
	return (TRUE);
}

void load_hooks_fnc(t_mrt *mrt)
{
	mrt->hooks[31] = &sphere_diam;
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
	load_hooks_fnc(mrt);
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
