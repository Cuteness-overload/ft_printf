/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebesnoin <ebesnoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 05:47:20 by ebesnoin          #+#    #+#             */
/*   Updated: 2024/04/20 06:22:29 by ebesnoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*prev;
	t_list	*curr;

	curr = *lst;
	while (curr->next != NULL)
	{
		prev = curr;
		curr = curr->next;
		del(prev->content);
		free(prev);
	}
	del(curr->content);
	free(curr);
	*lst = NULL;
}
