/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:07:39 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/02/08 11:25:06 by ael-hiou         ###   ########.fr       */
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
    return (NULL);
}

// void    executing_command(t_process_vars *var, char **av,char **env_variables, int sign)
// {
//     if (sign == SECOND_CHILD_PROC)
//     {
//         close(var->fd_pipe[OUTPUT_FD]);
//         dup2(var->second_file_fd, OUTPUT_FD);
//         dup2(var->fd_pipe[INPUT_FD], INPUT_FD);
//         var->splited_command = ft_split(av[SECOND_COMMAND_ARG], ' ');
//         var->full_path = get_command_path(env_variables, var->splited_command[0]);
//         execve(var->full_path, var->splited_command, env_variables);
//     }
//     else
//     {
//         close(var->fd_pipe[INPUT_FD]);
//         dup2(var->first_file_fd, INPUT_FD);
//         dup2(var->fd_pipe[OUTPUT_FD], OUTPUT_FD);
//         var->splited_command = ft_split(av[FIRST_COMMAND_ARG], ' ');
//         var->full_path = get_command_path(env_variables, var->splited_command[0]);
//         execve(var->full_path, var->splited_command, env_variables); 
//     }
// }
void    executing_command(char **av, char **env_variables,int arg_position)
{
    t_arg arg;

    
    arg.splited_command = ft_split(av[arg_position], ' ');
    arg.full_path = get_command_path(env_variables, arg.splited_command[0]);
    printf("Im In The Execute \n");
    execve(arg.full_path, arg.splited_command, env_variables);
}


int main(int ac, char **av, char **env_variables)
{
    int id;
    int first_file_fd;
    int second_file_fd;
    int command_number;
    int i;
    int *pipe_fd;
    int **pipes_array;

    i = 0;
    command_number = ac - 3;
    pipe_fd = malloc(sizeof(int) * 2);
    pipes_array = malloc(sizeof(pipe_fd) * (command_number) - 1);
    first_file_fd = open(av[FIRST_FILE_ARG], O_RDONLY);
    second_file_fd = open(av[ac - 1], O_RDWR | O_CREAT, 0777);
    if (access(av[FIRST_FILE_ARG], R_OK) != 0 || access(av[ac - 1], W_OK) != 0 || ac < 5)
        error_printing();
    int j = 0;
    while (i < command_number && j < 1)
    {
        pipe(pipes_array[i]);
        id = fork();
        if (id == 0)
        {
            if (i == 0)
            {
                close(pipes_array[i][0]);
                dup2(first_file_fd, 0);
                dup2(pipes_array[i][1], 1);
                printf("Im Here\n");
                executing_command(av, env_variables, (i + 2));
            }
            else if (i == command_number - 1)
            {
                dup2(pipes_array[i - 1][0], 0);
                close(pipes_array[i - 1][0]);
                close(pipes_array[i - 1][1]);
                dup2(second_file_fd, 1);
            }
            else
            {
                dup2(pipes_array[i - 1][0], 0);
                close(pipes_array[i - 1][0]);
                close(pipes_array[i - 1][1]);
                dup2(pipes_array[i][1], 1);
                executing_command(av, env_variables, (i + 2));
            }
        }
        else
            waitpid(id, 0, 0);
        i++;
        j++;
    }
}