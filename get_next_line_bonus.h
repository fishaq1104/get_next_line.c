/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fishaq <fishaq@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/25 16:35:47 by fishaq            #+#    #+#             */
/*   Updated: 2023/08/28 20:06:24 by fishaq           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <limits.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
void				create_list(t_list **lst, int fd);
int					finder(t_list *lst);
t_list				*find_last_node(t_list *lst);
void				append(t_list **lst, char *buff, int fd);
char				*making_line(t_list *lst);
int					find_the_size(t_list *lst);
void				join_the_line(t_list *lst, char *theline);
void				clear_list(t_list **lst);
void				clean(t_list *lst);

#endif