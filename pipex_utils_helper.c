/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 11:44:28 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/02/22 11:53:53 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_quotes_replacing(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (command[i] == '\'')
		{
			replacing(command + i + 1, ' ', -1);
			break ;
		}
		i++;
	}
	return (command);
}

void	replacing(char *s, char to_be_replaced, char replacer)
{
	int	i;

	i = 0;
	while (s[i] != '\'')
	{
		if (s[i] == to_be_replaced)
			s[i] = replacer;
		i++;
	}
}
