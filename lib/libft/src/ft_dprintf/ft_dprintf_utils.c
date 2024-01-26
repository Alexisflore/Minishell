/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:23:06 by ladloff           #+#    #+#             */
/*   Updated: 2023/06/29 17:07:37 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_dprintf.h"
#include "libft.h"

void	ft_dprintchar(int fd, char c, ssize_t *len_args)
{
	*len_args += write(fd, &c, 1);
}

void	ft_dprintstr(int fd, char *s, ssize_t *len_args)
{
	if (!s)
		*len_args += write(fd, "(null)", 6);
	else
		*len_args += write(fd, s, ft_strlen(s));
}

void	ft_dprintptr(int fd, unsigned long n, ssize_t *len_args)
{
	if (n > 0)
	{
		ft_dprintstr(fd, "0x", len_args);
		ft_dputhexa(fd, n, HEXA_LOWER_BASE, len_args);
	}
	else
		ft_dprintstr(fd, NULL_POINTER_STR, len_args);
}

void	ft_dprintdec(int fd, int n, ssize_t *len_args)
{
	char	*str;

	str = ft_itoa(n);
	ft_dprintstr(fd, str, len_args);
	free(str);
}

void	ft_dprintudec(int fd, unsigned int n, ssize_t *len_args)
{
	char	*str;

	str = ft_uitoa(n);
	ft_dprintstr(fd, str, len_args);
	free(str);
}
