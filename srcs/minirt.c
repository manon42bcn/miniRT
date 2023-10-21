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

void		printVector(t_v3d *vector)
{
	printf("[%f x %f y %f z]", vector->x, vector->y, vector->z);
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
	if (mrt->scn.res_init == FALSE)
		my_mlx_getScreenSize(&(mrt->scn.w_x), &(mrt->scn.w_y));
	mrt->scn.ratio = (double)mrt->scn.w_x / (double)mrt->scn.w_y;
	while (node)
	{
		node->ratio = mrt->scn.ratio;
		node = node->next;
	}
	mrt->clean_window = &mlx_clear_window;
	mrt->clean_image = &mlx_destroy_image;
	mrt->window = FALSE;
	load_hooks(mrt);
	mlx_starter(mrt);
	get_bumps_textures(mrt);
}

/**
 * @brief Finds the closest object intersected by a given ray.
 *
 * This function traverses the list of scene objects to determine which one
 * is the closest object that the ray intersects. The distance to the closest
 * intersection point is stored in the `closest_intersection` parameter.
 *
 * @param ray The ray for which intersections with scene objects are checked.
 * @param obj Pointer to the head of the list of scene objects.
 * @param closest_intersection Pointer to store the distance to the closest
 * intersection point.
 *
 * @return t_obj* Returns a pointer to the closest intersected object,
 * or NULL if no object is intersected.
 */
t_obj	*get_selected(t_ray ray, t_obj *obj, double *closest_intersection)
{
	double		dist;
	t_solver	solve;
	t_obj		*rst;

	rst = NULL;
	while (obj)
	{
		solve = get_solver(obj->type);
		dist = solve(ray.from, ray.to, obj);
		if (dist > EPSILON && dist < *closest_intersection)
		{
			rst = obj;
			*closest_intersection = dist;
		}
		obj = obj->next;
	}
	return (rst);
}

/**
 * @brief Processes the mouse selection for objects in a scene.
 *
 * This function detects if a mouse click was performed over an object
 * on the scene. If so, the object is marked as selected and its color
 * is updated to indicate the selection.
 *
 * @param mouse_code The code associated with the mouse event.
 * @param x X-coordinate of the mouse click.
 * @param y Y-coordinate of the mouse click.
 * @param mrt Pointer to the main renderer structure, which contains
 * scene details and settings.
 *
 * @return int Returns TRUE if an object was successfully selected,
 * FALSE otherwise.
 */
int	mouse_select(int mouse_code, int x, int y, t_mrt *mrt)
{
	double	closest;
	t_ray	rfp;
	t_obj	*obj_hit;

	if (mrt->mode != TO_SELECT)
		return (FALSE);
	(void)mouse_code;
	mlx_mouse_get_pos(mrt->mlx_win, &x, &y);
	if (x < 0 || y < 0)
		return (FALSE);
	closest = INFINITY;
	rfp = (t_ray){mrt->cmr->position, ray_from_pixel(x, y, mrt)};
	obj_hit = get_selected(rfp, mrt->obj, &closest);
	if (obj_hit == NULL)
		return (FALSE);
	obj_hit->selected = TRUE;
	obj_hit->color = obj_hit->sel_color;
	mrt->mode = SELECTION;
	mrt->to_img = TO_RENDER;
	ft_putstr_fd("[OBJECT SELECTED - TRANSLATION MODE]\n", STDOUT_FILENO);
	return (TRUE);
}

void	map_obj(t_obj *obj)
{
	while (obj)
	{
		printf("%d type %p pointer\n", obj->type, obj);
		obj = obj->next;
	}
}

/**
 * @brief Deselects any selected object in the scene and reverts the
 * scene mode to NORMAL.
 *
 * If an object was previously selected in the scene, this function
 * will deselect it, revert its color back to its original, and notify
 * the user that the mode has changed back to NORMAL.
 * If the current mode is already NORMAL or TO_SELECT, the function will
 * exit early without making any changes.
 *
 * @param mrt Pointer to the scene's main struct which contains the list
 * of objects and the current mode.
 *
 * @return int Returns TRUE if an object was successfully deselected and
 * mode changed, FALSE otherwise.
 */
int	unselect_objet(t_mrt *mrt)
{
	t_obj	*obj;

	if (mrt->mode < SELECTION)
		return (FALSE);
	obj = mrt->obj;
	while (obj)
	{
		if (obj->selected == TRUE)
		{
			obj->selected = FALSE;
			obj->color = obj->orig_color;
		}
		obj = obj->next;
	}
	mrt->to_img = TO_RENDER;
	mrt->mode = NORMAL;
	ft_putstr_fd("[BACK TO NORMAL MODE]\n", STDOUT_FILENO);
	return (TRUE);
}

/**
 * @brief Activates the SELECTION MODE for the scene.
 *
 * If NORMAL mode is set, this function sets the scene mode
 * to TO_SELECT and provides a user notification that
 * SELECTION MODE has been activated.
 *
 * @param mrt Pointer to the scene's main struct which contains the
 * list of objects and the current mode.
 *
 * @return int Returns TRUE after setting the mode and printing the
 * notification message if NORMAL mode is active. Otherwise
 * return FALSE.
 */
int selection_mode(t_mrt *mrt)
{
	if (mrt->mode != NORMAL)
		return (FALSE);
	mrt->mode = TO_SELECT;
	ft_putstr_fd("[SELECTION MODE ACTIVATE]\n", STDOUT_FILENO);
	return (TRUE);
}

int	rotation_mode(t_mrt *mrt)
{
	if (mrt->mode != SELECTION)
		return (FALSE);
	mrt->mode = TO_ROTATE;
	ft_putstr_fd("[ROTATION MODE ACTIVATE]\n", STDOUT_FILENO);
	return (TRUE);
}

/**
 * @brief Retrieves the currently selected object from the list.
 *
 * This function iterates through the provided object list and returns
 * the first object that is marked as selected. If no object is selected,
 * it returns NULL.
 *
 * @param obj Pointer to the head of the object linked list.
 *
 * @return t_obj* Returns a pointer to the selected object,
 * or NULL if no object is selected.
 */
t_obj	*get_select_obj(t_obj *obj)
{
	while (obj && obj->selected == FALSE)
		obj = obj->next;
	return (obj);
}

/**
 * @brief Translates the selected object based on key inputs.
 *
 * If in SELECTION mode, this function translates the currently selected
 * object in the scene based on the arrow keys or plus/minus keys.
 * Note: Objects of type ELM_BOX are exempted from translations.
 *
 * @param key_dir Integer representing the key direction or command.
 * Values can be K_UP, K_DOWN, K_LEFT, K_RIGHT, K_PLUS, K_MINUS.
 * @param mrt Pointer to the main scene's struct containing the list
 * of objects and current mode.
 *
 * @return int Returns TRUE if the translation was successful,
 * otherwise returns FALSE.
 */
int	object_traslation(int key_dir, t_mrt *mrt)
{
	t_obj	*node;

	if (mrt->mode != SELECTION)
		return (FALSE);
	node = get_select_obj(mrt->obj);
	if (!node || (node->type == BOX))
		return (FALSE);
	if (key_dir == K_UP)
		node->elm.fig.centre.y += 0.1f;
	if (key_dir == K_DOWN)
		node->elm.fig.centre.y -= 0.1f;
	if (key_dir == K_LEFT)
		node->elm.fig.centre.x -= 0.1f;
	if (key_dir == K_RIGHT)
		node->elm.fig.centre.x += 0.1f;
	if (key_dir == K_PLUS)
		node->elm.fig.centre.z += 0.1f;
	if (key_dir == K_MINUS)
		node->elm.fig.centre.z -= 0.1f;
	mrt->to_img = TO_RENDER;
	return (TRUE);
}

/**
 * @brief Rotates the selected object based on key input.
 *
 * This function allows for the rotation of a selected object along the
 * x, y, and z-axes. The direction and axis of rotation depend on the key input.
 * The function will not operate if the current mode is not set to TO_ROTATE or
 * if the selected object is a SPHERE, which cannot be rotated.
 *
 * @param key The key code indicating the direction of rotation.
 * @param mrt Pointer to the main ray-tracing structure which holds information
 * about the scene and current mode.
 *
 * @return int Returns TRUE if the rotation was performed, and FALSE otherwise.
 */
int object_rotation(int key, t_mrt *mrt)
{
	t_obj	*node;

	if (mrt->mode != TO_ROTATE)
		return (FALSE);
	node = get_select_obj(mrt->obj);
	if (!node || node->type == SPHERE)
		return (FALSE);
	if (key == K_UP)
		node->elm.fig.orient = rotate_y(node->elm.fig.orient, RAD_ANGLE);
	if (key == K_DOWN)
		node->elm.fig.orient = rotate_y(node->elm.fig.orient, -RAD_ANGLE);
	if (key == K_LEFT)
		node->elm.fig.orient = rotate_x(node->elm.fig.orient, RAD_ANGLE);
	if (key == K_RIGHT)
		node->elm.fig.orient = rotate_x(node->elm.fig.orient, -RAD_ANGLE);
	if (key == K_PLUS)
		node->elm.fig.orient = rotate_z(node->elm.fig.orient, RAD_ANGLE);
	if (key == K_MINUS)
		node->elm.fig.orient = rotate_z(node->elm.fig.orient, -RAD_ANGLE);
	node->elm.fig.orient = ft_normal_v3d(node->elm.fig.orient);
	mrt->to_img = TO_RENDER;
	return (TRUE);
}

/**
 * @brief Activates the width-diameter adjustment mode for the selected object.
 *
 * This function switches the mode to TO_WIDTH for adjusting the width or
 * diameter of the currently selected object. The function will only activate
 * the mode if the current mode is SELECTION. Once activated, a corresponding
 * message is displayed to the standard output.
 *
 * @param mrt Pointer to the main ray-tracing structure which holds information
 * about the scene and current mode.
 *
 * @return int Returns TRUE if the mode was activated, and FALSE otherwise.
 */
int	width_mode(t_mrt *mrt)
{
	if (mrt->mode != SELECTION)
		return (FALSE);
	mrt->mode = TO_WIDTH;
	ft_putstr_fd("[WIDTH-DIAM MODE ACTIVATE]\n", STDOUT_FILENO);
	return (TRUE);
}

/**
 * @brief Adjusts the width or diameter of the selected object based on key
 * input.
 *
 * This function modifies the width/diameter of the currently selected object
 * either by increasing (if the key is K_PLUS) or decreasing (if the key is
 * K_MINUS) it. The modification is a 10% increment or decrement. Objects of
 * type PLANE cannot have their width adjusted, and the function returns early
 * in such cases. After adjusting the object's width, the scene needs to be
 * re-rendered, which is signified by setting mrt->to_img to TO_RENDER.
 *
 * @param key Integer representing the key pressed by the user. This can be
 * either K_PLUS or K_MINUS.
 * @param mrt Pointer to the main ray-tracing structure which holds information
 * about the scene and current mode.
 *
 * @return int Returns TRUE if the width was adjusted, and FALSE otherwise.
 */
int object_width(int key, t_mrt *mrt)
{
	t_obj	*obj;

	obj = get_select_obj(mrt->obj);
	if (obj == NULL || obj->type == PLANE)
		return (FALSE);
	if (key == K_PLUS)
		obj->elm.fig.width *= 1.1f;
	else if (key == K_MINUS && obj->elm.fig.width / 1.1f > 0)
		obj->elm.fig.width /= 1.1f;
	mrt->to_img = TO_RENDER;
	return (TRUE);
}

int	height_mode(t_mrt *mrt)
{
	if (mrt->mode != SELECTION)
		return (FALSE);
	mrt->mode = TO_HEIGHT;
	ft_putstr_fd("[HEIGHT MODE ACTIVATE]\n", STDOUT_FILENO);
	return (TRUE);
}

int object_height(int key, t_mrt *mrt)
{
	t_obj	*obj;

	obj = get_select_obj(mrt->obj);
	if (obj == NULL || obj->type == PLANE || obj->type == SPHERE)
		return (FALSE);
	if (key == K_PLUS)
		obj->elm.fig.width *= 1.1f;
	else if (key == K_MINUS && obj->elm.fig.width / 1.1f > 0)
		obj->elm.fig.width /= 1.1f;
	mrt->to_img = TO_RENDER;
	return (TRUE);
}

int	key_behaviour(int key, t_mrt *mrt)
{
	if (key == K_Q)
		return (unselect_objet(mrt));
	if (key == K_S)
		return (selection_mode(mrt));
	if (key == K_R)
		return (rotation_mode(mrt));
	if (key == K_D)
		return (width_mode(mrt));
	if (key == K_H)
		return (height_mode(mrt));
	if (mrt->mode == SELECTION
		&& (key == K_MINUS || key == K_PLUS || (key >= K_LEFT && key <= K_UP)))
		return (object_traslation(key, mrt));
	if (mrt->mode == TO_ROTATE
		&& (key == K_MINUS || key == K_PLUS || (key >= K_LEFT && key <= K_UP)))
		return (object_rotation(key, mrt));
	if (mrt->mode == TO_WIDTH
		&& (key == K_MINUS || key == K_PLUS))
		return (object_width(key, mrt));
	if (mrt->mode == TO_HEIGHT
		&& (key == K_MINUS || key == K_PLUS))
		return (object_width(key, mrt));
	return (FALSE);
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
	render_main(mrt);
	map_obj(mrt->obj);
	mrt->mlx_win = mlx_new_window(mrt->mlx, mrt->scn.w_x,
			mrt->scn.w_y, "miniRT");
	mlx_key_hook(mrt->mlx_win, key_behaviour, mrt);
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
