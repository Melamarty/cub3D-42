/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-amar <mel-amar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:29:13 by mel-amar          #+#    #+#             */
/*   Updated: 2024/09/15 15:29:13 by mel-amar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_line(int fd, char *buffer, char *remainder)
{
	ssize_t	r;
	char	*tmp;

	r = 1;
	while (r > 0)
	{
		r = read(fd, buffer, BUFFER_SIZE);
		if (r == -1)
		{
			return (NULL);
		}
		if (r == 0)
			break ;
		buffer[r] = '\0';
		if (remainder == NULL)
			remainder = ft_strdup("");
		tmp = remainder;
		remainder = ft_strjoin(tmp, buffer);
		tmp = NULL;
		if (strrchr(buffer, '\n'))
			break ;
	}
	return (remainder);
}

char	*update_remainder(char *line)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[1] || !line[i])
		return (NULL);
	tmp = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!tmp[0])
	{
		tmp = NULL;
	}
	line[i + 1] = '\0';
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*remainder;

	buffer = (char *)my_malloc((BUFFER_SIZE + 1) * sizeof(char), 0);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) || !buffer)
	{
		remainder = NULL;
		buffer = NULL;
		return (NULL);
	}
	line = read_line(fd, buffer, remainder);
	buffer = NULL;
	if (!line)
		return (NULL);
	remainder = update_remainder(line);
	return (line);
}
