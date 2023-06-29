/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_clean.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 11:34:20 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/21 10:52:42 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline int	ft_trim_charset(char c, char const *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static inline void	ft_trim_fromto(char const *s1,
		char const *set, size_t *fromto)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	while (s1[i] && ft_trim_charset(s1[i], set) == 1)
		i++;
	fromto[0] = i;
	fromto[2] = len;
	fromto[1] = fromto[2] - 1;
	while (ft_trim_charset(s1[fromto[1]], set) == 1)
		fromto[1]--;
	if (fromto[0] == len)
	{
		fromto[2] = 0;
		fromto[1] = fromto[0] + 1;
	}
	else
		fromto[2] = (fromto[1] - fromto[0]) + 1;
	if (len == 0)
		fromto[2] = 0;
}

static inline void	ft_fill_str(char *s1, size_t *fromto, char **rst)
{
	size_t	i;

	i = 0;
	if (fromto[2] == 0)
		return ;
	while (i < fromto[2])
	{
		(*rst)[i] = s1[fromto[0]];
		i++;
		fromto[0]++;
	}
}

char	*ft_strtrim_clean(char *s1, char const *set)
{
	size_t	fromto[3];
	char	*rst;

	if (!set)
		return (s1);
	if (!s1)
		return (NULL);
	ft_trim_fromto(s1, set, &fromto[0]);
	rst = (char *)malloc(sizeof(char) * (fromto[2] + 1));
	if (rst == NULL)
		return (NULL);
	rst[fromto[2]] = '\0';
	ft_fill_str(s1, &fromto[0], &rst);
	ft_safe_free_char(&s1);
	return (rst);
}
