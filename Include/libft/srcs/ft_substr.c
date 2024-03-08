/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:27:28 by svolodin          #+#    #+#             */
/*   Updated: 2023/11/11 17:37:42 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	actual_len;
	size_t	i;

	if (start > ft_strlen(s))
	{
		result = malloc(1);
		result[0] = '\0';
		return (result);
	}
	if (len > ft_strlen(s) - start)
		actual_len = ft_strlen(s) - start;
	else
		actual_len = len;
	result = malloc((actual_len + 1) * sizeof(char));
	i = 0;
	if (!s || !result)
		return (NULL);
	while (s[(size_t)start + i] && (i < len))
	{
		result[i] = s[(size_t)start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
