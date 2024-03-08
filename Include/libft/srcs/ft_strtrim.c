/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:48:09 by svolodin          #+#    #+#             */
/*   Updated: 2023/11/12 10:55:56 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	char_in_set(char const *set, size_t set_len, char c)
{
	size_t	i;

	i = -1;
	while (++i < set_len)
	{
		if (c == set[i])
			return (1);
	}
	return (0);
}

size_t	get_b_cut(char const *set, char const *s1, size_t set_len)
{
	size_t	i;
	size_t	b_cut;

	i = -1;
	b_cut = 0;
	while (char_in_set(set, set_len, s1[++i]))
		b_cut++;
	return (b_cut);
}

size_t	get_e_cut(char const *set, char const *s1, size_t set_len)
{
	size_t	i;
	size_t	e_cut;

	i = ft_strlen(s1) - 1;
	e_cut = 0;
	while (char_in_set(set, set_len, s1[i--]))
		e_cut++;
	return (e_cut);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	b_cut;
	size_t	e_cut;
	char	*result;

	b_cut = get_b_cut(set, s1, ft_strlen(set));
	e_cut = get_e_cut(set, s1, ft_strlen(set));
	if ((b_cut + e_cut) >= ft_strlen(s1))
	{
		result = malloc(1);
		result[0] = '\0';
		return (result);
	}
	result = malloc((ft_strlen(s1) - (b_cut + e_cut) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = b_cut - 1;
	j = 0;
	while (++i < (ft_strlen(s1) - e_cut))
		result[j++] = s1[i];
	result[j] = '\0';
	return (result);
}
