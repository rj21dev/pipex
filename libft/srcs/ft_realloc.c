/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:33:12 by rjada             #+#    #+#             */
/*   Updated: 2022/02/12 23:35:52 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_realloc(void *src, size_t size)
{
	void	*dst;
	size_t	i;

	dst = malloc(size);
	if (!dst)
		return (NULL);
	i = 0;
	while (src && i < size && ((char *)src)[i])
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	((char *)dst)[i] = '\0';
	free(src);
	return (dst);
}
