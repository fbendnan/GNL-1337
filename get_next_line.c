/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbendnan <fbendnan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 08:03:36 by fbendnan          #+#    #+#             */
/*   Updated: 2025/11/23 15:13:20 by fbendnan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*safe_join_free(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	if (!tmp)
		return (free(s1), (NULL));
	return (free(s1), (tmp));
}

static char	*read_buffer_and_fill_storage(int fd, char *storage)
{
	char	*buffer;
	ssize_t	read_bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (read_bytes > 0 && (!storage || !ft_strchr(storage, '\n')))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(buffer);
			free(storage);
			return (NULL);
		}
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		storage = safe_join_free(storage, buffer);
		if (!storage)
			return (free(buffer), (NULL));
	}
	return (free(buffer), (storage));
}

static char	*extract_line(char *storage)
{
	int		i;
	char	*line;

	i = 0;
	if (!storage || !storage[0])
		return (NULL);
	while (storage[i] && storage[i] != '\n')
	{
		i++;
	}
	if (storage[i] == '\n')
		line = malloc(i + 2);
	else
		line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
		line[i++] = '\n';
	return (line[i] = '\0', line);
}

static char	*extract_rest(char *storage)
{
	int		i;
	int		j;
	char	*rest;

	i = 0;
	if (!storage)
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
		return (free(storage), (NULL));
	rest = malloc(ft_strlen(storage) - i);
	if (!rest)
		return (free(storage), (NULL));
	i++;
	j = 0;
	while (storage[i])
		rest[j++] = storage[i++];
	rest[j] = '\0';
	return (free(storage), (rest));
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage = read_buffer_and_fill_storage(fd, storage);
	if (!storage)
		return (NULL);
	line = extract_line(storage);
	storage = extract_rest(storage);
	return (line);
}
