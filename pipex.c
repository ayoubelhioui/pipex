/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:07:39 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/02/21 12:47:04 by ael-hiou         ###   ########.fr       */
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
			return (full_path);
	}
	return (command);
}
// char *between_quotes(char *command)
// {
// 	int i;

// 	i = 0;
// 	while (command[i] || command[i] != '\'')
// 		i++;
// 	ret
// }
char	**find_quotes(char *command)
{
	int	i;
	char **s;

	i = 0;
	s = NULL;
	while (command[i])
	{
		if (command[i] == '\'')
		{
			s = malloc(sizeof(char *) * 3);
			s[0] = ft_substr(command, 0, i - 1);
			s[1] = ft_substr(command, i + 1, ft_strlen(command) - i - 2);
			s[2] = NULL;	
			return (s);
		}
		i++;
	}
	return (NULL);
}
void	executing_command(char **av, char **env_variables, int arg_position)
{
	t_arg	arg;
	char **quotes_handling;

	quotes_handling = NULL;
	if (ft_strlen(av[arg_position]) == 0)
		error_printing("Command Not Found\n", ERROR_FD);
	quotes_handling = find_quotes(av[arg_position]);
	if (quotes_handling)
		arg.splited_command = quotes_handling;
	else
		arg.splited_command = ft_split(av[arg_position], ' ');
	arg.full_path = get_command_path(env_variables, arg.splited_command[0]);
	if (execve(arg.full_path, arg.splited_command, env_variables) == -1)
		error_printing("Command Not Found\n", ERROR_FD);
}

void	getting_things_ready(t_process_vars *vars, char **av, int ac)
{
	vars->command_number = ac - 3;
	vars->p_ids = malloc(sizeof(int) * vars->command_number);
	vars->first_command_position = 2;
	if (ft_strcmp(av[FIRST_FILE_ARG], HERE_DOC) == 0)
	{
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
	if (vars->output_fd < 0)
	{
		perror("");
		exit (1);
	}
	vars->pipes_number = vars->command_number - 1;
	vars->pipes_array = malloc(sizeof(int *) * vars->pipes_number);
}

void	pipe_simulating(t_process_vars *vars, char **av, \
		char **env_variables, int index)
{
	if (vars->p_ids[index] == 0)
	{
		close_unused_pipes(vars ->pipes_array, index);
		if (index == 0)
		{
			if (vars->input_fd < 0)
				error_printing("no such file or directory\n", OUTPUT_FD);
			duplicating(vars->input_fd, vars->pipes_array[index][1]);
		}
		else if (index == vars->command_number - 1)
			duplicating(vars->pipes_array[index - 1][INPUT_FD], \
					vars->output_fd);
		else
			duplicating(vars->pipes_array[index - 1][INPUT_FD], \
				vars->pipes_array[index][OUTPUT_FD]);
		executing_command(av, env_variables, \
				(index + vars->first_command_position));
	}
}

int	main(int ac, char **av, char **env_variables)
{
	t_process_vars	vars;
	int				i;

	i = 0;
	getting_things_ready(&vars, av, ac);
	while (i < vars.command_number)
	{
		pipe(vars.pipes_array[i]);
		vars.p_ids[i] = fork();
		pipe_simulating(&vars, av, env_variables, i);
		i++;
	}
	close_pipes(vars.pipes_array, vars.pipes_number);
	wait_for_childs(vars.p_ids, vars.command_number);
	close(vars.input_fd);
	close(vars.output_fd);
}
