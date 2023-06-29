/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_replace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 23:31:40 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/30 23:32:03 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_char_replace(char **s, char org, char new)
{
	int	i;

	i = 0;
	if (!*s || !org || !new)
		return ;
	while (*(s)[i] != '\0')
	{
		if (*(s)[i] == org)
			*(s)[i] = new;
		i++;
	}
}
