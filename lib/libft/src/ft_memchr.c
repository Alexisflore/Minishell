/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 22:22:44 by ladloff           #+#    #+#             */
/*   Updated: 2022/10/27 22:55:32 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p_s;

	if (n != 0)
	{
		p_s = s;
		while (n--)
			if (*p_s++ == (unsigned char)c)
				return ((void *)(p_s - 1));
	}
	return (NULL);
}
