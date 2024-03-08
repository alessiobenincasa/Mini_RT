/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:32:16 by svolodin          #+#    #+#             */
/*   Updated: 2023/11/11 14:38:06 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	if (!dst && !src)
		return (0);
	src_len = ft_strlen(src);
	if (dstsize < 1)
		return (src_len);
	dst_len = ft_strlen((const char *)dst);
	i = 0;
	if (dstsize <= dst_len)
		return (dstsize + src_len);
	while (src[i] && ((dst_len + i) < (dstsize - 1)))
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	if ((dst_len + i) < dstsize)
		dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}
