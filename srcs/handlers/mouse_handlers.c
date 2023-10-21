/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 00:41:04 by mporras-          #+#    #+#             */
/*   Updated: 2023/10/22 00:41:06 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Finds the closest object intersected by a given ray.
 *
 * This function traverses the list of scene objects to determine which one
 * is the closest object that the ray intersects. The distance to the closest
 * intersection point is stored in the `closest_intersection` parameter.
 *
 * @param ray The ray for which intersections with scene objects are checked.
 * @param obj Pointer to the head of the list of scene objects.
 * @param closest Pointer to store the distance to the closest
 * intersection point.
 *
 * @return t_obj* Returns a pointer to the closest intersected object,
 * or NULL if no object is intersected.
 */
static inline t_obj	*get_selected(t_ray ray, t_obj *obj, double *closest)
{
	double		dist;
	t_solver	solve;
	t_obj		*rst;

	rst = NULL;
	while (obj)
	{
		solve = get_solver(obj->type);
		dist = solve(ray.from, ray.to, obj);
		if (dist > EPSILON && dist < *closest)
		{
			rst = obj;
			*closest = dist;
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
int	selection_mode(t_mrt *mrt)
{
	if (mrt->mode != NORMAL)
		return (FALSE);
	mrt->mode = TO_SELECT;
	ft_putstr_fd("[SELECTION MODE ACTIVATE]\n", STDOUT_FILENO);
	return (TRUE);
}
