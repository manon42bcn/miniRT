/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 22:40:46 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/06 22:42:56 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	if (!s1[i] && !s2[i])
		return (0);
	if (s1[i])
		return (((unsigned char *)s1)[i]);
	if (s2[i])
		return (((unsigned char *)s2)[i]);
	return (0);
}

int	ft_strict_n_cmp(char *s1, char *s2, size_t l1, size_t l2)
{
	size_t	i;

	i = 0;
	if (l1 == 0 || l1 != l2)
		return (0);
	while (i + 1 < l1 && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

int	ft_strict_cmp(char *s1, char *s2)
{
	size_t	i;
	size_t	l1;
	size_t	l2;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	i = 0;
	if (l1 != l2)
		return (-1);
	while (i + 1 < l1 && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}

int	ft_strncmp_fnc(char *s1, char *s2, size_t n, int (*str_to)(int))
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i + 1 < n && (s1[i] || s2[i]))
	{
		if (str_to(s1[i]) != str_to(s2[i]))
			return (str_to(s1[i]) != str_to(s2[i]));
		i++;
	}
	return (str_to(s1[i]) != str_to(s2[i]));
}

t_bool	ft_match_cmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (FALSE);
		i++;
	}
	if (s1[i] != s2[i])
		return (FALSE);
	return (TRUE);
}
