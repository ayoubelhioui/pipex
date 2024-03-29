/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 12:13:14 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/02/19 14:25:50 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_unused_pipes(int (*pipes_array)[2], int idx_process)
{
	int	i;

	i = 0;
	while (i <= idx_process)
	{
		if (i != idx_process - 1)
			close(pipes_array[i][0]);
		if (i != idx_process)
			close (pipes_array[i][1]);
		i++;
	}
}

void	close_pipes(int (*pipes_array)[2], int array_length)
{
	int	i;

	i = 0;
	while (i < array_length)
	{
		close(pipes_array[i][1]);
		close(pipes_array[i][0]);
		i++;
	}
}

void	wait_for_childs(int *p_ids, int commands_number)
{
	int	i;

	i = 0;
	while (i < commands_number)
		waitpid(p_ids[i++], 0, 0);
}

void	duplicating(int input, int output)
{
	dup2(input, 0);
	dup2(output, 1);
}

int	get_input_lines(char *limiter)
{
	char	*saver;
	char	*last;
	int		hidden_file_fd;

	saver = NULL;
	last = get_next_line(0);
	unlink(HIDDEN_FILE);
	hidden_file_fd = open(HIDDEN_FILE, O_WRONLY | O_CREAT, FULL_ACCESS);
	while (last)
	{
		if (ft_strcmp(last, limiter) == 0)
			break ;
		ft_putstr_fd(last, hidden_file_fd);
		ft_putstr_fd("\n", hidden_file_fd);
		free(last);
		last = get_next_line(0);
	}
	free(last);
	close(hidden_file_fd);
	open(HIDDEN_FILE, O_RDONLY, FULL_ACCESS);
	return (hidden_file_fd);
}
