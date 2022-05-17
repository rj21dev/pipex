/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 22:12:02 by rjada             #+#    #+#             */
/*   Updated: 2022/02/12 23:34:31 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstprint(t_list *lst)
{
	if (!lst)
		ft_putendl_fd("NULL or empty.", STDOUT);
	while (lst)
	{
		ft_putendl_fd(lst->content, STDOUT);
		lst = lst->next;
	}
}
