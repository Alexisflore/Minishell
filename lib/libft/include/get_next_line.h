/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 16:07:22 by ladloff           #+#    #+#             */
/*   Updated: 2023/05/22 01:54:43 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct s_gnl
{
	size_t			buffer_index;
	char			*buffer;
	ssize_t			read_bytes;
	struct s_gnl	*next;
}	t_gnl;

/* get_next_line.c */
char	*get_next_line(int fd);

#endif /* GET_NEXT_LINE_H */
