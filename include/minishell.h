/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfloren <alfloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:59:04 by  ladloff          #+#    #+#             */
/*   Updated: 2024/01/29 14:46:31 by alfloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <sys/types.h>
#include <sys/wait.h>
#include "libft.h"

# define OP 5
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

t_list	*ft_lstlast(t_list *stash);
void	extract_line(t_list *stash, char **line);
size_t	ft_strlen(const char *str);
int		found_line(t_list *stash);
void	generate_line(t_list *stash, char **line);
void	add_to_stash(t_list **stash, char *buff, int read_count);
void	read_and_stash(int fd, t_list **stash);
void	clean_stash(t_list **stash);
void	free_stash(t_list *stash);
char	*get_next_line(int fd, int state);

# define ESTR_QUOTE "minishell: syntax error: unmatched quote\n"
# define ESTR_DQUOTE "minishell: syntax error: unmatched double quote\n"
# define ESTR_UNEXP "minishell: syntax error: unexpected token '%c'\n"
# define ESTR_OPSTART "minishell: syntax error near unexpected token 'newline'\n"
# define NUM_ARG_ERR "minishell: exit: %s: numeric argument required\n"
# define TOO_MANY_ARGS_ERR "minishell: exit: too many arguments\n"
# define DEFAULT_PATH_1 "/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin"
# define DEFAULT_PATH_2 ":/opt/homebrew/bin"
# define SHLVL "SHLVL"

typedef enum e_builtin_type
{
	T_ERROR = 1,
	T_CD,
	T_ECHO,
	T_ENV,
	T_EXIT,
	T_PWD,
	T_UNSET,
	T_EXPORT,
	T_BUILTIN,
	T_ABSPATH,
	T_PIPE,
	T_RED_IN,
	T_D_RED_IN,
	T_RED_OUT,
	T_D_RED_OUT,
}	t_builtin_type;

// typedef enum e_token_type
// {
// 	T_BUILTIN,
// }	t_builtin_type;

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*last;
}	t_env;

typedef struct s_token
{
	t_builtin_type	type;
	char			*data;
	char			**split_args;
	struct s_token	*next;
	struct s_token	*last;
}	t_token;

typedef struct s_exec
{
	int			argc;
	char		**argv;
	char		*pathname;
	t_token		*cmds;
	pid_t		*pid;
	int			fd[2];
	int			old_pipefd[2];
	bool		first_cmd;
	bool		simple_quotes;
	int			nbcmds;
	int			stdin_fd;
	int			stdout_fd;
	char		*in;
	char		*out;
	int			old_pipes;
	int			flag;
}	t_exec;

typedef struct s_master
{
	t_env	*env_list;
	char	*line_read;
	t_token	*token_list;
	t_exec	*exec;
}	t_master;


extern int	g_exit_status;

/* builtin_utils.c */

void			print_data_builtins(t_exec	*current);
void			handle_error_cases(t_exec *exec);

/* builtin.c */

t_builtin_type	execute_command_or_builtin(t_master *master, t_exec *exec);
bool			find_path_name(t_master *master, t_exec *exec);
t_builtin_type	inspect_token(char *arg);
/* execution_mem.c */

void		free_double_ptr(char **str);
t_exec		*create_arguments(t_master *master, t_token *token);

/* execution_utils.c */

char			**env_list_to_array(t_master *master, t_env *env_list);
void			init(t_master *mast, t_exec *e, int *s);
t_builtin_type	exectype(t_master *master);
/* execution.c */

void			launch_execution(t_master *master);
int	      execute_builtin(t_master *master, t_exec *exec, t_builtin_type type);

/* expansion_utils.c */

char			*get_env_value(t_master *master, t_env *env, char *name);
char			*extract_expansion_name(t_master *master, char *str);

/* expansion.c */

void			launch_expansion(t_master *master, t_exec *exec);

/* split_args.c */

void			split_args(t_master *master, char *s, char **argv,
					bool *simple_quotes);

/* cleanup.c */

void			cleanup_executable(t_master *master);
void			cleanup_before_exit(t_master *master);

/* exit.c */

void			error_exit(t_master *master, char *error_str);
void			ft_error_exit(t_master *master, char *error_str, int errnum);
void			handle_eof(t_master *master);

/* lexer.c */

int				launch_lexer(t_master *master, char *line_read,
					t_token **token_list);

/* lexer_utils.c */

int				is_heredoc_pipe(t_token **token_lst);
int				exit_handler(t_token **token_lst);
int				is_clean(t_token **token_lst);
int				is_matched_quotes(const char *line_read);

/* lexer_utils2.c */
int				is_escaped(const char *str, int index);
char			*trim_spaces(t_master *master, const char *str, size_t start,
		size_t end);
bool			is_in_quotes(const char *line, size_t *i);

/* lexer_mem.c */

void			free_token_list(t_token *token_list);
void			create_token_node(t_master *master, t_builtin_type type,
					char *data, t_token **token_list);

/* signals.c */

void			set_sigaction(void);

/* env_utils.c */

void			update_executable_path(t_exec *exec, t_env *env_list);
void			print_environement_list(t_env *env_list);
void			print_environement_var(t_env *env_list, char *name);
char			*update_shlvl(t_master *master, char *value, char *name);

/* env.c */

void			free_environment_list(t_env *env);
void			manage_environment(t_master *master, t_env **env_list);

int				ft_cd(int argc, char **argv, t_master *master);
int				ft_echo(int argc, char **argv, t_master *master);
void			ft_env(t_master *master);
void			ft_exit(t_master *master, int argc, char **argv);
int				ft_export(int argc, char **argv, t_master *master);
int				ft_pwd(void);
int				ft_unset(int argc, char **argv, t_master *master);

int 			launch_redirection(t_master *master, t_token *tmp);

void			ft_freetab(char **tab);
void			waitprocess(t_exec *exec);


#endif /* MINISHELL_H */
