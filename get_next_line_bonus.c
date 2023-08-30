/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fishaq <fishaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:35:50 by fishaq            #+#    #+#             */
/*   Updated: 2023/08/29 14:36:48 by fishaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	finder(t_list *lst)
{
	size_t	i;

	while (lst)
	{
		i = 0;
		while (lst->content && lst->content[i] && i < BUFFER_SIZE)
		{
			if (lst->content[i] == '\n')
				return (1);
			i++;
		}
		lst = lst->next;
	}
	return (0);
}

void	create_list(t_list **lst, int fd)
{
	int		i;
	char	*new;

	while (!finder(lst[fd]))
	{
		new = malloc((size_t)BUFFER_SIZE + 1);
		if (!new)
			return ;
		i = read(fd, new, BUFFER_SIZE);
		if (!i)
		{
			free(new);
			return ;
		}
		new[i] = '\0';
		append(lst, new, fd);
	}
}

char	*making_line(t_list *lst)
{
	char	*theline;
	int		len;

	len = find_the_size(lst);
	theline = (char *)malloc(sizeof(char) * (len + 1));
	if (!theline)
		return (NULL);
	join_the_line(lst, theline);
	return (theline);
}

void	clear_list(t_list **lst)
{
	int		j;
	int		k;
	t_list	*last_node;
	t_list	*new_node;

	j = 0;
	new_node = malloc(sizeof(t_list));
	if (!lst || !new_node)
		return ;
	new_node->next = NULL;
	last_node = find_last_node(*lst);
	while (last_node->content[j] != '\0' && last_node->content[j] != '\n')
		j++;
	if (last_node->content && last_node->content[j] == '\n')
		j++;
	new_node->content = malloc(sizeof(char) * (((size_t)BUFFER_SIZE - j) + 1));
	if (new_node->content == NULL)
		return ;
	k = 0;
	while (last_node->content[j])
		new_node->content[k++] = last_node->content[j++];
	new_node->content[k] = '\0';
	clean(*lst);
	*lst = new_node;
}

char	*get_next_line(int fd)
{
	static t_list	*lst[4096];
	char			*the_line;

	if (fd < 0 || fd >= 4095 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX
		|| read(fd, &the_line, 0) < 0)
	{
		clean(lst[fd]);
		lst[fd] = NULL;
		return (NULL);
	}
	create_list(lst, fd);
	if (!lst[fd])
		return (NULL);
	the_line = making_line(lst[fd]);
	clear_list(&lst[fd]);
	if (the_line[0] == '\0')
	{
		clean(lst[fd]);
		lst[fd] = NULL;
		free(the_line);
		return (NULL);
	}
	return (the_line);
}
