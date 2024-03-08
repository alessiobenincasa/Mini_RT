/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:26:32 by svolodin          #+#    #+#             */
/*   Updated: 2023/11/11 14:04:33 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	total_len;
	size_t	i;
	size_t	j;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	result = malloc((total_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (++i < ft_strlen(s1))
		result[i] = s1[i];
	while (i < total_len)
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}
