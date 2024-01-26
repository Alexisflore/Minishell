/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 13:03:22 by ladloff           #+#    #+#             */
/*   Updated: 2023/06/20 16:35:39 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len_total;
	char	*strjoin;

	if (!s1 || !s2)
		return (NULL);
	len_total = ft_strlen(s1) + ft_strlen(s2);
	strjoin = malloc((len_total + 1) * sizeof(char));
	if (!strjoin)
		return (NULL);
	i = -1;
	while (s1[++i])
		strjoin[i] = s1[i];
	j = -1;
	while (i + ++j < len_total)
		strjoin[i + j] = s2[j];
	strjoin[i + j] = '\0';
	return (strjoin);
}
