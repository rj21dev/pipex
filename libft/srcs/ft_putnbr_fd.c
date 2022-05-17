/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 15:16:23 by rjada             #+#    #+#             */
/*   Updated: 2022/02/12 23:35:38 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n == MIN_OF_INT)
	{
		write(fd, "-2147483648", sizeof(char) * 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", sizeof(char));
		n *= -1;
	}
	if (n < 10)
	{
		c = n + '0';
		write(fd, &c, sizeof(char));
	}
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
