/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 20:50:16 by ladloff           #+#    #+#             */
/*   Updated: 2023/06/29 17:10:16 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DPRINTF_H
# define FT_DPRINTF_H

# include <stdarg.h>
# include <sys/types.h>

# ifdef __APPLE__
#  define NULL_POINTER_STR "0x0"
# else
#  define NULL_POINTER_STR "(nil)"
# endif

# define HEXA_LOWER_BASE "0123456789abcdef"
# define HEXA_UPPER_BASE "0123456789ABCDEF"

/* ft_dprintf.c */
void	ft_dformat(int fd, va_list *ap, const char format, ssize_t *len_args);
void	ft_dputhexa(int fd, unsigned long n, const char *base,
			ssize_t *len_args);
int		ft_dprintf(int fd, const char *str,
			...)__attribute__((format(printf, 2, 3)));

/* ft_dprintf_utils.c */
void	ft_dprintchar(int fd, char c, ssize_t *len_args);
void	ft_dprintstr(int fd, char *s, ssize_t *len_args);
void	ft_dprintptr(int fd, unsigned long n, ssize_t *len_args);
void	ft_dprintdec(int fd, int n, ssize_t *len_args);
void	ft_dprintudec(int fd, unsigned int n, ssize_t *len_args);

#endif /* FT_DPRINTF_H */
