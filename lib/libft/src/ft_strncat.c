/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:30:59 by ladloff           #+#    #+#             */
/*   Updated: 2023/06/20 16:26:57 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	char	*str;
	size_t	src_len;

	str = dst;
	dst += ft_strlen(dst);
	src_len = ft_strnlen(src, n);
	dst[src_len] = '\0';
	ft_memcpy(dst, src, src_len);
	return (str);
}
