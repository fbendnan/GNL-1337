/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbendnan <fbendnan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 10:38:17 by fbendnan          #+#    #+#             */
/*   Updated: 2025/11/17 15:49:33 by fbendnan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char **storage)
{
    char    *line;
	char	*newline_p;

	newline_p = ft_strchr(*storage, '\n') + 1;
	newline_p = ft_substr(newline_p, 0, ft_strlen(newline_p));
	line = ft_substr(*storage, 0, (ft_strlen(*storage) - ft_strlen(newline_p)) + 1);
	free(*storage);
	*storage = NULL;
	*storage = ft_strdup(newline_p);
	free(newline_p);
	return (line);
}

void    read_buffer(int fd, char **storage)
{
	char	*tmp_line;
	char	buffer[BUFFER_SIZE];
	int		read_return;

	if (ft_strchr(*storage, '\n'))
		return;
	read_return = read(fd, buffer, BUFFER_SIZE);
	while (read_return && !ft_strchr(*buffer, '\n'))
	{
		tmp_line = ft_strjoin(*storage, buffer);
		*storage = ft_strdup(tmp_line);
		read_return = read(fd, buffer, BUFFER_SIZE);
	}
	free(tmp_line);
	free(buffer);
}

char	*get_next_line(int fd)
{
	static char *storage;
	char	*line;

	if (fd == -1)
		return (NULL);
	if(!storage)
		storage = ft_strdup("");
	read_buffer(fd, *storage);
	line = extract_line(*storage);
	return (line);
}
