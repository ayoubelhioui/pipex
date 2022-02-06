/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:30:31 by marvin            #+#    #+#             */
/*   Updated: 2022/01/26 16:30:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "includes/get_next_line.h"
#include "includes/get_next_line_bonus.h"
#include "libft/libft.h"
# define INPUT_FD 0
# define OUTPUT_FD 1
# define FIRST_FILE_ARG 1
# define SECOND_FILE_ARG 4
# define FIRST_COMMAND_ARG 2
# define SECOND_COMMAND_ARG 3
# define FIRST_CHILD_PROC 0
# define SECOND_CHILD_PROC 1

typedef struct s_variables
{
    int     input_fd;
    int     output_fd;
    int     process_id;
}               t_process_vars;
typedef struct argument
{
    char    **splited_command;
    char    *full_path;
}               t_arg;
#endif