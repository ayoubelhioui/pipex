/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:07:39 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/02/09 12:17:53 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_putstr(char *str)
{
    int i;

    i = 0;
    while (str[i])
        write(1, &str[i++], 1);
}

void    error_printing()
{
    ft_putstr("Error\n");
    exit(1);
}

char    *get_command_path(char **env_variables, char *command)
{
    char *full_path;
    char **path;
    int i;

    i = 0;
    while (env_variables[i])
    {
        if (ft_strncmp(env_variables[i], "PATH", 4) == 0)
            break;
        i++;
    }
    path = ft_split(env_variables[i], ':');
    i = 0;
    while (path[i])
    {
        full_path = ft_strjoin(ft_strjoin(path[i],"/"), command);
        if (access(full_path, F_OK) == 0)
            return (full_path);
        i++;
    }
    return (command);
}

void    executing_command(char **av, char **env_variables, int arg_position)
{
    t_arg arg;

    
    arg.splited_command = ft_split(av[arg_position], ' ');
    arg.full_path = get_command_path(env_variables, arg.splited_command[0]);
    execve(arg.full_path, arg.splited_command, env_variables);
}

void    close_pipes(int (*pipes_array)[2], int array_length,int position)
{
    int i;

    i = 0;
    while (i < array_length)
    {
        if(i != position  - 1)
            close(pipes_array[i][0]); 
        if (i != position)
             close(pipes_array[i][1]);
        i++;
    }
}

void    wait_for_childs(int *p_ids, int commands_number)
{
    int i;

    i = 0;
    while (i < commands_number)
        waitpid(p_ids[i++], 0, 0);
}
void    duplicating(int input, int output)
{
   dup2(input, 0);
   dup2(output, 1);  
}

int main(int ac, char **av, char **env_variables)
{
    int *p_ids;
    int first_file_fd;
    int second_file_fd;
    int command_number;
    int i;
    int (*pipes_array)[2];
    int pipes_number;

    i = 0;
    command_number = ac - 3;
    p_ids = malloc(sizeof(int) * command_number);
    pipes_number = command_number - 1;
    pipes_array = malloc(sizeof(int *) * (command_number - 1));
    first_file_fd = open(av[FIRST_FILE_ARG], O_RDONLY);
    second_file_fd = open(av[ac - 1], O_RDWR | O_CREAT, 0777);
    if (access(av[ac - 1], W_OK) != 0 || ac < 5)
        error_printing();
    // int j = 0;
    while (i < command_number)
    {
        if (access(av[FIRST_FILE_ARG], F_OK) == -1)
            i = 1;
        pipe(pipes_array[i]);
        p_ids[i] = fork();
        if (p_ids[i] == 0)
        {
            close_pipes(pipes_array, (command_number- 1), i);
            if (i == 0)
            {
                duplicating(first_file_fd, pipes_array[i][1]);
                // dup2(first_file_fd, 0);
                // dup2(pipes_array[i][1], 1);
            }
            else if (i == command_number - 1)
            {
                duplicating(pipes_array[i - 1][0], second_file_fd);
                // dup2(second_file_fd, 1);
                // dup2(pipes_array[i - 1][0], 0);
            }
            else
            {
                duplicating(pipes_array[i - 1][0], pipes_array[i][1]);
                // dup2(pipes_array[i - 1][0], 0);
                // dup2(pipes_array[i][1], 1);
            }
            executing_command(av, env_variables, (i + 2));
        }
        i++;
        // j++;
    }
    close_pipes(pipes_array, (command_number- 1), - 1);
    wait_for_childs(p_ids, command_number);
  
}