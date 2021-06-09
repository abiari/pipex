/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_append_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abiari <abiari@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 18:16:28 by abiari            #+#    #+#             */
/*   Updated: 2021/06/09 10:02:06 by abiari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

void	lst_append(t_list **lst, void *content)
{
	t_list	*current;
	t_list	*new;

	if (!lst)
		return ;
	current = *lst;
	if (current)
	{
		while (current->next)
			current = current->next;
		new = ft_lstnew(content);
		current->next = new;
	}
	else
	{
		new = ft_lstnew(content);
		*lst = new;
	}
}
