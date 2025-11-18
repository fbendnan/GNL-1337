/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbendnan <fbendnan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:38:17 by fbendnan          #+#    #+#             */
/*   Updated: 2025/11/18 15:44:46 by fbendnan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	line = ft_substr(*storage, 0, len_line);
	rest = ft_substr(*storage, len_line, (ft_strlen(*storage) - len_line));
	free(*storage);
	*storage = rest;
	free(rest);
	return (line);
}

void	read_buffer_and_fill_storage(int fd, char **storage)
{
	char	*tmp_line;
	char	buffer[BUFFER_SIZE];
	int		read_return;

	if (ft_strchr(*storage, '\n'))
		return;
	read_return = read(fd, buffer, BUFFER_SIZE);
	while (read_return && !ft_strchr(buffer, '\n'))
	{
		free(tmp_line);
		tmp_line = ft_strjoin(*storage, buffer);
		*storage = tmp_line;
		read_return = read(fd, buffer, BUFFER_SIZE);
	}
	free(tmp_line);
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
	line = extract_line(&storage);
	return (line);
}
