/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:44:50 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/06 10:55:13 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

char	*strdup_upto_whitespace(const char *s)
{
	size_t	len;
	size_t	i;
	char	*result;

	len = 0;
	while (s[len] && s[len] != ' ' && s[len] != '\t')
		len++;
	if (len == 0)
		return (NULL);
	result = ft_calloc(len + 1, sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len)
		result[i] = s[i];
	result[i] = '\0';
	return (result);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}

void	get_next_value(char **value, char **line)
{
	*value = strdup_upto_whitespace(*line);
	if (*value && **value)
	{
		*line += ft_strlen(*value);
		*line += skip_spaces(*line);
	}
	if (!*value && **line == '\0')
	{
		if (*value)
			free(*value);
		*value = NULL;
	}
}
