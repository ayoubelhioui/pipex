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

char	*ft_get_all_lines(int fd)
{
	char	*saver;
	char	*last;

	saver = NULL;
	last = get_next_line(fd);
	while (last)
	{
		saver = ft_strjoin(saver, last);
		free (last);
		last = get_next_line(fd);
		if (!last)
			break ;
	}
	return (saver);
}

int main(int ac, char **av, char **env_variables)
{
    int id;
    // int fd[2];
    char *full_path;
    char **splited_argument;
    // int fd;

    // fd = open(av[1], 2);
    if (access(av[1], R_OK) != 0 || access(av[4], W_OK) != 0 || ac < 5)
        error_printing();
    // pipe(fd);
    id = fork();
    splited_argument= ft_split(av[2], ' ');
    full_path = get_command_path(env_variables, splited_argument[0]);
    if (id == 0)
    {
        execve(full_path, splited_argument, env_variables);
    }
    else
    {
        wait(NULL);
    }

}