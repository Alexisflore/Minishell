/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnlen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:24:19 by ladloff           #+#    #+#             */
/*   Updated: 2023/06/20 16:25:18 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strnlen(const char *str, size_t maxlen)
{
	const char	*ptr = str;
	size_t		len;

	if (!maxlen)
		return (0);
	len = 0;
	while (len < maxlen && *ptr)
	{
		ptr++;
		len++;
	}
	return (len);
}
