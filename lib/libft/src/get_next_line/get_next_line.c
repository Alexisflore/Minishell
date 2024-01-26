/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:09:24 by ladloff           #+#    #+#             */
/*   Updated: 2023/05/22 02:04:04 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/select.h>
#include "get_next_line.h"

t_gnl	*free_gnl_node(t_gnl *current)
{
	t_gnl	*next;

	if (!current)
		return (NULL);
	next = current->next;
	free(current->buffer);
	free(current);
	return (next);
}

t_gnl	*create_gnl_node(int fd)
{
	t_gnl	*new_node;

	new_node = ft_calloc(1, sizeof(t_gnl));
	if (!new_node)
		return (NULL);
	new_node->buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
	if (!new_node->buffer)
	{
		free(new_node);
		return (NULL);
	}
	new_node->read_bytes = read(fd, new_node->buffer, BUFFER_SIZE);
	if (new_node->read_bytes < 0)
	{
		free(new_node->buffer);
		free(new_node);
		return (NULL);
	}
	return (new_node);
}

static char	*extract_line(t_gnl **list, size_t line_size)
{
	size_t	i;
	char	*line;
	char	*p_line;

	if (!list || !(*list))
		return (NULL);
	line = ft_calloc((line_size + 1), sizeof(char));
	if (!line)
		return (NULL);
	p_line = line;
	i = (*list)->buffer_index;
	while (line_size--)
	{
		*line++ = (*list)->buffer[i++];
		if ((size_t)(*list)->read_bytes == i)
		{
			*list = free_gnl_node(*list);
			i = 0;
		}
	}
	*line = '\0';
	if (*list)
		(*list)->buffer_index = i;
	return (p_line);
}

static size_t	get_line_size(t_gnl *list, int fd)
{
	size_t	i;
	size_t	line_size;
	t_gnl	*new_node;

	if (!list || !list->buffer)
		return (0);
	line_size = 1;
	i = list->buffer_index;
	while (list->buffer[i] && list->buffer[i++] != '\n')
	{
		if ((size_t)list->read_bytes == i)
		{
			new_node = create_gnl_node(fd);
			if (!new_node)
				return (0);
			new_node->next = list->next;
			list->next = new_node;
			list = new_node;
			i = 0;
		}
		line_size++;
	}
	return (line_size);
}

char	*get_next_line(int fd)
{
	static t_gnl	*list;
	char			*line;
	size_t			line_size;

	if (fd < 0 || fd >= FD_SETSIZE)
		return (NULL);
	if (!list)
		list = create_gnl_node(fd);
	if (!list)
		return (NULL);
	if (!list->read_bytes)
	{
		list = free_gnl_node(list);
		return (NULL);
	}
	line_size = get_line_size(list, fd);
	if (!line_size)
		return (NULL);
	line = extract_line(&list, line_size);
	return (line);
}
