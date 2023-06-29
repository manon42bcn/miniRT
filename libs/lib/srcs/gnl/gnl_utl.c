/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 23:54:08 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/01 11:44:56 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_gnl(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr_gnl(char *s, int start, int len, int *nl_len)
{
	char	*rst;

	if (!s)
		return (NULL);
	if (len > (nl_len[1] - start))
		len = nl_len[1] - start;
	if (start > nl_len[1])
		len = 0;
	rst = (char *)malloc(sizeof(char) * (len + 1));
	if (rst == NULL)
		return (NULL);
	rst[len] = '\0';
	ft_memcpy_gnl(rst, &s[start], len);
	return (rst);
}

char	*ft_strdup_gnl(char *src, int len)
{
	char	*dst;

	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (dst == NULL)
		return (NULL);
	dst[len] = '\0';
	while (len-- > 0)
		dst[len] = src[len];
	return (dst);
}

char	*ft_strjoin_gnl(char *s1, char *s2, int bytes, int *nl_len)
{
	char	*rst;

	if (!s1 || !s2)
		return (NULL);
	rst = (char *)malloc(sizeof(char) * (nl_len[1] + 1));
	if (rst == NULL)
		return (NULL);
	rst[nl_len[1]] = '\0';
	ft_memcpy_gnl(rst, s1, nl_len[1] - bytes);
	ft_memcpy_gnl(&rst[nl_len[1] - bytes], s2, bytes);
	ft_safe_free_char(&s1);
	return (rst);
}

void	*ft_memcpy_gnl(char *dest, char *src, int n)
{
	int	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
