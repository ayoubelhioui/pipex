/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-hiou <ael-hiou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 18:24:28 by ael-hiou          #+#    #+#             */
/*   Updated: 2022/02/09 14:20:34 by ael-hiou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strchr(char *s, int c)
{
	int		i;

	i = 0;
	c = (char)c;
	if (!s)
		return (-1);
	while (s[i] && s[i] != c)
		i++;
	if (s[i] == c)
		return (i);
	return (-1);
}

char	*coppy_remainder(char *str, int index)
{
	int		k;
	int		i;
	int		len;	
	char	*remainder;

	i = index;
	len = ft_strlen(str + index);
	k = 0;
	remainder = malloc(sizeof(char) * (len + 1));
	while (str[i])
	{
		remainder[k++] = str[i++];
	}
	remainder[k] = '\0';
	free(str);
	return (remainder);
}

char	*ft_cut(char *str, int index)
{
	char	*line;

	line = malloc(sizeof(char) * (index + 1));
	ft_strlcpy(line, str, index + 1);
	return (line);
}

char	*ft_helper(int fd, char *buffer)
{
	int		k;
	char	*temp;

	k = 1;
	temp = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	while ((ft_strchr(buffer, '\n') == -1) && k != 0)
	{
		k = read(fd, temp, BUFFER_SIZE);
		if (k == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[k] = '\0';
		buffer = ft_strjoin(buffer, temp);
	}
	free(temp);
	if (k == 0 && ft_strlen(buffer) == 0)
	{
		free(buffer);
		buffer = NULL;
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	int			index_new_line;
	char		*line;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_strchr(buffer[fd], '\n') == -1)
		buffer[fd] = ft_helper(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	index_new_line = ft_strchr(buffer[fd], '\n');
	if (index_new_line == -1)
	{
		line = buffer[fd];
		buffer[fd] = NULL;
		return (line);
	}
	line = ft_cut(buffer[fd], index_new_line);
	buffer[fd] = coppy_remainder(buffer[fd], index_new_line + 1);
	return (line);
}
