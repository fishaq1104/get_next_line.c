/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_ultil.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fishaq <fishaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:44:06 by fishaq            #+#    #+#             */
/*   Updated: 2023/08/23 16:25:50 by fishaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	append(t_list **lst, char *buff)
{
	t_list	*last_node;
	t_list	*new_node;

	last_node = find_last_node(*lst);
	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return ;
	if (last_node == NULL)
		*lst = new_node;
	else
		last_node->next = new_node;
	new_node->content = buff;
	new_node->next = NULL;
}

int	find_the_size(t_list *lst)
{
	int	count;
	int	i;

	count = 0;
	while (lst)
	{
		i = 0;
		while (lst->content[i])
		{
			if (lst->content[i] == '\n')
			{
				count++;
				return (count);
			}
			i++;
			count++;
		}
		lst = lst->next;
	}
	return (count);
}

t_list	*find_last_node(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	join_the_line(t_list *lst, char *theline)
{
	int	j;
	int	k;

	if (!lst)
		return ;
	k = 0;
	while (lst)
	{
		j = 0;
		while (lst->content[j])
		{
			if (lst->content[j] == '\n')
			{
				theline[k++] = '\n';
				theline[k] = '\0';
				return ;
			}
			theline[k++] = lst->content[j++];
		}
		lst = lst->next;
	}
	theline[k] = '\0';
}

void	clean(t_list *lst)
{
	t_list	*temp;

	while (lst)
	{
		temp = (lst)->next;
		free((lst)->content);
		free(lst);
		lst = temp;
	}
}
