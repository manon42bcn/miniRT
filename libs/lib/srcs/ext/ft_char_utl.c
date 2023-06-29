/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_utl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 11:44:45 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/28 18:37:55 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlenchar(const char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	ft_strict_lenchar(const char *s, char c)
{
	int	i;

	i = -1;
	if (!s)
		return (-1);
	while (s[++i])
	{
		if (s[i] == c)
			return (i);
	}
	return (-1);
}

size_t	ft_strlen_max(const char *s, size_t max)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (i > max)
			break ;
		i++;
	}
	return (i);
}

size_t	ft_count_char(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			count++;
		i++;
	}
	return (count);
}

char	ft_last_char(char *s)
{
	size_t	i;
	char	c;

	if (!s)
		return (0);
	i = 0;
	c = 0;
	while (s[i])
	{
		c = s[i];
		i++;
	}
	return (c);
}
