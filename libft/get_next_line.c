/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shson <shson@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 17:30:57 by shson             #+#    #+#             */
/*   Updated: 2025/10/18 12:45:42 by seokson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_two_pointers(char *p1, char *p2)
{
	free(p1);
	free(p2);
	return (NULL);
}

static int	free_line_new(char **line, char **new)
{
	if (!*line || !*new)
	{
		free(*line);
		free(*new);
		*line = NULL;
		*new = NULL;
		return (1);
	}
	if ((*new)[0] == '\0')
	{
		free(*new);
		*new = NULL;
	}
	return (0);
}

static char	*split_by_newline(char **backup)
{
	char	*line;
	char	*p;
	char	*new;
	size_t	len;

	if (!*backup || !**backup)
		return (free_two_pointers(*backup, NULL));
	p = gnl_strchr(*backup, '\n');
	if (!p)
		len = gnl_strlen(*backup);
	else
		len = p - *backup + 1;
	line = gnl_substr(*backup, 0, len);
	new = gnl_substr(*backup, len, gnl_strlen(*backup) - len);
	free(*backup);
	if (free_line_new(&line, &new))
		return (NULL);
	*backup = new;
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*backup[OPEN_MAX];
	char		*temp;
	char		*buffer;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		temp = backup[fd];
		backup[fd] = gnl_strjoin(backup[fd], buffer);
		free(temp);
		if (!backup[fd])
			return (free_two_pointers(buffer, NULL));
		if (gnl_strchr(backup[fd], '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (split_by_newline(&backup[fd]));
}
