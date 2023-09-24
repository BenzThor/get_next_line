/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 12:52:24 by tbenz             #+#    #+#             */
/*   Updated: 2023/09/24 12:10:07 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*str_buf;
	struct s_list	*next;
}	t_list;

int		ft_lst_strlen(t_list *lst);
int		ft_check(t_list *list);
void	copy_str(t_list *list, char *str);
t_list	*ft_lstlast(t_list *lst);
void	ft_add_elem(t_list **lst, char *buf, int fd);
char	*get_next_line(int fd);

#endif
