/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_secure_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 21:05:08 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/30 21:44:53 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_sec_malloc(size_t size)
{
	void	*rst;

	rst = malloc(size);
	if (!rst)
		ft_perror("Secure Malloc failed.");
	return (rst);
}

void	*ft_sec_calloc(size_t size)
{
	void	*rst;

	rst = ft_calloc(size, 1);
	if (!rst)
		ft_perror("Secure Calloc failed.");
	return (rst);
}

void	ft_perror(char *msg)
{
	ft_putstr_fd("[Libft]", STDERR_FILENO);
	perror(msg);
	exit(ERROR);
}
