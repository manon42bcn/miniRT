/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 00:41:52 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/21 21:52:25 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

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
int	object_traslation(int key, t_mrt *mrt)
{
	t_obj	*node;

	if (mrt->mode != TO_TRANSLATE)
		return (FALSE);
	node = mrt->sel_obj;
	if (!node || (node->type == BOX))
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

void	rotation_perp(t_obj *node)
{
	if (node->type != ELLIPS)
		return ;
	node->elm.elp.dirx = ft_perp_v3d(node->elm.elp.dir);
	node->elm.elp.diry = ft_cross_v3d(node->elm.elp.dir, node->elm.elp.dirx);
}

int	object_rotation(int key, t_mrt *mrt)
{
	t_obj	*node;

	if (mrt->mode != TO_ROTATE)
		return (FALSE);
	node = mrt->sel_obj;
	if (!node || node->type == SPHERE)
		return (FALSE);
	if (key == K_UP)
		node->elm.fig.orient = ft_rot_v3d_y(node->elm.fig.orient, RAD_ANGLE);
	if (key == K_DOWN)
		node->elm.fig.orient = ft_rot_v3d_y(node->elm.fig.orient, -RAD_ANGLE);
	if (key == K_LEFT)
		node->elm.fig.orient = ft_rot_v3d_x(node->elm.fig.orient, RAD_ANGLE);
	if (key == K_RIGHT)
		node->elm.fig.orient = ft_rot_v3d_x(node->elm.fig.orient, -RAD_ANGLE);
	if (key == K_PLUS)
		node->elm.fig.orient = ft_rot_v3d_z(node->elm.fig.orient, RAD_ANGLE);
	if (key == K_MINUS)
		node->elm.fig.orient = ft_rot_v3d_z(node->elm.fig.orient, -RAD_ANGLE);
	node->elm.fig.orient = ft_normal_v3d(node->elm.fig.orient);
	rotation_perp(node);
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
int	object_width(int key, t_mrt *mrt)
{
	t_obj	*obj;

	obj = mrt->sel_obj;
	if (obj == NULL || obj->type == PLANE || obj->type == ELLIPS)
		return (FALSE);
	if (key == K_PLUS)
		obj->elm.fig.width *= SIZE_FACTOR;
	else if (key == K_MINUS && obj->elm.fig.width / SIZE_FACTOR > 0)
		obj->elm.fig.width /= SIZE_FACTOR;
	mrt->to_img = TO_RENDER;
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
int	object_height(int key, t_mrt *mrt)
{
	t_obj	*obj;

	obj = mrt->sel_obj;
	if (obj == NULL || obj->type == PLANE || obj->type == SPHERE
		|| obj->type == ELLIPS)
		return (FALSE);
	if (key == K_PLUS)
		obj->elm.fig.height *= SIZE_FACTOR;
	else if (key == K_MINUS && obj->elm.fig.height / SIZE_FACTOR > 0)
		obj->elm.fig.height /= SIZE_FACTOR;
	mrt->to_img = TO_RENDER;
	return (TRUE);
}
