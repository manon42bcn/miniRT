/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:03:40 by mporras-          #+#    #+#             */
/*   Updated: 2024/01/13 01:55:01 by mporras-         ###   ########.fr       */
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
t_rectangle	build_box_face(t_box *box, int axis, double direction)
{
	t_rectangle	face;
	t_dec		off[3];

	off[0] = 0.5L * direction * box->depth;
	off[1] = 0.5L * direction * box->height;
	off[2] = 0.5L * direction * box->width;
	if (axis == 0)
	{
		face.height = box->height;
		face.width = box->width;
	}
	if (axis == 1)
	{
		face.height = box->depth;
		face.width = box->width;
	}
	if (axis == 2)
	{
		face.height = box->depth;
		face.width = box->height;
	}
	face.orient = ft_v3d_identity(axis);
	face.centre = ft_plus_v3d(box->centre,
			ft_scalar_v3d(off[axis], face.orient));
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
 * @param box Pointer to box structure, to save its faces.
 */

void	build_box(t_box *box)
{
	int	side;
	int	face;
	int	axis;

	axis = 0;
	while (axis < 3)
	{
		side = -1;
		while (side <= 1)
		{
			face = axis * 2 + (side + 1) / 2;
			box->faces[face] = build_box_face(box, axis, side);
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
	t_mode	mode;

	mode = element_check(BOX, mrt);
	if (mode == ERROR_MODE)
		msg_error_parsing("Wrong data elements to build box/cube", mrt);
	mrt->obj = object_builder(BOX, mrt->obj);
	box = mrt->obj;
	box->elm.box.centre = get_v3d(mrt, mrt->tab[BOX_CENTRE], V3D_COOR);
	box->elm.box.width = ft_atolf(mrt->tab[BOX_WIDTH]);
	if (!check_range(box->elm.box.width, 0, INFINITY))
		msg_error_parsing("Box width out of range", mrt);
	box->elm.box.height = ft_atolf(mrt->tab[BOX_HEIGHT]);
	if (!check_range(box->elm.box.width, 0, INFINITY))
		msg_error_parsing("Box height out of range", mrt);
	box->elm.box.depth = ft_atolf(mrt->tab[BOX_DEPTH]);
	if (!check_range(box->elm.box.width, 0, INFINITY))
		msg_error_parsing("Box depth out of range", mrt);
	get_common(mrt, BOX_DEPTH, "Box", mode);
	build_box(&mrt->obj->elm.box);
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
