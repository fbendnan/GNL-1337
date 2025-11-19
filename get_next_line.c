/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbendnan <fbendnan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:38:17 by fbendnan          #+#    #+#             */
/*   Updated: 2025/11/19 08:18:51 by fbendnan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> //////

char	*extract_line(char **storage)
{
    char    *line;
	char	*newline_p;
	char	*rest;
	int		len_line;

	newline_p = ft_strchr(*storage, '\n');
	if(!newline_p)
	{
		line = ft_strdup(*storage);
		free(*storage);
		*storage = NULL;
		return (line);
	}
	len_line = newline_p - *storage + 1;
	// //////
	// printf("len line = %d\n",len_line);
	line = ft_substr(*storage, 0, len_line);
	////
	// printf("line = %s\n",line);
	rest = ft_substr(*storage, len_line, (ft_strlen(*storage) - len_line));
	// ////////
	// printf("rest = %s\n",rest);
	free(*storage);
	*storage = rest;
	return (line);
}

void	read_buffer_and_fill_storage(int fd, char **storage)
{
	char	*tmp_line;
	char	buffer[BUFFER_SIZE + 1];
	int		read_return;

	if (ft_strchr(*storage, '\n'))
		return;
	tmp_line = ft_strdup("");
	while (!ft_strchr(*storage, '\n') && (read_return = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_return] = '\0';
		tmp_line = ft_strjoin(*storage, buffer);
		free(*storage);
		*storage = tmp_line;
	}
}

char	*get_next_line(int fd)
{
	static char *storage;
	char	*line;

	if (fd == -1)
		return (NULL);
	if(!storage)
		storage = ft_strdup("");
	read_buffer_and_fill_storage(fd, &storage);
	if (!storage || storage[0] == '\0')
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	line = extract_line(&storage);
	/////
	// printf("storage after extract line = %s", storage);
	return (line);
}
