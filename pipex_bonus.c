/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:07:39 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/02/10 14:16:59 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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
    if (execve(arg.full_path, arg.splited_command, env_variables) == -1){
        perror("");
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

void    get_lines(char *limiter)
{
	char	*saver;
	char	*last;

	saver = NULL;
	last = get_next_line(0);
	while (last)
	{
        if (ft_strcmp(last, limiter) == 0)
            return ;
        last = get_next_line(0);
	}
}
void    pipe_simulating(t_process_vars *vars, char **av, char **env_variables)
{
    int i;
    
    i = 0;
    while (i < vars->command_number){
    pipe(vars->pipes_array[i]);
    vars->p_ids[i] = fork();
    if (vars->p_ids[i] == 0){
        close_pipes(vars->pipes_array, vars->pipes_number, i);
        if (i == 0){
            vars->first_file_fd = open(av[FIRST_FILE_ARG], O_RDONLY);
            if (vars->first_file_fd < 0){
                perror(av[FIRST_FILE_ARG]);
                exit(1);
            }
            duplicating(vars->first_file_fd, vars->pipes_array[i][1]);
        }
        else if (i == vars->command_number - 1)   
            duplicating(vars->pipes_array[i - 1][0], vars->second_file_fd);
        else
            duplicating(vars->pipes_array[i - 1][0], vars->pipes_array[i][1]);
        executing_command(av, env_variables, (i + 2));
    }
    i++;
}
}
int main(int ac, char **av, char **env_variables)
{
    t_process_vars vars;
    int i;

    i = 0;
    vars.command_number = ac - 3;
    vars.p_ids = malloc(sizeof(int) * vars.command_number);
    vars.pipes_number = vars.command_number - 1;
    vars.second_file_fd = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (ft_strcmp(av[FIRST_FILE_ARG], "here_doc") == 0){
        get_lines(av[2]);
    }
    vars.pipes_array = malloc(sizeof(int *) * vars.pipes_number);
    if (access(av[ac - 1], W_OK) != 0 || ac < 5)
        error_printing();
    // while (i < vars.command_number){
    //     pipe(vars.pipes_array[i]);
    //     vars.p_ids[i] = fork();
    //     if (vars.p_ids[i] == 0){
    //         close_pipes(vars.pipes_array, vars.pipes_number, i);
    //         if (i == 0){
    //             vars.first_file_fd = open(av[FIRST_FILE_ARG], O_RDONLY);
    //             if (vars.first_file_fd < 0){
    //                 perror(av[FIRST_FILE_ARG]);
    //                 exit(1);
    //             }
    //             duplicating(vars.first_file_fd, vars.pipes_array[i][1]);
    //         }
    //         else if (i == vars.command_number - 1)   
    //             duplicating(vars.pipes_array[i - 1][0], vars.second_file_fd);
    //         else
    //             duplicating(vars.pipes_array[i - 1][0], vars.pipes_array[i][1]);
    //         executing_command(av, env_variables, (i + 2));
    //     }
    //     i++;
    // }
    pipe_simulating(&vars, av, env_variables);
    close_pipes(vars.pipes_array, vars.pipes_number, -1);
    wait_for_childs(vars.p_ids, vars.command_number);
    close(vars.second_file_fd);
    close(vars.first_file_fd);
}