/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:26:41 by ladloff           #+#    #+#             */
/*   Updated: 2023/06/20 16:36:09 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	get_prefix_length(const char *s1, const char *set)
{
	size_t	len_prefix;

	len_prefix = 0;
	while (*s1 && ft_strchr(set, *s1) && ++len_prefix)
		++s1;
	return (len_prefix);
}

static size_t	get_suffix_length(const char *s1, const char *set,
		size_t len_total, size_t len_prefix)
{
	size_t		len_suffix;
	const char	*end;
	const char	*suffix_end;

	len_suffix = 0;
	end = s1 + len_total;
	suffix_end = end;
	while (suffix_end > s1 + len_prefix && ft_strchr(set, *(suffix_end - 1))
		&& ++len_suffix)
		--suffix_end;
	return (len_suffix);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len_total;
	size_t	len_prefix;
	size_t	len_suffix;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	len_total = ft_strlen(s1);
	len_prefix = get_prefix_length(s1, set);
	len_suffix = get_suffix_length(s1, set, len_total, len_prefix);
	str = malloc(len_total - len_prefix - len_suffix + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s1 + len_prefix, len_total - len_prefix - len_suffix);
	str[len_total - len_prefix - len_suffix] = '\0';
	return (str);
}
