/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:33:35 by rjada             #+#    #+#             */
/*   Updated: 2022/02/12 23:38:46 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static size_t	count_numlen(unsigned long int nbr, size_t baselen);

static int		is_base_valid(char *base);

char	*ft_ultoa(unsigned long int nbr, char *base)
{
	char	*num;
	size_t	numlen;
	size_t	baselen;

	if (!is_base_valid(base))
		return (NULL);
	baselen = ft_strlen(base);
	numlen = count_numlen(nbr, baselen);
	num = (char *) malloc(sizeof(char) * numlen + (!nbr) + 1);
	if (!num)
		return (NULL);
	num[numlen + (!nbr)] = 0;
	if (!nbr)
		num[0] = '0';
	while (nbr)
	{
		num[--numlen] = base[nbr % baselen];
		nbr /= baselen;
	}
	return (num);
}

static size_t	count_numlen(unsigned long int nbr, size_t baselen)
{
	size_t	nbr_len;

	nbr_len = 0;
	while (nbr)
	{
		nbr /= baselen;
		++nbr_len;
	}
	return (nbr_len);
}

static int	is_base_valid(char *base)
{
	int		i;
	int		j;
	int		len;

	len = ft_strlen(base);
	if (!base || len < 2 || len > 16)
		return (0);
	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (0);
		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (FALSE);
			++j;
		}
		++i;
	}
	return (TRUE);
}
