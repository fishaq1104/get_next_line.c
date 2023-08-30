/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fishaq <fishaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 20:41:58 by fishaq            #+#    #+#             */
/*   Updated: 2023/08/30 19:13:49 by fishaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	char	*new;
	int		i;

	i = 1;
	while (!finder(*lst))
	{
		new = (char *)malloc((size_t)BUFFER_SIZE + 1);
		if (!new)
			return ;
		i = read(fd, new, BUFFER_SIZE);
		if (!i)
		{
			free(new);
			return ;
		}
		new[i] = '\0';
		append(lst, new);
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
	static t_list	*lst = NULL;
	char			*the_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX || read(fd,
			&the_line, 0) < 0)
	{
		clean(lst);
		lst = NULL;
		return (NULL);
	}
	create_list(&lst, fd);
	if (lst == NULL)
		return (NULL);
	the_line = making_line(lst);
	clear_list(&lst);
	if (the_line[0] == '\0')
	{
		clean(lst);
		lst = NULL;
		free(the_line);
		return (NULL);
	}
	return (the_line);
}
// int	main(void)
// {
// 	int fd;
// 	char *line;
// 	fd = open("file1.txt", O_RDONLY);
// 	if (fd < 0)
// 	{
// 		return (1);
// 	}
// 	while ((line = get_next_line(fd)) != NULL)
// 	{
// 		printf("Line: %s", line);
// 		free(line);
// 	}
// 	close(fd);

// 	return (0);
// }
