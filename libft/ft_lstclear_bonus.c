/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:37:12 by ael-hiou          #+#    #+#             */
/*   Updated: 2021/11/15 21:28:41 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;
	t_list	*saver;

	temp = *lst;
	while (temp != NULL)
	{
		saver = temp ->next;
		ft_lstdelone(temp, del);
		temp = saver;
	}
	*lst = NULL;
}
