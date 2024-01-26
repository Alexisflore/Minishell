/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfloren <alfloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:41:29 by ladloff           #+#    #+#             */
/*   Updated: 2024/01/25 11:24:41 by alfloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "minishell.h"
#include "libft.h"

int	is_heredoc_pipe(t_token **token_lst)
{
	t_token	*current;

	current = *token_lst;
	while (current)
	{
		if (current->type == T_PIPE && !current->next)
			return (EXIT_FAILURE);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

int	exit_handler(t_token **token_lst)
{
	int	i;

	i = EXIT_FAILURE;
	if ((*token_lst)->type == T_BUILTIN)
		i = EXIT_SUCCESS;
	else if ((*token_lst)->type == T_PIPE)
		printf(ESTR_UNEXP, '|');
	else if ((*token_lst)->type == T_RED_IN
		|| (*token_lst)->type == T_RED_OUT
		|| (*token_lst)->type == T_D_RED_IN
		|| (*token_lst)->type == T_D_RED_OUT)
		i = EXIT_SUCCESS;
	else if ((*token_lst)->type != T_BUILTIN)
		printf(ESTR_OPSTART);
	if (i || is_clean(token_lst) || is_heredoc_pipe(token_lst))
	{
		g_exit_status = 2;
		return (free_token_list(*token_lst), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	is_clean(t_token **token_lst)
{
	char		type;
	t_token		*current;
	const char	*ops[OP] = {"|", "<", "<<", ">", ">>"};

	current = *token_lst;
	while (current && current->next)
	{
		if (current->next->type == T_BUILTIN && !ft_strlen(current->next->data)
			&& current->type > T_BUILTIN)
		{
			type = *ops[current->type - 1];
			printf(ESTR_UNEXP, type);
			return (EXIT_FAILURE);
		}
		current = current->next;
	}
	return (EXIT_SUCCESS);
}

static bool	return_value(bool in_single_quote, bool in_double_quote)
{
	if (in_single_quote)
	{
		printf(ESTR_QUOTE);
		return (EXIT_FAILURE);
	}
	else if (in_double_quote)
	{
		printf(ESTR_DQUOTE);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	is_matched_quotes(const char *line_read)
{
	size_t	i;
	bool	in_single_quote;
	bool	in_double_quote;

	i = -1;
	in_single_quote = false;
	in_double_quote = false;
	while (line_read[++i])
	{
		if (line_read[i] == '\'')
		{
			if (!is_escaped(line_read, i) && !in_double_quote)
				in_single_quote = !in_single_quote;
		}
		else if (line_read[i] == '\"')
		{
			if (!is_escaped(line_read, i) && !in_single_quote)
				in_double_quote = !in_double_quote;
		}
	}
	return (return_value(in_single_quote, in_double_quote));
}
