/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:30:31 by rjada             #+#    #+#             */
/*   Updated: 2022/02/12 23:32:05 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	check_overflow(int res, unsigned long long extreme, int sign);

int	ft_atoi(const char *str)
{
	int					i;
	int					sign;
	int					res;
	unsigned long long	overflow;

	sign = 1;
	res = 0;
	overflow = 0;
	i = 0;
	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		++i;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		overflow = overflow * 10 + str[i] - '0';
		++i;
	}
	return (check_overflow(res, overflow, sign));
}

static int	check_overflow(int res, unsigned long long overflow, int sign)
{
	unsigned long long	min;
	unsigned long long	max;

	min = 9223372036854775808UL;
	max = 9223372036854775807UL;
	if (overflow > max && sign == 1)
		return (-1);
	if (overflow > min && sign == -1)
		return (0);
	return (res * sign);
}
