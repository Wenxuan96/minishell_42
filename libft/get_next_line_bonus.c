/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wxi <wxi@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 12:43:01 by wxi               #+#    #+#             */
/*   Updated: 2025/02/23 20:10:30 by wxi              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size -1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

static char	*initiat_n_extract_nl(char	**remainder)
{
	char	*newline_pos;
	char	*nextline;
	char	*temp;

	nextline = NULL;
	if (!(*remainder))
		return (NULL);
	newline_pos = ft_strchr(*remainder, '\n');
	if (newline_pos)
	{
		nextline = ft_substr(*remainder, 0, newline_pos - *remainder + 1);
		temp = ft_strdup(newline_pos + 1);
		free(*remainder);
		*remainder = temp;
	}
	return (nextline);
}

static int	read_n_update_remainder(int fd, char *buffer, char **remainder,
									ssize_t *readbytes)
{
	char	*tmp;	

	*readbytes = read(fd, buffer, BUFFER_SIZE);
	if (!(*remainder))
		*remainder = ft_strdup("");
	if (*remainder == NULL)
		return (-1);
	if (*readbytes > 0)
	{
		buffer[*readbytes] = '\0';
		tmp = ft_strjoin(*remainder, buffer);
		free(*remainder);
		if (tmp == NULL)
		{
			*remainder = NULL;
			return (-1);
		}
		*remainder = tmp;
	}
	if (*readbytes < 0)
	{
		free(*remainder);
		*remainder = NULL;
	}
	return (*readbytes);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*remainder[1024] = {NULL};
	char		*nextline;
	ssize_t		readbytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1024)
		return (NULL);
	nextline = initiat_n_extract_nl(&remainder[fd]);
	if (nextline)
		return (nextline);
	while (read_n_update_remainder(fd, buffer, &remainder[fd], &readbytes) > 0)
	{
		nextline = initiat_n_extract_nl(&remainder[fd]);
		if (nextline)
			return (nextline);
	}
	if (readbytes == 0 && remainder[fd])
	{
		if (*remainder[fd])
			nextline = ft_strdup(remainder[fd]);
		free(remainder[fd]);
		return (remainder[fd] = NULL, nextline);
	}
	return (NULL);
}
