/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:00:30 by svolodin          #+#    #+#             */
/*   Updated: 2023/11/09 09:45:14 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = -1;
	len = ft_strlen(src);
	if (dstsize < 1)
		return (len);
	while ((++i < dstsize - 1) && src[i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (len);
}
