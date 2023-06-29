/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:25:20 by mporras           #+#    #+#             */
/*   Updated: 2022/06/03 22:10:10 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char const *s1, char const *s2, char sep)
{
	char	*rst;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2 || !sep)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	rst = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 2));
	if (rst == NULL)
		return (NULL);
	ft_memcpy(rst, s1, len_s1);
	rst[len_s1] = sep;
	ft_memcpy(&rst[len_s1 + 1], s2, len_s2);
	rst[len_s1 + len_s2 + 1] = '\0';
	return (rst);
}

char	*ft_strjoin_clean_char(char **s1, char **s2, char sep, int clean)
{
	char	*rst;
	size_t	len_s1;
	size_t	len_s2;

	if (!*s1 && !*s2)
		return (NULL);
	len_s1 = ft_strlen(*s1);
	len_s2 = ft_strlen(*s2);
	rst = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 2));
	if (rst == NULL)
		return (NULL);
	if (s1)
		ft_memcpy(rst, *s1, len_s1);
	rst[len_s1] = sep;
	if (*s2)
		ft_memcpy(&rst[len_s1 + 1], *s2, len_s2);
	rst[len_s1 + len_s2 + 1] = '\0';
	if (*s1 && (clean == 1 || clean == 0))
		ft_safe_free_char(s1);
	if (*s2 && (clean == 2 || clean == 0))
		ft_safe_free_char(s2);
	return (rst);
}
