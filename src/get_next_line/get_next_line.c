/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myevou <myevou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:24:04 by myevou            #+#    #+#             */
/*   Updated: 2024/01/23 17:05:47 by myevou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* taille du content de la liste chaine = size du buffer
	on cree une nouvelle node a chque fois qu'on reutilise read*/

#include "get_next_line.h"

char	*get_next_line(int fd, int state)
{
	static t_list	*stash = NULL;
	char			*line;

	if (state)
		return (free_stash(stash), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
		return (NULL);
	line = NULL;
	read_and_stash(fd, &stash);
	if (!stash)
		return (NULL);
	extract_line(stash, &line);
	if (!line)
		return (NULL);
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

/* 1. read from fd and add to linked list*/
void	read_and_stash(int fd, t_list **stash)
{
	char	*buff;
	int		read_count;

	read_count = 1;
	while (!found_line(*stash) && read_count)
	{
		buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buff)
			return ;
		read_count = (int)read(fd, buff, BUFFER_SIZE);
		if ((!(*stash) && !(read_count)) || read_count == -1)
		{
			free(buff);
			return ;
		}
		buff[read_count] = '\0';
		add_to_stash(stash, buff, read_count);
		free(buff);
	}
}

void	add_to_stash(t_list **stash, char *buff, int read_count)
{
	int		i;
	t_list	*new;
	t_list	*ptr;

	new = malloc(sizeof(t_list));
	if (!new)
		return ;
	new->next = NULL;
	new->content = malloc(sizeof(char) * (read_count + 1));
	if (!(new->content))
		return ;
	i = 0;
	while (buff[i] && i < read_count)
	{
		new->content[i] = buff[i];
		i++;
	}
	new->content[i] = '\0';
	if (!(*stash))
	{
		*stash = new;
		return ;
	}
	ptr = ft_lstlast(*stash);
	ptr->next = new;
}

/* 2. exctract from scratch to line*/
void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (!stash)
		return ;
	generate_line(stash, line);
	if (!(*line))
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

/* 3. clean up stash*/
void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*clean;
	int		i;
	int		j;

	clean = malloc(sizeof(t_list));
	if (!stash || !clean)
		return (free(clean));
	clean->next = NULL;
	last = ft_lstlast(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content && last->content[i] == '\n')
		i++;
	clean->content = malloc(sizeof(char) * ((ft_strlen(last->content) - i)
				+ 1));
	if (!clean->content)
		return ;
	j = 0;
	while (last->content[i])
		clean->content[j++] = last->content[i++];
	clean->content[j] = '\0';
	free_stash(*stash);
	*stash = clean;
}
// #include <stdio.h>
// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("file.txt", O_RDONLY);
// 	int i = 0;
// 	while (++i < 3)
// 	{
// 		line = get_next_line(fd, 0);
// 		printf("%s", line);
// 		if (line == NULL)
// 			break ;
// 		free(line);
// 	}
// 	get_next_line(92110, 1);
// 	return (0);
// }
