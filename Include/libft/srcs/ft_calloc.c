/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:41:21 by svolodin          #+#    #+#             */
/*   Updated: 2023/11/13 10:49:52 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	size_t	total_size;
	size_t	i;
	void	*allocated_memory;

	if (nitems < 1 || size < 1)
	{
		allocated_memory = malloc(1);
		return (allocated_memory);
	}
	total_size = nitems * size;
	if (nitems == 0 || (total_size / nitems) != size)
		return (NULL);
	allocated_memory = malloc(total_size);
	if (!allocated_memory)
		return (NULL);
	i = -1;
	while (++i < total_size)
		((unsigned char *)allocated_memory)[i] = 0;
	return (allocated_memory);
}
