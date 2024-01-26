/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:50:16 by ladloff           #+#    #+#             */
/*   Updated: 2023/05/21 23:40:15 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <sys/types.h>

# ifdef __APPLE__
#  define NULL_POINTER_STR "0x0"
# else
#  define NULL_POINTER_STR "(nil)"
# endif

# define HEXA_LOWER_BASE "0123456789abcdef"
# define HEXA_UPPER_BASE "0123456789ABCDEF"

/* ft_printf.c */
void	ft_format(va_list *ap, const char format, ssize_t *len_args);
void	ft_puthexa(unsigned long n, const char *base, ssize_t *len_args);
int		ft_printf(const char *str, ...)__attribute__((format(printf, 1, 2)));

/* ft_printf_utils.c */
void	ft_printchar(char c, ssize_t *len_args);
void	ft_printstr(char *s, ssize_t *len_args);
void	ft_printptr(unsigned long n, ssize_t *len_args);
void	ft_printdec(int n, ssize_t *len_args);
void	ft_printudec(unsigned int n, ssize_t *len_args);

#endif /* FT_PRINTF_H */
