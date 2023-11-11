/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 08:39:55 by mgarcia-          #+#    #+#             */
/*   Updated: 2023/11/11 02:29:22 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Initializes the MiniLibX library and prepares the images for each
 * camera.
 *
 * Initializes the MiniLibX library and creates an image for each camera in
 * the scene. Each camera's image pointer, address, bytes per pixel, size,
 * and endianness are stored within the camera's structure.
 *
 * @param mrt A pointer to the general properties of the scene.
 */
static inline void	mlx_starter(t_mrt *mrt)
{
	t_cmr	*node;

	node = mrt->cmr;
	mrt->mlx = mlx_init();
	if (mrt->mlx == NULL)
		msg_error_exit("mlx init error");
	while (node)
	{
		node->img_ptr = mlx_new_image(mrt->mlx, mrt->scn.w_x, mrt->scn.w_y);
		node->addr = (int *)mlx_get_data_addr(node->img_ptr,
				&node->bpp, &node->size, &node->endian);
		node = node->next;
	}
}

/**
 * @brief Load bump textures for all objects in the scene.
 *
 * Iterates through all objects in the scene and, for those with bump mapping
 * enabled, loads the associated bump texture.
 *
 * @param mrt Pointer to the main RT structure that contains scene and
 * rendering details.
 */
static inline void	get_bumps_textures(t_mrt *mrt)
{
	t_obj	*node;

	node = mrt->obj;
	while (node)
	{
		if (node->bump)
		{
			node->xpm.img = mlx_xpm_file_to_image(mrt->mlx,
					node->xpm.path, &node->xpm.width,
					&node->xpm.height);
			node->xpm.addr = mlx_get_data_addr(node->xpm.img,
					&node->xpm.bbp, &node->xpm.ll,
					&node->xpm.endian);
		}
		node = node->next;
	}
}

/**
 * @brief Finalizes the parsing process and initializes specific rendering
 * parameters.
 * Once the scene is parsed, this function is used to set specific screen
 * parameters and initialize the scene's camera. It also sets up the
 * necessary hooks for interactivity.
 *
 * @param mrt Pointer to the main structure containing scene, camera,
 * and other essential data.
 */
static inline void	after_parse_process(t_mrt *mrt)
{
	t_cmr	*node;

	node = mrt->cmr;
	mrt->main_cam = node;
	if (mrt->scn.res_init == FALSE)
		my_mlx_getScreenSize(&(mrt->scn.w_x), &(mrt->scn.w_y));
//	mrt->scn.w_x /= 3;
//	mrt->scn.w_y /= 3;
	mrt->scn.ratio = (double)mrt->scn.w_x / (double)mrt->scn.w_y;
	while (node)
	{
		node->ratio = mrt->scn.ratio;
		node = node->next;
	}
	mrt->clean_window = &mlx_clear_window;
	mrt->clean_image = &mlx_destroy_image;
	mrt->get_solver = &get_solver;
	mrt->ray_pixel = &ray_from_pixel;
	mrt->window = FALSE;
	mlx_starter(mrt);
	get_bumps_textures(mrt);
}

/**
 * @brief Renders and displays the scene to the window.
 *
 * If the scene is set to be rendered, it will call the rendering function.
 * After rendering or if already rendered, it will then display the image
 * corresponding to the current camera to the window.
 *
 * @param mrt A pointer to the general properties of the scene.
 * @return Always returns TRUE. Used for hook functions in MiniLibX.
 */
int	to_win(t_mrt *mrt)
{
//	t_obj *obj;
	if (mrt->to_img == TO_RENDER)
	{
//		obj = mrt->obj;
//		while (obj)
//		{
//			printf("%f diam %f x %f y %f z [%s]\n", obj->elm.sph.radius, obj->elm.sph.centre.x, obj->elm.sph.centre.y,obj->elm.sph.centre.z, obj->xpm.path);
//			obj = obj->next;
//		}
//		printf("Cam [%f x %f y %f z] ORIENT [%f x %f y %f z]\n", mrt->cmr->position.x, mrt->cmr->position.y, mrt->cmr->position.z, mrt->cmr->dir.x, mrt->cmr->dir.y, mrt->cmr->dir.z);

		if (mrt->window == TRUE)
			render_main(mrt);
		mlx_put_image_to_window(mrt->mlx, mrt->mlx_win,
			mrt->cmr->img_ptr, 0, 0);
		mrt->to_img = RENDERED;
		mrt->window = TRUE;
	}
	return (TRUE);
}

int	print_help(void)
{
	printf("miniRT, version 1.0\n\n");
	printf("miniRT is a simple RayTracer program that generates images using the Raytracing protocol.\n");
    printf("This program is an introduction to the beautiful world of Raytracing.\n\n");
	printf("Usage: ./miniRT [map]\n\n");
    printf("Options:\n");
    printf("  --help\t\tShow this help message and exit.\n\n");
	printf("Arguments:\n");
    printf("  SCENE.rt\t\tA scene description file in the .rt format that describes the objects, lights, and camera.\n\n");
	return (1);
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
		msg_error_exit("Args error. Type --help for instructions.\n"); // VICTOR: Agregar salto de linea
	if (argc == 3)
		msg_error_exit("invalid argument\n");
	if (ft_strncmp("--help", (char *)argv[1], 7) == 0 && print_help()) // Siento que esta comparacion es sucia con otra que quizas pueda realizar manuel
		return(SUCCESS);
	mrt = readfile_parser(argv[1]); // parseo de objetos
	after_parse_process(mrt);
	render_main(mrt);
	mrt->mlx_win = mlx_new_window(mrt->mlx, mrt->scn.w_x,
			mrt->scn.w_y, "miniRT");
	mlx_key_hook(mrt->mlx_win, key_main, mrt);
	mlx_hook(mrt->mlx_win, 17, 0L, window_handler, mrt);
	mlx_hook(mrt->mlx_win, 4, 1L << 2, mouse_select, mrt);
	mlx_hook(mrt->mlx_win, 5, 1L << 3, mouse_select, mrt);
	mlx_loop_hook(mrt->mlx, to_win, mrt);
	mlx_loop(mrt->mlx);
	clear_all(mrt, SUCCESS, NULL, NULL);
	return (SUCCESS);
}
