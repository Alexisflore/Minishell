/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 20:23:49 by ladloff           #+#    #+#             */
/*   Updated: 2023/06/20 16:36:37 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_uitoa(unsigned int n)
{
	unsigned int	value;
	char			*buffer;
	int				buffer_size;

	if (n == 0)
	{
		buffer = malloc(2 * sizeof(char));
		if (!buffer)
			return (NULL);
		return ((buffer[0] = '0'), (buffer[1] = '\0'), buffer);
	}
	value = n;
	buffer_size = 0;
	while (value > 0 && ++buffer_size)
		value /= 10;
	buffer = malloc((buffer_size + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[buffer_size] = '\0';
	while (--buffer_size >= 0)
	{
		buffer[buffer_size] = (char)('0' + (n % 10));
		n /= 10;
	}
	return (buffer);
}
