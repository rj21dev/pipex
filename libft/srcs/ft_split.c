/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 12:47:16 by rjada             #+#    #+#             */
/*   Updated: 2022/05/16 19:10:09 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	count_tokens(char const *src, char sep);

static char	*create_token(char const *src, char sep);

static char	**create_token_arr(char **dst, char const *src, char sep);

static void	garbage_collector(char **dst, int i);

char	**ft_split(char const *s, char c)
{
	char	**split;

	if (!s)
		return (NULL);
	split = (char **) malloc(sizeof(char *) * (count_tokens(s, c) + 1));
	if (!split)
		return (NULL);
	return (create_token_arr(split, s, c));
}

static int	count_tokens(char const *src, char sep)
{
	int	i;
	int	total;

	total = 0;
	i = 0;
	while (src[i])
	{
		while (src[i] && src[i] == sep)
			++i;
		if (src[i] && src[i] != sep)
		{
			++total;
			while (src[i] && src[i] != sep)
				++i;
		}
	}
	return (total);
}

static char	*create_token(char const *src, char sep)
{
	char	*token;
	int		i;

	i = 0;
	while (src[i] && src[i] != sep)
		++i;
	token = (char *) malloc(sizeof(char) * (i + 1));
	if (!token)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != sep)
	{
		token[i] = src[i];
		++i;
	}
	token[i] = 0;
	return (token);
}

static char	**create_token_arr(char **dst, char const *src, char sep)
{
	int	i;
	int	token;

	i = 0;
	token = 0;
	while (src[i])
	{
		while (src[i] && src[i] == sep)
			++i;
		if (src[i] && src[i] != sep)
		{
			dst[token] = create_token(src + i, sep);
			if (!dst[token])
			{
				garbage_collector(dst, token);
				return (dst);
			}
			++token;
			while (src[i] && src[i] != sep)
				++i;
		}
	}
	dst[token] = NULL;
	return (dst);
}

static void	garbage_collector(char **dst, int i)
{
	while (i >= 0)
	{
		free(dst[i]);
		i--;
	}
	free(dst);
	dst = NULL;
}
