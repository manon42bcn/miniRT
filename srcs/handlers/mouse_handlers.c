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
 * is the closest object that the ray intersects.
 *
 * @param ray The ray for which intersections with scene objects are checked.
 * @param obj Pointer to the head of the list of scene objects.
 *
 * @return t_obj* Returns a pointer to the closest intersected object,
 * or NULL if no object is intersected.
 */
static inline t_obj	*get_selected(t_ray ray, t_obj *obj)
{
	double		dist;
	t_solver	solve;
	t_obj		*rst;
	double		closest;

	rst = NULL;
	closest = INFINITY;
	while (obj)
	{
		solve = get_solver(obj->type);
		dist = solve(ray.from, ray.to, obj);
		if (dist > EPSILON && dist < closest)
		{
			rst = obj;
			closest = dist;
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
	t_ray	rfp;
	t_obj	*obj_hit;

	(void)mouse_code;
	if (mrt->mode == NORMAL || mrt->mode > TO_HEIGHT)
		return (FALSE);
	mlx_mouse_get_pos(mrt->mlx_win, &x, &y);
	if (x < 0 || y < 0)
		return (FALSE);
	rfp = (t_ray){mrt->cmr->position, ray_from_pixel(x, y, mrt)};
	obj_hit = get_selected(rfp, mrt->obj);
	if (obj_hit == NULL)
		return (FALSE);
	if (mrt->sel_obj && mrt->sel_obj == obj_hit)
		return (TRUE);
	mrt->sel_obj->color = mrt->sel_obj->orig_color;
	mrt->sel_obj = obj_hit;
	obj_hit->color = obj_hit->sel_color;
	if (mrt->mode == TO_SELECT)
		mrt->mode = TO_TRANSLATE;
	mrt->to_img = TO_RENDER;
	ft_putstr_fd("[OBJECT SELECTED - TRANSLATION MODE]\n", STDOUT_FILENO);
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
