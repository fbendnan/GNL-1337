/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbendnan <fbendnan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 08:03:36 by fbendnan          #+#    #+#             */
/*   Updated: 2025/11/20 12:25:49 by fbendnan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (!dst || !src)
		return (0);
	if (size != 0)
	{
		while (src[i] && (i < size -1))
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

char	*extract_line(char **storage)
{
	char	*line;
	char	*newline_p;
	char	*rest;
	int		len_line;

	newline_p = ft_strchr(*storage, '\n');
	if (!newline_p)
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
	return (line);
}

void	read_buffer_and_fill_storage(int fd, char **storage)
{
	char	*tmp_line;
	char	*buffer;
	int		read_return;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return ;
	if (ft_strchr(*storage, '\n'))
		return ;
	read_return = 1;
	while (!ft_strchr(*storage, '\n') && read_return > 0)
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		if (read_return <= 0)
			break ;
		buffer[read_return] = '\0';
		tmp_line = ft_strjoin(*storage, buffer);
		free(*storage);
		*storage = tmp_line;
	}
	free(buffer);
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd == -1)
		return (NULL);
	if (!storage)
		storage = ft_strdup("");
	read_buffer_and_fill_storage(fd, &storage);
	if (!storage || storage[0] == '\0')
	{
		free(storage);
		storage = NULL;
		return (NULL);
	}
	line = extract_line(&storage);
	return (line);
}
