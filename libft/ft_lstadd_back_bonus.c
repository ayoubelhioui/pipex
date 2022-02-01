/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 16:05:56 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/01/16 18:55:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_stack **lst, t_stack *new)
{
	t_stack	*save;

	if (!lst)
		return ;
	if (!(*lst))
	{
		*lst = new;
		new ->previous = NULL;
		return ;
	}
	else
	{
		save = ft_lstlast(*lst);
		save -> next = new;
		new ->previous = save;
	}
}
