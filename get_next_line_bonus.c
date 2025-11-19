#include "get_next_line_bonus.h"

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
	return (line);
}

void	read_buffer_and_fill_storage(int fd, char **storage)
{
	char	*tmp_line;
	char	*buffer;
	int		read_return;

	buffer = malloc(BUFFER_SIZE + 1);
	if (ft_strchr(*storage, '\n'))
		return;
	tmp_line = "";
	while (!ft_strchr(*storage, '\n') && (read_return = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[read_return] = '\0';
		tmp_line = ft_strjoin(*storage, buffer);
		free(*storage);
		*storage = tmp_line;
	}
	free(buffer);
}

char	*get_next_line(int fd)
{
	static char *storage[1024];
	char	*line;

	if (fd == -1)
		return (NULL);
	if(!storage[fd])
		storage[fd] = ft_strdup("");
	read_buffer_and_fill_storage(fd, &storage[fd]);
	if (!storage[fd] || storage[fd][0] == '\0')
	{
		free(storage[fd]);
		storage[fd] = NULL;
		return (NULL);
	}
	line = extract_line(&storage[fd]);
	return (line);
}
