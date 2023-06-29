/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mporras- <manon42bcn@yahoo.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 00:29:32 by mporras-          #+#    #+#             */
/*   Updated: 2023/06/09 22:46:12 by mporras-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_to_lst(t_list **head, char const *s, char *charset)
{
	char	*content;
	size_t	size;

	size = ft_len_charset(s, charset);
	content = ft_strndup(s, size);
	if (!content)
		return (-1);
	ft_lstadd_front(head, ft_lstnew(content));
	return (size);
}

char	**ft_safe_end(t_list **head)
{
	ft_lstclear(head, free);
	return (NULL);
}

char	**ft_build_tab(t_list **head)
{
	char	**rst;
	t_list	*node;
	int		deep;

	node = *head;
	deep = ft_lstsize(node);
	rst = (char **)ft_calloc(deep + 1, sizeof(char *));
	if (!rst)
		return (ft_safe_end(head));
	deep--;
	while (node)
	{
		rst[deep] = node->content;
		node = node->next;
		deep--;
	}
	ft_lstclear(head, NULL);
	return (rst);
}

char	**ft_split_cs(char const *s, char *charset)
{
	t_list	*head;
	int		i;
	int		eval;

	head = NULL;
	i = 0;
	while (s[i])
	{
		eval = 1;
		if (ft_is_charset(s[i], charset) == FALSE)
			eval = ft_str_to_lst(&head, &s[i], charset);
		if (eval == -1)
			return (ft_safe_end(&head));
		i += eval;
	}
	return (ft_build_tab(&head));
}
