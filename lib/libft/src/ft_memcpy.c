/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 17:42:54 by ladloff           #+#    #+#             */
/*   Updated: 2022/10/29 12:29:56 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*p_src;
	unsigned char		*p_dst;

	if (!dst && !src)
		return (NULL);
	p_src = src;
	p_dst = dst;
	while (n--)
		*p_dst++ = *p_src++;
	return (dst);
}
