/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 00:41:52 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/14 23:08:10 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

/**
 * @brief Rotate the dimensions of a box object.
 *
 * This function rotates the dimensions of a selected box object by swapping
 * its width, depth, and height. After the rotation, the function triggers the
 * rebuilding of the box with the updated dimensions.
 *
 * @param mrt A pointer to the Mini Ray Tracer structure.
 * @return always TRUE.
 */
static inline t_bool	box_rotation(t_mrt *mrt)
{
	t_obj	*box;
	double	tmp;

	box = mrt->sel_obj;
	tmp = box->elm.box.width;
	box->elm.box.width = box->elm.box.depth;
	box->elm.box.depth = box->elm.box.height;
	box->elm.box.height = tmp;
	build_box(&box->elm.box);
	mrt->to_img = TO_RENDER;
	return (TRUE);
}

/**
 * @brief Translates the selected object based on key inputs.
 *
 * If in SELECTION mode, this function translates the currently selected
 * object in the scene based on the arrow keys or plus/minus keys.
 * Note: Objects of type ELM_BOX are exempted from translations.
 *
 * @param key Integer representing the key direction or command.
 * Values can be K_UP, K_DOWN, K_LEFT, K_RIGHT, K_PLUS, K_MINUS.
 * @param mrt Pointer to the main scene's struct containing the list
 * of objects and current mode.
 *
 * @return int Returns TRUE if the translation was successful,
 * otherwise returns FALSE.
 */
t_bool	object_traslation(int key, t_mrt *mrt)
{
	t_obj	*node;

	if (mrt->mode != TO_TRANSLATE)
		return (FALSE);
	node = mrt->sel_obj;
	if (!node)
		return (FALSE);
	if (key == K_UP)
		node->elm.fig.centre.y += MOVE_FACTOR;
	if (key == K_DOWN)
		node->elm.fig.centre.y -= MOVE_FACTOR;
	if (key == K_LEFT)
		node->elm.fig.centre.x -= MOVE_FACTOR;
	if (key == K_RIGHT)
		node->elm.fig.centre.x += MOVE_FACTOR;
	if (key == K_PLUS)
		node->elm.fig.centre.z += MOVE_FACTOR;
	if (key == K_MINUS)
		node->elm.fig.centre.z -= MOVE_FACTOR;
	if (node->type == BOX)
		build_box(&node->elm.box);
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
t_bool	object_rotation(int key, t_mrt *mrt)
{
	t_obj	*node;
	t_v3d	dir;

	node = mrt->sel_obj;
	if (mrt->mode != TO_ROTATE || !node || node->type == SPHERE)
		return (FALSE);
	if (node->type == BOX)
		return (box_rotation(mrt));
	dir = node->elm.fig.orient;
	if (key == K_UP)
		node->elm.fig.orient = ft_rot_v3d(dir, Y_C, RAD_ANGLE);
	if (key == K_DOWN)
		node->elm.fig.orient = ft_rot_v3d(dir, Y_C, -RAD_ANGLE);
	if (key == K_LEFT)
		node->elm.fig.orient = ft_rot_v3d(dir, X_C, RAD_ANGLE);
	if (key == K_RIGHT)
		node->elm.fig.orient = ft_rot_v3d(dir, X_C, -RAD_ANGLE);
	if (key == K_PLUS)
		node->elm.fig.orient = ft_rot_v3d(dir, Z_C, RAD_ANGLE);
	if (key == K_MINUS)
		node->elm.fig.orient = ft_rot_v3d(dir, Z_C, -RAD_ANGLE);
	node->elm.fig.orient = ft_normal_v3d(node->elm.fig.orient);
	mrt->to_img = TO_RENDER;
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
t_bool	object_width(int key, t_mrt *mrt)
{
	t_obj	*obj;

	obj = mrt->sel_obj;
	if (obj == NULL || obj->type == PLANE)
		return (FALSE);
	if (key == K_PLUS)
		obj->elm.fig.width *= SIZE_FACTOR;
	else if (key == K_MINUS && obj->elm.fig.width / SIZE_FACTOR > 0)
		obj->elm.fig.width /= SIZE_FACTOR;
	mrt->to_img = TO_RENDER;
	if (obj->type == BOX)
		build_box(&obj->elm.box);
	return (TRUE);
}

/**
 * @brief Adjusts the height of the selected object based on key input.
 *
 * This function modifies the height of the currently selected object
 * either by increasing (if the key is K_PLUS) or decreasing (if the key
 * is K_MINUS) it. The modification is a 10% increment or decrement. Objects of
 * type PLANE and SPHERE cannot have their height adjusted, and the function
 * returns early in such cases. After adjusting the object's height, the scene
 * needs to be re-rendered, which is signified by setting mrt->to_img to
 * TO_RENDER.
 *
 * @param key Integer representing the key pressed by the user. This can be
 * either K_PLUS or K_MINUS.
 * @param mrt Pointer to the main ray-tracing structure which holds information
 * about the scene and current mode.
 *
 * @return int Returns TRUE if the height was adjusted, and FALSE otherwise.
 */
t_bool	object_height(int key, t_mrt *mrt)
{
	t_obj	*obj;

	obj = mrt->sel_obj;
	if (obj == NULL || obj->type == PLANE || obj->type == SPHERE)
		return (FALSE);
	if (key == K_PLUS)
		obj->elm.fig.height *= SIZE_FACTOR;
	else if (key == K_MINUS && obj->elm.fig.height / SIZE_FACTOR > 0)
		obj->elm.fig.height /= SIZE_FACTOR;
	if (obj->type == BOX)
		build_box(&obj->elm.box);
	mrt->to_img = TO_RENDER;
	return (TRUE);
}
