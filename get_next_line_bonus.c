/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbendnan <fbendnan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 08:03:21 by fbendnan          #+#    #+#             */
/*   Updated: 2025/11/20 12:25:00 by fbendnan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char *safe_join_free(char *s1, char *s2)
{
	char *tmp = ft_strjoin(s1, s2);
	if (!tmp)
        return (free(s1), (NULL));
	return (free(s1), (tmp));
}

static char *read_buffer_and_fill_storage(int fd, char *storage)
{
    char    *buffer;
    ssize_t read_bytes;

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
            break;

        buffer[read_bytes] = '\0';
        storage = safe_join_free(storage, buffer);
        if (!storage)
            return (free(buffer), (NULL));
    }
    return (free(buffer), (storage));
}

static char *extract_line(char *storage)
{
    int     i;
    char    *line;

	i = 0;
    if (!storage || !storage[0])
        return (NULL);
    while (storage[i] && storage[i] != '\n')
        i++;
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
    line[i] = '\0';
    return (line);
}

static char *extract_rest(char *storage)
{
    int     i;
    int     j;
    char    *rest;

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

char *get_next_line(int fd)
{
	static char *storage[1024];
    char        *line;

    if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
        return (NULL);
    if (!storage[fd])
        storage[fd] = NULL;
    storage[fd] = read_buffer_and_fill_storage(fd, storage[fd]);
    if (!storage[fd])
        return (NULL);
    line = extract_line(storage[fd]);
    storage[fd] = extract_rest(storage[fd]);
    return (line);
}
