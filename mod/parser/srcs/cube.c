/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 20:03:40 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/24 21:57:12 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#ifdef BONUS

void setup_rectangle_for_box_face(t_obj *rectangle, t_obj *box, int axis, int side) {
    double offset;
    t_v3d normal = {0.0, 0.0, 0.0};

    switch(axis) {
        case 0:  // Eje X
            normal.x = side;
            offset = 0.5 * box->elm.box.width * side;
            rectangle->elm.rc.width = box->elm.box.depth;
            rectangle->elm.rc.height = box->elm.box.height;
            break;
        case 1:  // Eje Y
            normal.y = side;
            offset = 0.5 * box->elm.box.height * side;
            rectangle->elm.rc.width = box->elm.box.width;
            rectangle->elm.rc.height = box->elm.box.depth;
            break;
        case 2:  // Eje Z
            normal.z = side;
            offset = 0.5 * box->elm.box.depth * side;
            rectangle->elm.rc.width = box->elm.box.width;
            rectangle->elm.rc.height = box->elm.box.height;
            break;
    }

    rectangle->normal = normal;
    rectangle->elm.rc.centre = ft_plus_v3d(box->elm.box.centre, ft_scalar_v3d(offset, normal));
    rectangle->elm.rc.orient = box->elm.box.dir;
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
	box->elm.box.height = ft_atolf(mrt->tab[BOX_DEPTH]);
	if (!check_range(box->elm.box.width, 0, INFINITY))
		msg_error_parsing("Box depth out of range", mrt);
	get_common(mrt, BOX_DEPTH, "Box");
	box->elm.box.min.x = box->elm.box.centre.x - box->elm.box.width / 2.0;
	box->elm.box.min.y = box->elm.box.centre.y - box->elm.box.height / 2.0;
	box->elm.box.min.z = box->elm.box.centre.z - box->elm.box.depth / 2.0;
	box->elm.box.max.x = box->elm.box.centre.x + box->elm.box.width / 2.0;
	box->elm.box.max.y = box->elm.box.centre.y + box->elm.box.height / 2.0;
	box->elm.box.max.z = box->elm.box.centre.z + box->elm.box.depth / 2.0;
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