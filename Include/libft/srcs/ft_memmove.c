/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 08:42:01 by svolodin          #+#    #+#             */
/*   Updated: 2023/11/10 16:25:13 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*src_ptr;
	unsigned char		*dest_ptr;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	src_ptr = (const unsigned char *)src;
	dest_ptr = (unsigned char *)dest;
	i = -1;
	if (dest_ptr < src_ptr)
	{
		while (++i < n)
			dest_ptr[i] = src_ptr[i];
	}
	else
	{
		while (n-- > 0)
			dest_ptr[n] = src_ptr[n];
	}
	return (dest);
}
