/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_clean.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/11 01:25:20 by mporras           #+#    #+#             */
/*   Updated: 2022/06/02 13:23:49 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_clean(char **s1, char **s2, int clean)
{
	char	*rst;
	size_t	len_s1;
	size_t	len_s2;

	if (!*s1 && !*s2)
		return (NULL);
	len_s1 = ft_strlen(*s1);
	len_s2 = ft_strlen(*s2);
	rst = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (rst == NULL)
		return (NULL);
	if (s1)
		ft_memcpy(rst, *s1, len_s1);
	if (s2)
		ft_memcpy(&rst[len_s1], *s2, len_s2);
	rst[len_s1 + len_s2] = 0;
	if (*s1 && (clean == 1 || clean == 0))
		ft_safe_free_char(s1);
	if (*s2 && (clean == 2 || clean == 0))
		ft_safe_free_char(s2);
	return (rst);
}

char	*ft_strjoin_clean_one(char **s1, char *s2)
{
	char	*rst;
	size_t	len_s1;
	size_t	len_s2;

	if (!*s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(*s1);
	len_s2 = ft_strlen(s2);
	rst = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (rst == NULL)
		return (NULL);
	if (s1)
		ft_memcpy(rst, *s1, len_s1);
	if (s2)
		ft_memcpy(&rst[len_s1], s2, len_s2);
	rst[len_s1 + len_s2] = 0;
	ft_safe_free_char(s1);
	return (rst);
}

char	*ft_strjoin_clean_two(char *s1, char **s2)
{
	char	*rst;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !*s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(*s2);
	rst = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (rst == NULL)
		return (NULL);
	if (s1)
		ft_memcpy(rst, s1, len_s1);
	if (s2)
		ft_memcpy(&rst[len_s1], *s2, len_s2);
	rst[len_s1 + len_s2] = 0;
	ft_safe_free_char(s2);
	return (rst);
}

char	*ft_strjoin_clear_ptn(char *s1, char *s2, int clean)
{
	char	*rst;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	rst = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (rst == NULL)
		return (NULL);
	if (s1)
		ft_memcpy(rst, s1, len_s1);
	if (s2)
		ft_memcpy(&rst[len_s1], s2, len_s2);
	rst[len_s1 + len_s2] = 0;
	if (s1 && (clean == 1 || clean == 0))
		free(s1);
	if (s2 && (clean == 2 || clean == 0))
		free(s2);
	return (rst);
}
