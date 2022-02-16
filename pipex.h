/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:30:31 by marvin            #+#    #+#             */
/*   Updated: 2022/02/13 14:41:52 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include "includes/get_next_line.h"
# include "includes/get_next_line_bonus.h"
# include "libft/libft.h"

# define INPUT_FD 0
# define OUTPUT_FD 1
# define ERROR_FD 2
# define FIRST_FILE_ARG 1
# define FULL_ACCESS 0777
# define HIDDEN_FILE "/tmp/.temp_file"
# define HERE_DOC "here_doc"

typedef struct s_variables
{
	int	*p_ids;
	int	(*pipes_array)[2];
	int	input_fd;
	int	output_fd;
	int	command_number;
	int	pipes_number;
	int	first_command_position;
}				t_process_vars;
typedef struct argument
{
	char	**splited_command;
	char	*full_path;
}				t_arg;

void	error_printing(char *str, int standard);
void	close_pipes(int (*pipes_array)[2], int array_length);
void	wait_for_childs(int *p_ids, int commands_number);
void	duplicating(int input, int output);
int		get_input_lines(char *limiter);
#endif
