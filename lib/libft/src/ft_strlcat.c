/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 12:21:17 by ladloff           #+#    #+#             */
/*   Updated: 2023/04/10 10:51:35 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_total;

	if (!dst && dstsize == 0)
		return (0);
	if (dstsize == 0)
		return (ft_strlen(src));
	if (dstsize < ft_strlen(dst))
		return (ft_strlen(src) + dstsize);
	i = -1;
	len_dst = ft_strlen(dst);
	len_total = ft_strlen(src) + len_dst;
	while (src[++i] && len_dst + i < dstsize - 1)
	{
		if (!dst)
			return (0);
		dst[len_dst + i] = src[i];
	}
	if (!dst)
		return (0);
	dst[len_dst + i] = '\0';
	return (len_total);
}
