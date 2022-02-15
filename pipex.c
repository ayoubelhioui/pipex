/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:07:39 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/02/15 10:48:10 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_command_path(char **env_variables, char *command)
{
	char	*full_path;
	char	**path;
	int		i;

	i = -1;
	while (env_variables[++i])
	{
		if (ft_strncmp(env_variables[i], "PATH", 4) == 0)
			break ;
	}
	path = ft_split(env_variables[i], ':');
	i = -1;
	while (path[++i])
	{
		full_path = ft_strjoin(ft_strjoin(path[i], "/"), command);
		if (access(full_path, F_OK) == 0)
		{
			i = 0;
			while (path[i])
				free(path[i++]);
			free(path);
			return (full_path);
		}
	}
	return (command);
}

void	executing_command(char **av, char **env_variables, int arg_position)
{
	t_arg	arg;

	if (ft_strlen(av[arg_position]) == 0)
		error_printing("Command Not Found\n", ERROR_FD);
	arg.splited_command = ft_split(av[arg_position], ' ');
	arg.full_path = get_command_path(env_variables, arg.splited_command[0]);
	if (execve(arg.full_path, arg.splited_command, env_variables) == -1)
		error_printing("Command Not Found\n", ERROR_FD);
}

void	pipe_simulating(t_process_vars *vars, char **av, \
		char **env_variables, int index)
{
	pipe(vars->pipes_array[index]);
	vars->p_ids[index] = fork();
	if (vars->p_ids[index] == 0)
	{
		if (index == 0)
		{
			close(vars->pipes_array[index][0]);
			if (vars->input_fd < 0)
				error_printing("no such file or directory\n", OUTPUT_FD);
			duplicating(vars->input_fd, vars->pipes_array[index][1]);
		}
		else if (index == vars->command_number - 1)
		{
			close(vars->pipes_array[index - 1][OUTPUT_FD]);
			duplicating(vars->pipes_array[index - 1][INPUT_FD], \
					vars->output_fd);
		}
		else
		{
			close(vars->pipes_array[index - 1][OUTPUT_FD]);
			close(vars->pipes_array[index][INPUT_FD]);
			duplicating(vars->pipes_array[index - 1][INPUT_FD], \
				vars->pipes_array[index][OUTPUT_FD]);
		}
		executing_command(av, env_variables, \
				(index + vars->first_command_position));
	}
}

void	getting_things_ready(t_process_vars *vars, char **av, int ac)
{
	vars->command_number = ac - 3;
	vars->p_ids = malloc(sizeof(int) * vars->command_number);
	vars->first_command_position = 2;
	if (ft_strcmp(av[FIRST_FILE_ARG], HERE_DOC) == 0)
	{
		vars->input_fd = open(av[FIRST_FILE_ARG], O_RDONLY);
		vars->output_fd = open(av[ac - 1], O_RDWR | O_CREAT \
				| O_APPEND, FULL_ACCESS);
		vars->input_fd = get_input_lines(av[2]);
		vars->command_number--;
		vars->first_command_position++;
	}
	else
	{
		vars->input_fd = open(av[FIRST_FILE_ARG], O_RDONLY);
		vars->output_fd = open(av[ac - 1], O_RDWR \
				| O_CREAT | O_TRUNC, FULL_ACCESS);
	}
	vars->pipes_number = vars->command_number - 1;
	vars->pipes_array = malloc(sizeof(int *) * vars->pipes_number);
}

int	main(int ac, char **av, char **env_variables)
{
	t_process_vars	vars;
	int				i;

	i = 0;
	if (ac < 5)
		error_printing("Need more arguments\n", OUTPUT_FD);
	getting_things_ready(&vars, av, ac);
	while (i < vars.command_number)
	{
		pipe_simulating(&vars, av, env_variables, i);
		i++;
	}
	close_pipes(vars.pipes_array, vars.pipes_number);
	wait_for_childs(vars.p_ids, vars.command_number);
	close(vars.input_fd);
	close(vars.output_fd);
}
