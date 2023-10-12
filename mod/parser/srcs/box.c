/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:03:40 by mporras-          #+#    #+#             */
/*   Updated: 2023/10/12 13:44:11 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#ifdef BONUS

/**
 * @brief Constructs a single face of a 3D box based on the given axis and
 * direction.
 *
 * Given a box's dimensions and its orientation, this function computes the
 * width, height, center, and orientation of a rectangle representing one face
 * of the box.
 *
 * @param box Pointer to the box structure, which holds the box's dimensions
 * and center.
 * @param axis Determines the axis of orientation (0 for X, 1 for Y, 2 for Z).
 * @param direction Specifies which direction along the axis to build the face
 * (-1 or 1).
 *
 * @return t_rectangle structure representing the constructed face of the box.
 */
t_rectangle	build_box_face(t_box *box, int axis, int direction)
{
	t_rectangle	face;
	t_v3d		offset;

	offset = (t_v3d){0.0, 0.0, 0.0};
	if (axis == 0)
	{
		offset.x = 0.5 * direction * box->width;
		face.width = box->depth;
		face.height = box->height;
	}
	else if (axis == 1)
	{
		offset.y = 0.5 * direction * box->height;
		face.width = box->depth;
		face.height = box->width;
	}
	else if (axis == 2)
	{
		offset.z = 0.5 * direction * box->depth;
		face.width = box->height;
		face.height = box->width;
	}
	face.centre = ft_plus_v3d(box->centre, offset);
	face.orient = ft_v3d_identity(axis);
	return (face);
}

/**
 * @brief Constructs all the faces for the box contained within the
 * main ray-tracer structure.
 *
 * This function populates the `faces` array in the `box` element of the
 * provided `mrt` structure. Each face is represented by a rectangle,
 * built using the `build_box_face` function.
 *
 * @param mrt Pointer to the main ray-tracer structure, which contains
 * details about the box object.
 */
void	build_box(t_mrt *mrt)
{
	int	axis;
	int	side;
	int	face_idx;

	axis = 0;
	while (axis < 3)
	{
		side = -1;
		while (side <= 1)
		{
			face_idx = axis * 2 + (side + 1) / 2;
			mrt->obj->elm.box.faces[face_idx] = build_box_face
				(&mrt->obj->elm.box, axis, side);
			side += 2;
		}
		axis++;
	}
}

/**
 * @brief Parses input to populate a box object's attributes.
 * -BONUS VERSION-
 * This function is responsible for reading the input related to a box
 * and populating the corresponding attributes in the `obj` structure.
 * It ensures the cube's side and are correctly extracted
 * and retrieves common attributes using the `get_common` function.
 *
 * min and max vectors are calculated here, to make normal at
 * hit direction step faster
 *
 * @param mrt  Main structure containing all parsed data.
 */
void	inp_box(t_mrt *mrt)
{
	t_obj	*box;

	if (ft_count_tab(mrt->tab) != ELM_BOX)
		msg_error_parsing("Wrong data elements to build box/cube", mrt);
	mrt->obj = object_builder(BOX, mrt->obj);
	box = mrt->obj;
	box->elm.box.centre = get_v3d(mrt, mrt->tab[BOX_CENTRE], V3D_COOR);
	box->elm.box.dir = get_v3d(mrt, mrt->tab[BOX_ORIENTATION], V3D_NORM);
	box->normal = box->elm.box.dir;
	box->elm.box.width = ft_atolf(mrt->tab[BOX_WIDTH]);
	if (!check_range(box->elm.box.width, 0, INFINITY))
		msg_error_parsing("Box width out of range", mrt);
	box->elm.box.height = ft_atolf(mrt->tab[BOX_HEIGHT]);
	if (!check_range(box->elm.box.width, 0, INFINITY))
		msg_error_parsing("Box height out of range", mrt);
	box->elm.box.depth = ft_atolf(mrt->tab[BOX_DEPTH]);
	if (!check_range(box->elm.box.width, 0, INFINITY))
		msg_error_parsing("Box depth out of range", mrt);
	get_common(mrt, BOX_DEPTH, "Box");
	build_box(mrt);
}

#else

/**
 * @brief Displays an error when trying to parse a cube in
 * the mandatory version.
 *
 * @param mrt The main structure containing all parsed data.
 */
void	inp_box(t_mrt *mrt)
{
	msg_error_parsing("Box is not supported at mandatory version", mrt);
}

#endif
