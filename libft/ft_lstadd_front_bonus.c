/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:29:35 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/01/16 19:09:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_stack **lst, t_stack *new)
{
	t_stack	*temp;

	if (!lst)
		return ;
	if (!*lst)
	{	
		*lst = new;
		new ->next = NULL;
		new->previous = NULL;
	}
	else
	{
		temp = *lst;
		temp->previous = new;
		*lst = new;
		new -> next = temp;
	}
}
