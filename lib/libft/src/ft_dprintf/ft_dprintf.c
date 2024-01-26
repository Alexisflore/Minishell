/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:54:11 by ladloff           #+#    #+#             */
/*   Updated: 2023/06/29 17:09:09 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_dprintf.h"

void	ft_dformat(int fd, va_list *ap, const char format, ssize_t *len_args)
{
	if (format == 'c')
		ft_dprintchar(fd, va_arg(*ap, unsigned int), len_args);
	if (format == 's')
		ft_dprintstr(fd, va_arg(*ap, char *), len_args);
	if (format == 'p')
		ft_dprintptr(fd, va_arg(*ap, unsigned long), len_args);
	if (format == 'd' || format == 'i')
		ft_dprintdec(fd, va_arg(*ap, int), len_args);
	if (format == 'u')
		ft_dprintudec(fd, va_arg(*ap, unsigned int), len_args);
	if (format == 'x')
		ft_dputhexa(fd, va_arg(*ap, unsigned int), HEXA_LOWER_BASE, len_args);
	if (format == 'X')
		ft_dputhexa(fd, va_arg(*ap, unsigned int), HEXA_UPPER_BASE, len_args);
	if (format == '%')
		ft_dprintchar(fd, '%', len_args);
}

void	ft_dputhexa(int fd, unsigned long n, const char *base,
ssize_t *len_args)
{
	int		i;
	char	hex[16];

	i = 0;
	while (n >= 16)
	{
		hex[i++] = base[n % 16];
		n /= 16;
	}
	hex[i] = base[n];
	while (i >= 0)
		ft_dprintchar(fd, hex[i--], len_args);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int		i;
	va_list	ap;
	ssize_t	len_args;

	i = -1;
	len_args = 0;
	va_start(ap, format);
	while (format[++i])
	{
		if (format[i] == '%')
			ft_dformat(fd, &ap, format[++i], &len_args);
		else
			ft_dprintchar(fd, format[i], &len_args);
	}
	return ((int)len_args);
}
