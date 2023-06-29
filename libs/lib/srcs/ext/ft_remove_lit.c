/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_lit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 23:22:07 by mporras-          #+#    #+#             */
/*   Updated: 2022/07/28 23:22:24 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline size_t	ft_lit_count(char *s, char c)
{
	size_t			i;
	size_t			count;
	unsigned char	sem;

	i = 0;
	count = 0;
	sem = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (sem == 0)
				count++;
			sem ^= 1;
		}
		else
		{
			if (sem == 1)
				sem ^= 1;
		}
		i++;
	}
	return (count);
}

static inline void	ft_iterate_remove(char **src, char **rst, int *o_c, char c)
{
	unsigned char	sem;

	sem = 0;
	while ((*src)[o_c[0]])
	{
		if ((*src)[o_c[0]] == c)
		{
			if (sem == 0)
				o_c[0] = o_c[0] + 1;
			else
			{
				(*rst)[o_c[1]] = (*src)[o_c[0]];
				o_c[0] = o_c[0] + 1;
				o_c[1] = o_c[1] + 1;
			}
			sem ^= 1;
			continue ;
		}
		(*rst)[o_c[1]] = (*src)[o_c[0]];
		o_c[0] = o_c[0] + 1;
		o_c[1] = o_c[1] + 1;
		if (sem == 1)
			sem ^= 1;
	}
}

char	*ft_remove_lit(char *s, char c)
{
	size_t	newlen;
	char	*rst;
	int		o_c[2];

	if (!s)
		return (NULL);
	if (ft_count_char(s, c) == 0)
		return (NULL);
	newlen = ft_strlen(s) - ft_lit_count(s, c);
	if (newlen <= 0)
		return (NULL);
	rst = (char *)malloc(sizeof(char) * (newlen + 1));
	if (rst == NULL)
		return (NULL);
	rst[newlen] = '\0';
	ft_init_vector(&o_c[0], 0, 2);
	ft_iterate_remove(&s, &rst, &o_c[0], c);
	return (rst);
}
