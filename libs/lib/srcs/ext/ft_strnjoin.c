/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:18:04 by mporras-          #+#    #+#             */
/*   Updated: 2022/06/20 13:58:25 by msoler-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2,
			size_t len_s1, size_t len_s2)
{
	char	*rst;

	if (!s1 || !s2)
		return (NULL);
	rst = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (rst == NULL)
		return (NULL);
	ft_memcpy(rst, s1, len_s1);
	ft_memcpy(&rst[len_s1], s2, len_s2);
	rst[len_s1 + len_s2] = 0;
	return (rst);
}

char	*ft_strnjoin_clean(char *s1, char *s2,
			size_t len_s1, size_t len_s2)
{
	char	*rst;

	if (!s1 && !s2)
		return (NULL);
	rst = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (rst == NULL)
		return (NULL);
	if (s1)
		ft_memcpy(rst, s1, len_s1);
	if (s2)
		ft_memcpy(&rst[len_s1], s2, len_s2);
	rst[len_s1 + len_s2] = 0;
	if (s1)
		ft_safe_free_char(&s1);
	if (s2)
		ft_safe_free_char(&s2);
	return (rst);
}
