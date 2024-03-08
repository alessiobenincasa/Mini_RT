/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 18:06:27 by svolodin          #+#    #+#             */
/*   Updated: 2024/02/05 18:06:38 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	char	*ptr;

	ptr = dest + ft_strlen(dest);
	while (*src != '\0' && n--)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dest);
}
