/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbenz <tbenz@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 13:12:55 by tbenz             #+#    #+#             */
/*   Updated: 2023/09/24 12:02:48 by tbenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_clean(t_list **lst, char *buf, t_list *return_node)
{
	t_list	*temp;

	if (*lst == NULL)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		free ((*lst)->str_buf);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
	if (return_node->str_buf[0])
		*lst = return_node;
	else
	{
		free (buf);
		free(return_node);
	}
}

void	ft_create_last_node_and_free(t_list **lst)
{
	char	*buf;
	t_list	*return_node;
	t_list	*last_node;
	int		k;
	int		i;

	buf = malloc(BUFFER_SIZE + 1);
	return_node = malloc(sizeof(t_list));
	if (!buf || !return_node)
		return ;
	last_node = ft_lstlast(*lst);
	i = 0;
	k = 0;
	while (last_node->str_buf[i] && last_node->str_buf[i] != '\n')
		i++;
	while (last_node->str_buf[i] && last_node->str_buf[++i])
		buf[k++] = last_node->str_buf[i];
	buf[k] = '\0';
	return_node->str_buf = buf;
	return_node->next = NULL;
	ft_clean(lst, buf, return_node);
}

char	*ft_create_new_line(t_list *lst)
{
	char	*str_create;
	int		total_len;

	if (!lst)
		return (NULL);
	total_len = ft_lst_strlen(lst);
	str_create = malloc((total_len + 1) * sizeof(char));
	if (!str_create)
		return (NULL);
	copy_str(lst, str_create);
	return (str_create);
}

int	function_to_get_the_line_up_to_new_line(int fd, t_list	**lst)
{
	int		bytes_read;
	char	*buf;

	while (!ft_check(*lst))
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (0);
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1 || !bytes_read)
		{
			free(buf);
			if (bytes_read == -1)
				return (-1);
			else
				return (0);
		}
		buf[bytes_read] = '\0';
		ft_add_elem(lst, buf);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	t_list			*temp;
	static t_list	*lst = NULL;
	char			*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (function_to_get_the_line_up_to_new_line(fd, &lst) == -1)
	{
		while (lst)
		{
			temp = (lst)->next;
			free ((lst)->str_buf);
			free(lst);
			lst = temp;
		}
	}
	if (!lst)
		return (NULL);
	next_line = ft_create_new_line(lst);
	ft_create_last_node_and_free(&lst);
	return (next_line);
}
/*
#include <stdio.h>
int	main(void)
{
	int		fd;
	char	*line;
	int		lines;

	lines = 0;

	fd = open("example_file.txt", O_RDONLY);

	while (lines++ < 3)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	close(fd);
	fd = open("example_file.txt", O_RDONLY);
	lines = 0;
	printf("XXX");
	while (lines++ < 4)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	close(fd);

}
*/
