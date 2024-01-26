/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:23:06 by ladloff           #+#    #+#             */
/*   Updated: 2023/06/20 16:36:47 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

void	ft_printchar(char c, ssize_t *len_args)
{
	*len_args += write(STDOUT_FILENO, &c, 1);
}

void	ft_printstr(char *s, ssize_t *len_args)
{
	if (!s)
		*len_args += write(STDOUT_FILENO, "(null)", 6);
	else
		*len_args += write(STDOUT_FILENO, s, ft_strlen(s));
}

void	ft_printptr(unsigned long n, ssize_t *len_args)
{
	if (n > 0)
	{
		ft_printstr("0x", len_args);
		ft_puthexa(n, HEXA_LOWER_BASE, len_args);
	}
	else
		ft_printstr(NULL_POINTER_STR, len_args);
}

void	ft_printdec(int n, ssize_t *len_args)
{
	char	*str;

	str = ft_itoa(n);
	ft_printstr(str, len_args);
	free(str);
}

void	ft_printudec(unsigned int n, ssize_t *len_args)
{
	char	*str;

	str = ft_uitoa(n);
	ft_printstr(str, len_args);
	free(str);
}
