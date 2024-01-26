/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfloren <alfloren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 21:46:41 by ladloff           #+#    #+#             */
/*   Updated: 2024/01/26 14:51:05 by alfloren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int	is_escaped(const char *str, int index)
{
	int	backslashes;

	backslashes = 0;
	while (index > 0 && str[index - 1] == '\\')
	{
		backslashes++;
		index--;
	}
	return (backslashes % 2 != 0);
}

char	*trim_spaces(t_master *master, const char *str, size_t start,
	size_t end)
{
	size_t		i;
	size_t		length;
	char		*trimmed_str;
	const char	ops[4] = "|&<>";

	if (start >= ft_strlen(str) || end >= ft_strlen(str))
		return (NULL);
	i = 0;
	while (i < 4 && ops[i])
	{
		if (ops[i] == str[end])
			end--;
		i++;
	}
	while (ft_isspace(str[start]) && start <= end)
		start++;
	while (ft_isspace(str[end]) && end >= start)
		end--;
	length = end - start + 1;
	trimmed_str = malloc((length + 1) * sizeof(char));
	if (!trimmed_str)
		error_exit(master, "malloc error in trim_spaces");
	ft_strlcpy(trimmed_str, &str[start], length + 1);
	return (trimmed_str);
}

bool	is_in_quotes(const char *line, size_t *i)
{
	while (line[*i] == ' ')
		(*i)++;
	if (line[*i] != '\"' && line[*i] != '\'')
		return (false);
	if (line[*i] == '\"')
	{
		(*i)++;
		while (line[*i] && line[*i] != '\"')
			(*i)++;
	}
	else
	{
		(*i)++;
		while (line[*i] && line[*i] != '\'')
			(*i)++;
	}
	(*i)++;
	return (true);
}
