/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 20:04:50 by ladloff           #+#    #+#             */
/*   Updated: 2022/10/29 12:29:51 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*p_dst;
	const unsigned char	*p_src;

	if (!dst && !src)
		return (NULL);
	p_dst = dst;
	p_src = src;
	if ((unsigned char *)dst > p_src)
		while (len--)
			p_dst[len] = p_src[len];
	else
		while (len--)
			*p_dst++ = *p_src++;
	return (dst);
}
