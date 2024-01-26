/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfloren <alfloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 10:41:22 by ladloff           #+#    #+#             */
/*   Updated: 2024/01/26 14:55:35 by alfloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

t_builtin_type	isnot_builtins(char c, const char *line_read, size_t *i)
{
	size_t					j;
	const char				*ops[OP] = {"|", "<", "<<", ">", ">>"};
	const t_builtin_type	types[OP] = {T_PIPE, T_RED_IN, T_D_RED_IN,
		T_RED_OUT, T_D_RED_OUT};
	t_builtin_type			token_type;

	j = 0;
	token_type = T_BUILTIN;
	while (j < OP)
	{
		if (c == *ops[j])
		{
			token_type = types[j];
			if (line_read[*i + 1] == c)
			{
				token_type = types[j + 1];
				(*i)++;
			}
			(*i)++;
			break ;
		}
		j++;
	}
	return (token_type);
}

t_builtin_type	is_builtin(const char *line_read, size_t *i)
{
	while (line_read[*i] != '\0'
		&& line_read[*i] != '|'
		&& line_read[*i] != '<'
		&& line_read[*i] != '>')
		(*i)++;
	return (T_BUILTIN);
}

t_builtin_type	check_type(char c, const char *line_read, size_t *i)
{
	t_builtin_type		token_type;

	token_type = isnot_builtins(c, line_read, i);
	if (token_type != T_BUILTIN)
		return (token_type);
	return (is_builtin(line_read, i));
}

static int	manage_redirection(const char *line_read, size_t *i)
{
	if (is_in_quotes(line_read, i))
		return (T_BUILTIN);
	if (line_read[*i] == '\0')
	{
		printf(ESTR_OPSTART);
		return (EXIT_FAILURE);
	}
	while (line_read[*i] == ' ' && line_read[*i])
		(*i)++;
	while (line_read[*i] != ' '
		&& line_read[*i] != '|'
		&& line_read[*i] != '<'
		&& line_read[*i] != '>'
		&& line_read[*i])
		(*i)++;
	return (T_BUILTIN);
}

int	launch_lexer(t_master *master, char *line_read, t_token **token_lst)
{
	size_t			i;
	size_t			j;
	char			*data;
	t_builtin_type	type;

	i = 0;
	type = T_BUILTIN;
	if (is_matched_quotes(line_read) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (line_read[i])
	{
		while (line_read[i] == ' ' && line_read[i])
			i++;
		j = i;
		type = check_type(line_read[i], line_read, &i);
		if (type != T_BUILTIN && type != T_PIPE)
		{
			j = i;
			if ((manage_redirection(line_read, &i) == EXIT_FAILURE))
				return (EXIT_FAILURE);
		}
		data = trim_spaces(master, line_read, j, i - 1);
		create_token_node(master, type, data, token_lst);
	}
	return (exit_handler(token_lst));
}


// static void print_tokens(t_token *token)
// {
// 	while (token)
// 	{
// 		printf("type: %d, data: %s\n", token->type, token->data);
// 		token = token->next;
// 	}
// }
// static t_builtin_type	check_token_type(char c,
	// const char *line_read, size_t *j)
// {
// 	size_t				i;
// 	t_token_type		token_type;
// 	const char			*ops[OP] = {"|", "<", "<<", ">", ">>"};
// 	const t_token_type	types[OP] = {T_PIPE, T_RED_IN, T_D_RED_IN, T_RED_OUT,
// 		T_D_RED_OUT};

// 	i = 0;
// 	token_type = T_BUILTIN;
// 	while (i < OP)
// 	{
// 		if (is_in_quotes(line_read, *j))
// 			return (T_BUILTIN);
// 		if (c != *ops[i])
// 		{
// 			i++;
// 			continue ;
// 		}
// 		token_type = types[i];
// 		if (line_read[*j + 1] == c)
// 		{
// 			token_type = types[i + 1];
// 			(*j)++;
// 		}
// 		(*j)++;
// 		break ;
// 	}
// 	return (token_type);
// }

//
// static void print_tokens(t_token *token)
// {
// 	while (token)
// 	{
// 		printf("type: %d, data: %s\n", token->type, token->data);
// 		token = token->next;
// 	}
// }

// static int	manage_token(t_master *master, const char *line_read,
// 	t_token **token_lst)
// {
// 	size_t			i;
// 	size_t			j;
// 	char			*data;
// 	t_token_type	type;

// 	i = 0;
// 	type = check_token_type(line_read[i], line_read, &i);
// 	if (start_operator(type) == EXIT_FAILURE)
// 		return (EXIT_FAILURE);
// 	if (type != T_BUILTIN)
// 		manage_redirection(master, line_read[i], line_read, &i, token_lst);
// 	while (line_read[i])
// 	{
// 		j = i;
// 		type = check_token_type(line_read[i], line_read, &i);
// 		if (type)
// 		while (line_read[i] && type == T_BUILTIN)
// 			type = check_token_type(line_read[++i], line_read, &i);
// 		data = trim_spaces(master, line_read, j, i - 1);
// 		create_token_node(master, T_BUILTIN, data, token_lst);
// 		if (type != T_BUILTIN)
// 		{
// 			create_token_node(master, type, NULL, token_lst);
// 			if (line_read[i] == ' ')
// 				i++;
// 		}
// 	}
// 	print_tokens(*token_lst);
// 	return (EXIT_SUCCESS);
// }

// static bool	is_quotes(const char *line_read, size_t j)
// {
// 	size_t	i;
// 	bool	inside_single_quotes;
// 	bool	inside_double_quotes;

// 	i = 0;
// 	inside_double_quotes = false;
// 	inside_single_quotes = false;
// 	while (line_read[i] && i < j)
// 	{
// 		if (line_read[i] == '\'' && !is_escaped(line_read, i)
// 			&& !inside_double_quotes)
// 			inside_single_quotes = !inside_single_quotes;
// 		else if (line_read[i] == '\"' && !is_escaped(line_read, i)
// 			&& !inside_single_quotes)
// 			inside_double_quotes = !inside_double_quotes;
// 		i++;
// 	}
// 	return (inside_single_quotes || inside_double_quotes);
// }
