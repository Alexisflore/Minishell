/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfloren <alfloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 21:20:24 by ladloff           #+#    #+#             */
/*   Updated: 2024/01/29 17:46:41 by alfloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "minishell.h"
#include <fcntl.h>
#include <errno.h>
#include <string.h>

void	print_token(t_token *token)
{
	while (token)
	{
		printf("token: %u , data: %s\n", token->type, token->data);
		token = token->next;
	}
}

static void	execute_command(t_master *master, t_exec *exec, t_env *env_list)
{
	char	**envp;

	envp = env_list_to_array(master, env_list);
	execve(exec->pathname, exec->argv, envp);
	free_double_ptr(envp);
	cleanup_executable(master);
	error_exit(master, "execve (execute_command)");
}

void	prepare_execution(t_master *master, t_token *token)
{
	t_builtin_type	type;

	master->exec = create_arguments(master, token);
	launch_expansion(master, master->exec);
	update_executable_path(master->exec, master->env_list);
	g_exit_status = 0;
	type = exectype(master);
	// type = execute_command_or_builtin(master, master->exec);
	if (type == T_ERROR && g_exit_status == 127)
	{
		cleanup_executable(master);
		return ;
	}
}

void	redirection_files(t_exec *args, int index)
{
	int	fd;

	if (index == 0)
		fd = open(args->in, O_RDONLY);
	if (index == args->nbcmds - 1)
		fd = open(args->out, O_RDWR | args->flag | O_CREAT, 0666);
	if (fd < 0)
	{
		fprintf(stderr, "error: %s\n", strerror(errno));
		exit(1);
	}
	dup2(fd, index == args->nbcmds - 1);
	close(fd);
}

void	redirection_pipes(t_exec *args, int index)
{
	if (index != args->nbcmds - 1)
		dup2(args->fd[1], STDOUT_FILENO);
	if (index != 0)
	{
		dup2(args->old_pipes, STDIN_FILENO);
		close(args->old_pipes);
	}
	close(args->fd[0]);
	close(args->fd[1]);
}

// void	waitprocess(t_master *master)
// {
// 	int	i;

// 	i = 0;
// 	while (i < master->exec->nbcmds)
// 		waitpid(master->exec->pid[i++], NULL, 0);
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

// void	here_doc(t_exec *exec, char *delim)
// {
// 	int		fd;
// 	char	*line;

// 	exec->nbcmds -= 1;
// 	exec->in = ".tmp";
// 	exec->cmds = exec->cmds->next;
// 	exec->flag = O_APPEND;
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

void	*execution(t_master *master)
{
	t_builtin_type	type;

	master->exec = create_arguments(master, master->token_list);
	launch_expansion(master, master->exec);
	update_executable_path(master->exec, master->env_list);
	g_exit_status = 0;
	type = exectype(master);
	// if (master->exec || *(master->exec->argv))
	// 	return (ft_freetab(master->exec->argv), exit(1), NULL);
	if (type == T_BUILTIN)
			execute_command(master, master->exec, master->env_list);
	else if (type == T_ABSPATH)
	{
		if (execve(master->exec->argv[0], master->exec->argv, NULL))
			printf("pipex: %s: command not found\n", master->exec->argv[0]);
	}
	else if (type != T_ERROR)
	{
		if (execute_builtin(master, master->exec, type) == T_ERROR)
			printf("pipex: %s: command not found\n", master->exec->argv[0]);
	}
	else
		printf("pipex: %s: command not found\n", master->exec->argv[0]);
	ft_freetab(master->exec->argv);
	return (NULL);
}

void	proccesses(t_exec *args, t_master *master)
{
	int	i;

	i = 0;
	while (master->token_list)
	{
		if (master->token_list->type == T_PIPE)
		{
			master->token_list = master->token_list->next;
			continue ;
		}
		pipe(args->fd);
		args->pid[i] = fork();
		if (args->pid[i] == 0)
		{
			free(args->pid);
			redirection_pipes(args, i);
			if (i == 0 || i == args->nbcmds - 1)
				redirection_files(args, i);
			execution(master);
		}
		else
		{
			close(args->fd[1]);
			if (i)
				close(args->old_pipes);
			args->old_pipes = args->fd[0];
		}
		master->token_list = master->token_list->next;
		i++;
	}
	close(args->fd[0]);
	// ft_freetab(args->env);
}

// int	main(int ac, char **av, char **env)
// {
// 	static t_exec	args = {0};

// 	initargs(&args, av, env, ac);
// 	get_env(&args, env);
// 	// if (!ft_strcmp(av[1], "here_doc"))
// 	// 	here_doc(&args, ft_strjoin(av[2], "\n"));
// 	args.pid = malloc(sizeof(pid_t) * args.nbcmds);
// 	if (!args.pid)
// 		exit(1);
// 	proccesses(&args);
// 	waitprocess(&args);
// 	free(args.pid);
// }

void	launch_execution(t_master *master)
{
	t_exec		exec;
	int			status;
	// t_token		*token;

	init(master, &exec, &status);
	exec.pid = malloc(sizeof(pid_t) * exec.nbcmds);
	if (!exec.pid)
		ft_error_exit(master, "malloc (launch_execution)", ENOMEM);
	master->exec = &exec;
	proccesses(&exec, master);
	waitprocess(master->exec);
	free(exec.pid);
	// while (token)
	// {
		// prepare_execution(master, token, &exec);

		// if (g_exit_status == 127)
		// 	break ;
		// child_process_execution(master, token, &exec);
		// parent_process_execution(master, &token, &exec);
	// }
	// if (!exec.first_cmd)
	// {
	// 	close(exec.old_pipefd[0]);
	// 	close(exec.old_pipefd[1]);
	// }
	// while ((waitpid(exec.pid, &status, 0)) > 0)
	// 	if (WIFEXITED(status) && g_exit_status != 127)
	// 		g_exit_status = WEXITSTATUS(status);
}
