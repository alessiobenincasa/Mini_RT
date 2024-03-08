/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:44:11 by svolodin          #+#    #+#             */
/*   Updated: 2023/11/09 09:46:04 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*byte_ptr;
	unsigned char		char_to_find;
	size_t				i;

	i = -1;
	byte_ptr = (const unsigned char *)s;
	char_to_find = (unsigned char)c;
	while (++i < n)
	{
		if (byte_ptr[i] == char_to_find)
			return ((void *)(byte_ptr + i));
	}
	return (NULL);
}
