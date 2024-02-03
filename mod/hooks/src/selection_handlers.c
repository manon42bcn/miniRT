/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 00:41:04 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/16 22:16:27 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"

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
static inline t_obj	*get_selected(t_ray ray, t_obj *obj, t_mrt *mrt)
{
	double		dist;
	t_obj		*rst;
	double		closest;
	t_inter		inter;

	rst = NULL;
	closest = INFINITY;
	while (obj)
	{
		dist = mrt->get_solver(ray.from, ray.to, obj, &inter);
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
 * @return t_bool Returns TRUE if an object was successfully selected,
 * FALSE otherwise.
 */
t_bool	mouse_select(int mouse_code, int x, int y, t_mrt *mrt)
{
	t_ray	rfp;
	t_obj	*obj_hit;

	(void)mouse_code;
	if (mrt->mode != TO_SELECT)
		return (FALSE);
	mlx_mouse_get_pos(mrt->mlx_win, &x, &y);
	if (x < 0 || y < 0)
		return (FALSE);
	rfp = (t_ray){mrt->cmr->position, mrt->ray_pixel(x, y, mrt)};
	obj_hit = get_selected(rfp, mrt->obj, mrt);
	if (obj_hit == NULL)
		return (FALSE);
	if (mrt->sel_obj && mrt->sel_obj == obj_hit)
		return (TRUE);
	if (mrt->sel_obj)
		mrt->sel_obj->color = mrt->sel_obj->orig_color;
	mrt->sel_obj = obj_hit;
	obj_hit->color = obj_hit->sel_color;
	mrt->mode = TO_SELECTED;
	mrt->to_img = TO_RENDER;
	ft_putstr_fd("[OBJECT SELECTED - SELECT HOOK MODE]\n", STDOUT_FILENO);
	return (TRUE);
}
