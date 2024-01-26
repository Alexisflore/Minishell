/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladloff <ladloff@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 00:06:34 by ladloff           #+#    #+#             */
/*   Updated: 2023/05/27 00:43:06 by ladloff          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

double	ft_atof(const char *str)
{
	int8_t	sign;
	double	factor;
	double	result;

	result = 0.0;
	sign = 1;
	factor = 1.0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -sign;
	while (ft_isdigit(*str))
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (ft_isdigit(*str))
		{
			result = result * 10.0 + (*str++ - '0');
			factor *= 10.0;
		}
	}
	return (sign * result / factor);
}
