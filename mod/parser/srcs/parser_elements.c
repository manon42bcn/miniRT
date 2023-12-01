/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:39:45 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/17 22:21:01 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#ifdef BONUS

/**
 * @brief Check the validity of the provided elements based on the object type.
 *
 * This function checks the validity of the provided elements based on the
 * object type. It compares the number of elements in the input with the
 * expected number of elements for the specified object type. The function
 * returns the mode (MANDATORY, BONUS_MODE, BUMP_MODE, or ERROR_MODE) based on
 * the comparison result.
 * This approach allows the render of mandatory format files at bonus version.
 *
 * @param type The object type.
 * @param mrt A pointer to the MiniRT structure.
 * @return The mode indicating the validity of the provided elements.
 */
t_mode	element_check(int type, t_mrt *mrt)
{
	size_t			tab_size;
	static size_t	elements[] = {4, 4, 6,
		6, 5, 7, 6, 7};

	tab_size = ft_count_tab(mrt->tab);
	if (tab_size == elements[type])
		return (MANDATORY);
	if (tab_size == elements[type] + 1)
		return (BONUS_MODE);
	else if (tab_size == elements[type] + 2)
		return (BUMP_MODE);
	return (ERROR_MODE);
}

#else

/**
 * @brief Check the validity of the provided elements based on the object type.
 *
 * This function checks the validity of the provided elements based on the
 * object type. It compares the number of elements in the input with the
 * expected number of elements for the specified object type. The function
 * returns the mode (MANDATORY or ERROR_MODE) based on
 * the comparison result.
 *
 * @param type The object type.
 * @param mrt A pointer to the MiniRT structure.
 * @return The mode indicating the validity of the provided elements.
 */
t_mode	element_check(int type, t_mrt *mrt)
{
	static size_t	elements[] = {4, 4, 6};

	if (ft_count_tab(mrt->tab) == elements[type])
		return (MANDATORY);
	return (ERROR_MODE);
}

#endif
