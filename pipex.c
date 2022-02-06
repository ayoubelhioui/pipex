/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:32:05 by marvin            #+#    #+#             */
/*   Updated: 2022/01/26 16:32:05 by marvin           ###   ########.fr       */
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
void    wait_and_close(t_variables *var)
{
    wait(NULL);
    wait(NULL);
    close(var->fd_pipe[INPUT_FD]);
    close(var->fd_pipe[OUTPUT_FD]);
    close(var->first_file_fd);
    close(var->second_file_fd); 
}

void    executing_command(t_variables *var, char **av,char **env_variables, int sign)
{
    if (sign == SECOND_CHILD_PROC)
    {
        close(var->fd_pipe[OUTPUT_FD]);
        dup2(var->second_file_fd, OUTPUT_FD);
        dup2(var->fd_pipe[INPUT_FD], INPUT_FD);
        var->splited_command = ft_split(av[SECOND_COMMAND_ARG], ' ');
        var->full_path = get_command_path(env_variables, var->splited_command[0]);
        execve(var->full_path, var->splited_command, env_variables);
    }
    else
    {
        close(var->fd_pipe[INPUT_FD]);
        dup2(var->first_file_fd, INPUT_FD);
        dup2(var->fd_pipe[OUTPUT_FD], OUTPUT_FD);
        var->splited_command = ft_split(av[FIRST_COMMAND_ARG], ' ');
        var->full_path = get_command_path(env_variables, var->splited_command[0]);
        execve(var->full_path, var->splited_command, env_variables);
    }
}

int main(int ac, char **av, char **env_variables)
{
    t_variables var;

    var.fd_pipe = malloc(sizeof(int) * 2);
    pipe(var.fd_pipe);
    var.first_file_fd = open(av[FIRST_FILE_ARG], O_RDONLY);
    var.second_file_fd = open(av[SECOND_FILE_ARG], O_RDWR | O_CREAT, 0777);
    if (access(av[FIRST_FILE_ARG], R_OK) != 0 || access(av[SECOND_FILE_ARG], W_OK) != 0 || ac < 5)
        error_printing();
    var.first_process_id = fork();
    if (var.first_process_id == 0)
    {
        var.second_process_id = fork();
        if (var.second_process_id == 0)
            executing_command(&var, av, env_variables, SECOND_CHILD_PROC);
        else
            executing_command(&var, av, env_variables, FIRST_CHILD_PROC);
    }
    else 
       wait_and_close(&var);
    while (1);
}