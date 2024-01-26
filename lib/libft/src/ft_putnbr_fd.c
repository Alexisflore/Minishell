/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:06:46 by ladloff           #+#    #+#             */
/*   Updated: 2023/05/22 02:35:47 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		nb = -nb;
		ft_putchar_fd('-', fd);
	}
	if (nb < 10)
		ft_putchar_fd((char)(nb + '0'), fd);
	else
	{
		ft_putnbr_fd((int)(nb / 10), fd);
		ft_putchar_fd((char)(nb % 10 + '0'), fd);
	}
}
