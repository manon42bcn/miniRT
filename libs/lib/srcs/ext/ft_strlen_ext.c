/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_ext.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 22:46:19 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/09 22:46:19 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_is_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

size_t	ft_len_charset(char const *s, char *charset)
{
	size_t	rst;

	rst = 0;
	while (s[rst])
	{
		if (ft_is_charset(s[rst], charset) == TRUE)
			return (rst);
		rst++;
	}
	return (rst);
}
