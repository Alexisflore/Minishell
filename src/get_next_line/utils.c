/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfloren <alfloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:54:08 by myevou            #+#    #+#             */
/*   Updated: 2024/01/29 12:33:12 by alfloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// void	initargs(t_args *args, char **av, char **env, int ac)
// {
// 	args->nbcmds = ac - 3;
// 	args->env = env;
// 	args->cmds = av + 2;
// 	args->in = av[1];
// 	args->out = av[ac - 1];
// 	args->old_pipes = -1;
// 	args->flag = O_TRUNC;
// }

// void	waitprocess(t_args *args)
// {
// 	int	i;

// 	i = 0;
// 	while (i < args->nbcmds)
// 		waitpid(args->pid[i++], NULL, 0);
// }

// void	ft_freetab(char **tab)
// {
// 	int	i;

// 	if (tab)
// 	{
// 		i = -1;
// 		while (tab[++i])
// 			free(tab[i]);
// 		free(tab);
// 	}
// }

// void	here_doc(t_args *args, char *delim)
// {
// 	int		fd;
// 	char	*line;

// 	args->nbcmds -= 1;
// 	args->in = ".tmp";
// 	args->cmds += 1;
// 	args->flag = O_APPEND;
// 	fd = open(".tmp", O_TRUNC | O_CREAT | O_RDWR, 0666);
// 	if (fd < 0)
// 		exit(127);
// 	while (1)
// 	{
// 		line = get_next_line(0, 0);
// 		if (!line || !(ft_strcmp(line, delim)))
// 			break ;
// 		ft_putstr_fd(line, fd);
// 		free(line);
// 	}
// 	get_next_line(0, 1);
// 	free(line);
// 	close(fd);
// }
