/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:38:52 by svolodin          #+#    #+#             */
/*   Updated: 2023/12/11 11:09:32 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	needle_len;
	size_t	i;
	size_t	j;

	if (!needle[0])
		return ((char *)haystack);
	if (len == 0)
		return (0);
	needle_len = ft_strlen(needle);
	i = 0;
	while (haystack[i] && i <= len - needle_len)
	{
		j = 0;
		while (needle[j] && needle[j] == haystack[i + j])
		{
			if (j == needle_len - 1)
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
