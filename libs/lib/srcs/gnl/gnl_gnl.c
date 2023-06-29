/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_gnl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/29 23:51:31 by mporras-          #+#    #+#             */
/*   Updated: 2022/05/16 13:18:16 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*get_next_line(int fd)
{	
	static char	*buffer[256];
	char		*rst;
	char		*reader;
	int			nl_len[2];

	if (fd < 0 || fd > 257 || BUFFER_SIZE < 1)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = NULL;
	nl_len[0] = ft_get_endline(buffer[fd]);
	nl_len[1] = ft_strlen_gnl(buffer[fd]);
	if (nl_len[0] == 0)
	{
		reader = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!reader)
			return (NULL);
		rst = ft_buffer_reader(fd, &buffer[fd], reader, &nl_len[0]);
		ft_safe_free_char(&reader);
	}
	else
		rst = ft_line_proccess(&buffer[fd], 0, &nl_len[0]);
	return (rst);
}

char	*ft_line_proccess(char **buffer, int bytes, int *nl_len)
{
	char	*rst;

	if (!*buffer)
		return (NULL);
	if (nl_len[0] == 0 && bytes == 0)
	{
		rst = ft_strdup_gnl(*buffer, nl_len[1]);
		*buffer = ft_delete_line_from_buffer(buffer, &nl_len[0]);
	}
	else
	{
		rst = ft_substr_gnl(*buffer, 0, nl_len[0], &nl_len[0]);
		*buffer = ft_delete_line_from_buffer(buffer, &nl_len[0]);
	}
	return (rst);
}

char	*ft_buffer_reader(int fd, char **buffer, char *reader, int *nl_len)
{
	int	bytes;
	int	nl_reader;

	bytes = 0;
	while (nl_len[0] == 0)
	{
		bytes = read(fd, reader, BUFFER_SIZE);
		if (bytes <= 0)
			break ;
		reader[bytes] = '\0';
		nl_len[1] += bytes;
		nl_reader = ft_get_endline(reader);
		if (!*buffer)
			*buffer = ft_strdup_gnl(reader, bytes);
		else
			*buffer = ft_strjoin_gnl(*buffer, reader, bytes, &nl_len[0]);
		if (*buffer == NULL)
			break ;
		if (nl_reader > 0)
			nl_len[0] = (nl_len[1] - bytes) + nl_reader;
	}
	if (bytes < 0 || !*buffer)
		return (NULL);
	return (ft_line_proccess(buffer, bytes, &nl_len[0]));
}

char	*ft_delete_line_from_buffer(char **buffer, int *nl_len)
{
	char	*rst;

	if (nl_len[0] == nl_len[1] || (nl_len[0] == 0 && nl_len[1] > 0))
	{
		ft_safe_free_char(buffer);
		return (NULL);
	}
	rst = ft_substr_gnl(*buffer, nl_len[0], nl_len[1] - nl_len[0], &nl_len[0]);
	ft_safe_free_char(buffer);
	return (rst);
}

int	ft_get_endline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}
