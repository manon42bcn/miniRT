/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_utl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 22:30:40 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/28 18:38:47 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_clear_tabs(char **tab)
{
	size_t	i;

	i = -1;
	if (!tab)
		return ;
	while (tab[++i])
	{
		if (tab[i])
			free(tab[i]);
		tab[i] = NULL;
	}
	free(tab);
	tab = NULL;
}

size_t	ft_count_tab(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_sort_str_tab(char **tab)
{
	int		i;
	int		k;
	char	*temp;

	i = 0;
	if (!tab)
		return ;
	while (tab[i] != 0)
	{
		k = i;
		while (tab[k] != 0)
		{
			if (ft_strcmp(tab[i], tab[k]) > 0)
			{
				temp = tab[i];
				tab[i] = tab[k];
				tab[k] = temp;
			}
			k++;
		}
		i++;
	}
}
