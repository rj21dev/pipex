/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjada <rjada@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:55:49 by rjada             #+#    #+#             */
/*   Updated: 2022/02/12 23:39:01 by rjada            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*read_from_fd(int fd, char **remainder, char **line);

static char	*eof_errno_case(int bytes_read, char **remainder, char **line);

char	*get_next_line(int fd)
{
	static char	*tail[OPEN_MAX + 1];
	char		*line;
	char		*eol_ptr;
	char		*tmp;

	line = NULL;
	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	if (tail[fd])
	{
		eol_ptr = ft_strchr(tail[fd], '\n');
		if (eol_ptr)
		{
			line = ft_substr(tail[fd], 0, eol_ptr - tail[fd] + 1);
			tmp = ft_substr(tail[fd], eol_ptr - tail[fd] + 1, BUFFER_SIZE);
			free(tail[fd]);
			tail[fd] = tmp;
			return (line);
		}
		line = tail[fd];
		tail[fd] = NULL;
	}
	else
		line = ft_realloc(line, 1);
	return (read_from_fd(fd, &tail[fd], &line));
}

static char	*read_from_fd(int fd, char **remainder, char **line)
{
	char	buf[BUFFER_SIZE + 1];
	char	*eol_ptr;
	int		len;
	int		bytes_read;

	len = ft_strlen(*line) + 1;
	while (TRUE)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
		if (bytes_read <= 0)
			return (eof_errno_case(bytes_read, remainder, line));
		eol_ptr = ft_strchr(buf, '\n');
		if (eol_ptr)
			break ;
		len += bytes_read;
		*line = ft_realloc(*line, len);
		ft_strlcat(*line, buf, len);
	}
	len += eol_ptr - buf + 1;
	*line = ft_realloc(*line, len);
	ft_strlcat(*line, buf, len);
	*remainder = ft_substr(buf, eol_ptr - buf + 1, BUFFER_SIZE);
	return (*line);
}

static char	*eof_errno_case(int bytes_read, char **remainder, char **line)
{
	int	len;

	len = ft_strlen(*line);
	if ((*line && bytes_read < 0) || (*line && !len && !bytes_read))
	{
		free(*line);
		*line = NULL;
	}
	if (*remainder && bytes_read < 0)
	{
		free(*remainder);
		*remainder = NULL;
	}
	return (*line);
}
