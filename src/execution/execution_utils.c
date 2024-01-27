/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfloren <alfloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 20:33:30 by ladloff           #+#    #+#             */
/*   Updated: 2024/01/26 16:03:30 by alfloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"
#include "libft.h"
#include <stdio.h>
#include <fcntl.h>

static size_t	get_env_list_size(t_env *env_list)
{
	size_t	size;

	size = 0;
	while (env_list)
	{
		size++;
		env_list = env_list->next;
	}
	return (size);
}

char	**env_list_to_array(t_master *master, t_env *env_list)
{
	size_t	i;
	char	*tmp;
	char	**array;

	if (!env_list)
		return (NULL);
	array = malloc((get_env_list_size(env_list) + 1) * sizeof(char *));
	if (!array)
		return (cleanup_executable(master),
			error_exit(master, "malloc (env_list_to_array)"),
			NULL);
	i = 0;
	while (env_list)
	{
		tmp = ft_strjoin(env_list->name, "=");
		if (!tmp)
			error_exit(master, "Failed to allocate memory for tmp");
		array[i] = ft_strjoin(tmp, env_list->value);
		free(tmp);
		if (!array[i])
			error_exit(master, "Failed to allocate memory for array[i]");
		env_list = env_list->next;
		i++;
	}
	return (array[i] = NULL, array);
}

void	init(t_master *master, t_exec *exec, int *status, t_token **token)
{
	*status = 0;
	exec->pid = -1;
	exec->first_cmd = true;
	// exec->pipefd[0] = -1;
	// exec->pipefd[1] = -1;
	exec->argc = 0;
	exec->cmds = master->token_list;
	// *token = master->token_list;
	exec->in = "/dev/stdin";
	exec->out = "/dev/stdout";
	exec->old_pipes = -1;
	exec->flag = O_TRUNC;
	exec->stdout_fd= dup(STDOUT_FILENO);
	exec->stdin_fd = dup(STDIN_FILENO);
	exec->nbcmds = nbr_command(master);
}
// void	initexec(t_master master, t_exec *exec, int *status, t_token **token)
// {
// 	exec->nbcmds = nbr
// 	exec->env = env;

// 	exec->in = av[1];
// 	exec->out = av[ac - 1];
// 	exec->old_pipes = -1;
// 	exec->flag = O_TRUNC;
// }

int	nbr_command(t_master *master)
{
	t_token	*token;
	int		nb;

	nb = 0;
	token = master->token_list;
	while (token)
	{
		if (token->type == T_PIPE)
			nb++;
		token = token->next;
	}
	return (nb + 1);
}

void	waitprocess(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->nbcmds)
		waitpid(exec->pid[i++], NULL, 0);
}

void	ft_freetab(char **tab)
{
	int	i;

	if (tab)
	{
		i = -1;
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}
}

void	here_doc(t_exec *exec, char *delim)
{
	int		fd;
	char	*line;

	exec->nbcmds -= 1;
	exec->in = ".tmp";
	exec->cmds = exec->cmds->next;
	exec->flag = O_APPEND;
	fd = open(".tmp", O_TRUNC | O_CREAT | O_RDWR, 0666);
	if (fd < 0)
		exit(127);
	while (1)
	{
		line = get_next_line(0, 0);
		if (!line || !(ft_strcmp(line, delim)))
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	get_next_line(0, 1);
	free(line);
	close(fd);
}

t_builtin_type  exectype(t_master *master)
{
  t_builtin_type type;

  if (master->exec->argc == 0)
    return (T_ERROR);
  type = inspect_token(master->exec->argv[0]);
  if (type == T_ERROR || !ft_strcmp(master->exec->argv[0], ".")
		|| !ft_strcmp(master->exec->argv[0], ".."))
    {
      handle_error_cases(master->exec);
      return (T_ERROR);
    }
  if (type == T_BUILTIN)
  {
    if (master->exec->argv[0][0] == '/')
      return (T_ABSPATH);
    else
    {
      if (find_path_name(master, master->exec) == false)
        return (T_ERROR);
    }
  }
  // else if (type == T_ERROR)
  //   return (T_ERROR);
  return (type);
}
