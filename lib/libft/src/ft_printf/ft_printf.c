/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:54:11 by ladloff           #+#    #+#             */
/*   Updated: 2023/05/21 23:40:00 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_format(va_list *ap, const char format, ssize_t *len_args)
{
	if (format == 'c')
		ft_printchar(va_arg(*ap, unsigned int), len_args);
	if (format == 's')
		ft_printstr(va_arg(*ap, char *), len_args);
	if (format == 'p')
		ft_printptr(va_arg(*ap, unsigned long), len_args);
	if (format == 'd' || format == 'i')
		ft_printdec(va_arg(*ap, int), len_args);
	if (format == 'u')
		ft_printudec(va_arg(*ap, unsigned int), len_args);
	if (format == 'x')
		ft_puthexa(va_arg(*ap, unsigned int), HEXA_LOWER_BASE, len_args);
	if (format == 'X')
		ft_puthexa(va_arg(*ap, unsigned int), HEXA_UPPER_BASE, len_args);
	if (format == '%')
		ft_printchar('%', len_args);
}

void	ft_puthexa(unsigned long n, const char *base, ssize_t *len_args)
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
		ft_printchar(hex[i--], len_args);
}

int	ft_printf(const char *format, ...)
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
			ft_format(&ap, format[++i], &len_args);
		else
			ft_printchar(format[i], &len_args);
	}
	return ((int)len_args);
}
