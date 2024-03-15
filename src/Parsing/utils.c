/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:44:50 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/14 16:34:41 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double	ft_atof(const char *str)
{
	double	result;
	double	sign;
	double	scale;

	result = 0.0;
	sign = 1.0;
	scale = 1.0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
	{
		sign = -1.0;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10.0) + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			result = (result * 10.0) + (*str - '0');
			scale *= 10.0;
			str++;
		}
	}
	return (sign * (result / scale));
}

char	*strdup_upto_whitespace(const char *s)
{
	size_t	len;
	size_t	i;
	char	*result;

	len = 0;
	while (s[len] && s[len] != ' ' && s[len] != '\t')
		len++;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len)
		result[i] = s[i];
	result[i] = '\0';
	return (result);
}

int	skip_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	return (i);
}
