/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_general_utl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 00:35:30 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/20 22:15:04 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_init_vector(int *vector, int value, int size)
{
	while (size--)
		vector[size] = value;
}

void	ft_safe_free_char(char **s)
{
	if (!s)
		return ;
	if (*(s))
	{
		free(*(s));
		*(s) = NULL;
	}
}

int	ft_check_by_fnc(char *s, int (f)(int))
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (f(s[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
