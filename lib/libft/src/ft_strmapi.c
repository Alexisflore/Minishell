/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 20:30:48 by ladloff           #+#    #+#             */
/*   Updated: 2023/06/20 16:35:52 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	len_s;
	char	*str;
	char	*p_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	str = malloc((len_s + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	p_s = (char *)s;
	while (s[++i])
		str[i] = f(i, p_s[i]);
	str[i] = '\0';
	return (str);
}
