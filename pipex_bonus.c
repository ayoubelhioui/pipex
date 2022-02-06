/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:07:39 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/02/06 19:10:07 by ael-hiou         ###   ########.fr       */
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
    execve(arg.full_path, arg.splited_command, env_variables);
}


int main(int ac, char **av, char **env_variables)
{
    t_arg   arg;
    t_process_vars var;
    int id;
    int id2;
    int first_file_fd;
    int second_file_fd;
    int *processes_array;
    int command_number;
    int i;
    int *pipe;
    int **fd_pipe;

    i = 0;
    command_number = ac - 3;
    pipe = malloc(sizeof(int) * 2);
    fd_pipe = malloc(sizeof(pipe) * (command_number) - 1);
    first_file_fd = open(av[FIRST_FILE_ARG], O_RDONLY);
    second_file_fd = open(av[SECOND_FILE_ARG], O_RDWR | O_CREAT, 0777);
    fd_pipe[0][1] = first_file_fd;
    fd_pipe[command_number + 1][0] = second_file_fd;
    if (access(av[FIRST_FILE_ARG], R_OK) != 0 || access(av[SECOND_FILE_ARG], W_OK) != 0 || ac < 5)
        error_printing();
    while (i < command_number)
    {
        // id = fork();
        // pipe(fd_pipe);
        // if (id == 0)
        // {
        //     if (i == 0)
        //     {
        //         close(fd_pipe[OUTPUT_FD]);
        //         dup2(first_file_fd, INPUT_FD);
        //         dup2(fd_pipe[OUTPUT_FD], OUTPUT_FD);
        //         executing_command(av, env_variables, (i + 2));
        //     }
        // }
        // else
        // {
        //     id2 = fork();
        //     if (id2 == 0)
        //     {
                
        //     }
        // }
    }
}