/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dduraku <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 11:29:02 by dduraku           #+#    #+#             */
/*   Updated: 2022/03/10 11:29:04 by dduraku          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_line(char *buffer)
{
	int		i;
	char	*str;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 1) + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		str[i] = buffer[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_read(int fd, char *str)
{
	char	*buffer;
	int		bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(str, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		str = ft_strjoin(str, buffer);
	}
	free(buffer);
	return (str);
}

char	*ft_buffer(char *buffer)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!str)
		return (NULL);
	i++;
	while (buffer[i])
		str[j++] = buffer[i++];
	str[j] = '\0';
	free(buffer);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer[fd] = ft_read(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_line(buffer[fd]);
	buffer[fd] = ft_buffer(buffer[fd]);
	return (line);
}
