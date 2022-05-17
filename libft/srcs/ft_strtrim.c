/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 11:24:31 by rjada             #+#    #+#             */
/*   Updated: 2022/02/12 23:38:22 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	is_set(char str_pos, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		start;
	int		end;
	int		i;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && is_set(s1[start], set))
		++start;
	end = ft_strlen(s1);
	while (end > start && is_set(s1[end - 1], set))
		--end;
	res = (char *) malloc(sizeof(char) * (end - start + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (start < end)
		res[i++] = s1[start++];
	res[i] = 0;
	return (res);
}

static int	is_set(char str_pos, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == str_pos)
			return (TRUE);
		i++;
	}
	return (FALSE);
}
