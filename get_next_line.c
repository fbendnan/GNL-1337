#include "get_next_line.h"

char	*extract_line(char **buffer)
{
    char    *line;
	char	*newline;

	newline = ft_strchr(buffer, '\n');
	line = ft_strlen(buffer) - ft_strlen(newline) + 1; 
	line = ft_substr(buffer, 0, ft_strlen(buffer) - ft_strlen(newline));
	buffer = newline++;

	return (line);
}

char    *read_buffer(int fd, char **buffer)
{
	char	*line;
	char	buff[BUFFER_SIZE];

	while (read(fd, buff, 0))
	{
		read(fd, buff, BUFFER_SIZE);
		line = ft_strjoin(buffer, buff);
		if (ft_strchr(buff, '\n'))
			return (1);
		read(fd, buff, BUFFER_SIZE);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char **buffer;

	if (fd == -1)
		return (NULL);
	
	// if (!buffer)
	// 	buffer = ft_strdup("");
	if(read_buffer(fd, buffer))
		return (extract_line(buffer));
	free(buffer);
}