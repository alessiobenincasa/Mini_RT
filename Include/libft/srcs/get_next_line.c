/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 09:40:41 by svolodin          #+#    #+#             */
/*   Updated: 2023/12/17 16:31:52 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*set_next(char *stat_buf)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	while (stat_buf[i] && stat_buf[i] != '\n')
		i++;
	if (!stat_buf[i])
	{
		free(stat_buf);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(stat_buf) - i + 1), sizeof(char));
	if (!line)
		return (NULL);
	i++;
	while (stat_buf[i])
		line[j++] = stat_buf[i++];
	free(stat_buf);
	return (line);
}

static char	*make_line(char *stat_buf)
{
	char	*line;
	size_t	i;

	i = 0;
	if (!stat_buf[0])
		return (NULL);
	while (stat_buf[i] && stat_buf[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = -1;
	while (stat_buf[++i] && stat_buf[i] != '\n')
		line[i] = stat_buf[i];
	if (stat_buf[i] && stat_buf[i] == '\n')
		line[i] = '\n';
	return (line);
}

static char	*join_and_free(char *stat_buf, char *temp_buf)
{
	char	*temp;

	temp = ft_strjoin(stat_buf, temp_buf);
	free(stat_buf);
	return (temp);
}

static char	*ft_read(int fd, char *stat_buf)
{
	char	*temp;
	int		bytes_size;

	if (!stat_buf)
		stat_buf = ft_calloc(1, sizeof(char));
	temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes_size = 1;
	while (bytes_size > 0)
	{
		bytes_size = read(fd, temp, BUFFER_SIZE);
		if (bytes_size == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[bytes_size] = '\0';
		stat_buf = join_and_free(stat_buf, temp);
		if (ft_strchr(stat_buf, '\n'))
			break ;
	}
	free(temp);
	return (stat_buf);
}

char	*get_next_line(int fd)
{
	static char	*stat_buf;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	stat_buf = ft_read(fd, stat_buf);
	if (!stat_buf)
		return (NULL);
	line = make_line(stat_buf);
	stat_buf = set_next(stat_buf);
	return (line);
}
