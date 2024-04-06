/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 10:55:33 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 10:56:13 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	parse_fractional_part(const char **str_ptr, double result, double sign);

double	parse_integer_part(const char **str_ptr)
{
	double	result;
	double	sign;

	result = 0.0;
	sign = 1.0;
	while (**str_ptr == ' ' || **str_ptr == '\t' || **str_ptr == '\n'
		|| **str_ptr == '\v' || **str_ptr == '\f' || **str_ptr == '\r')
	{
		(*str_ptr)++;
	}
	if (**str_ptr == '-')
	{
		sign = -1.0;
		(*str_ptr)++;
	}
	else if (**str_ptr == '+')
	{
		(*str_ptr)++;
	}
	while (**str_ptr >= '0' && **str_ptr <= '9')
	{
		result = (result * 10.0) + (**str_ptr - '0');
		(*str_ptr)++;
	}
	return (parse_fractional_part(str_ptr, result, sign));
}

double	parse_fractional_part(const char **str_ptr, double result, double sign)
{
	double	scale;

	scale = 1.0;
	if (**str_ptr == '.')
	{
		(*str_ptr)++;
		while (**str_ptr >= '0' && **str_ptr <= '9')
		{
			result = (result * 10.0) + (**str_ptr - '0');
			scale *= 10.0;
			(*str_ptr)++;
		}
	}
	return (sign * (result / scale));
}

double	ft_atof(const char *str)
{
	return (parse_integer_part(&str));
}
