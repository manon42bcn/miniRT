/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 16:24:36 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/20 22:19:19 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//void *ft_sec_malloc(size_t size)
//{
//	void	*rst;
//
//	rst = malloc(size);
//	if (!rst)
//	{
//		perror("[miniRT] Error ");
//		exit(ERROR);
//	}
//	return (rst);
//}
//
//void	*ft_sec_calloc(size_t size)
//{
//	void	*rst;
//	rst = ft_calloc(size, 1);
//	if (!rst)
//	{
//		perror("[miniRT] Error ");
//		exit(ERROR);
//	}
//	return (rst);
//}

void ft_safe_free(void *ptr)
{
	if (!ptr)
		return ;
	free(ptr);
	ptr = NULL;
}

//void	ft_perror(char *msg)
//{
////	ft_putstr_fd("miniRT: ", STDERR_FILENO);
//	perror(msg);
//	exit(ERROR);
//}
