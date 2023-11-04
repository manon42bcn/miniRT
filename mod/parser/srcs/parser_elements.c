/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 15:39:45 by mporras-          #+#    #+#             */
/*   Updated: 2023/11/04 15:39:48 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

#ifdef BONUS

t_mode	element_check(int type, t_mrt *mrt)
{
	int				tab_size;
	static size_t	elements[] = {4, 4, 6,
		6, 5, 7, 6, 6};

	tab_size = ft_count_tab(mrt->tab);
	if (tab_size == elements[type])
		return (MANDATORY);
	if (type == SPHERE)
	{
		if (tab_size == elements[type] + 4)
			return (BONUS_MODE);
		else if (tab_size == elements[type] + 5)
			return (BUMP_MODE);
		return (ERROR_MODE);
	}
	if (tab_size == elements[type] + 4)
		return (BONUS_MODE);
	return (ERROR_MODE);
}

#else

t_mode	element_check(int type, t_mrt *mrt)
{
	static size_t	elements[] = {4, 4, 6};

	if (ft_count_tab(mrt->tab) == elements[type])
		return (MANDATORY);
	return (ERROR_MODE);
}

#endif
