/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:07:39 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/02/13 11:58:08 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void     error_printing()
{
    ft_putstr_fd("Error\n", OUTPUT_FD);
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
        full_path = ft_strjoin(ft_strjoin(path[i], "/"), command);
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
    if (execve(arg.full_path, arg.splited_command, env_variables) == -1)
    {
        ft_putstr_fd("Command Not Found \n", 2);
        exit(1);
    }
}

void    close_pipes(int (*pipes_array)[2], int array_length, int position)
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

int get_input_lines(char *limiter)
{
	char	*saver;
	char	*last;
    int fd;

	saver = NULL;
	last = get_next_line(0);
    unlink("/tmp/.temp_file");
    fd = open("/tmp/.temp_file", O_WRONLY | O_CREAT, 0777);
	while (last)
	{
        if (ft_strcmp(last, limiter) == 0)
            break ;
        ft_putstr_fd(last, fd);
        ft_putstr_fd("\n", fd);
        last = get_next_line(0);
	}
    close(fd);
    open("/tmp/.temp_file", O_RDONLY, 0777);
    return (fd);
}

void    pipe_simulating(t_process_vars *vars, char **av, char **env_variables, int index)
{
    pipe(vars->pipes_array[index]);
    vars->p_ids[index] = fork();
    if (vars->p_ids[index] == 0)
    {
        close_pipes(vars->pipes_array, vars->pipes_number, index);
        if (index == 0)
        {
            if (vars->input_fd < 0)
            {
                ft_putstr_fd("no such file or directory\n", OUTPUT_FD);
                exit(1);
            }
            duplicating(vars->input_fd, vars->pipes_array[index][1]);
        }
        else if (index == vars->command_number - 1)
            duplicating(vars->pipes_array[index - 1][0], vars->output_fd);
        else
            duplicating(vars->pipes_array[index - 1][0], vars->pipes_array[index][1]);
        executing_command(av, env_variables, (index + vars->first_command_position));
    }
}

void    getting_things_ready(t_process_vars *vars, char **av, int ac)
{

    vars->command_number = ac - 3;
    vars->p_ids = malloc(sizeof(int) * vars->command_number);
    vars->first_command_position = 2;
    if (ft_strcmp(av[FIRST_FILE_ARG], "here_doc") == 0)
    {
        vars->output_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0777);
        vars->input_fd = get_input_lines(av[2]);
        vars->command_number--;
        vars->first_command_position++;
    }
    else
    {
        vars->output_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
        vars->input_fd = open(av[FIRST_FILE_ARG], O_RDONLY);
    }
    vars->pipes_number = vars->command_number - 1;
    vars->pipes_array = malloc(sizeof(int *) * vars->pipes_number);
    if (ac < 5)
        error_printing();
}

int main(int ac, char **av, char **env_variables)
{
    t_process_vars vars;
    int i;

    i = 0;
    getting_things_ready(&vars, av, ac);
    while (i < vars.command_number)
    {
        pipe_simulating(&vars, av, env_variables, i);
        i++;
    }
    close_pipes(vars.pipes_array, vars.pipes_number, -1);
    wait_for_childs(vars.p_ids, vars.command_number);
    close(vars.input_fd);
    close(vars.output_fd);
}