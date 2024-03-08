/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 10:53:08 by svolodin          #+#    #+#             */
/*   Updated: 2023/11/13 10:51:36 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_len(long n)
{
	int	len;

	len = 1;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*reverse(char *str, int len)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = len - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
	return (str);
}

char	*to_char(long n, int len, int neg)
{
	char	*result;
	int		i;

	result = ft_calloc((size_t)(len + 1), sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (n > 0)
	{
		result[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (neg)
		result[i++] = '-';
	result = reverse(result, len);
	return (result);
}

char	*ft_itoa(int n)
{
	int		is_neg;
	int		len;
	char	*result;
	long	num;

	num = n;
	if (num == 0)
		return (ft_strdup("0"));
	is_neg = 0;
	if (num < 0)
	{
		is_neg = 1;
		num *= -1;
	}
	len = get_len(num);
	if (is_neg)
		len++;
	result = to_char(num, len, is_neg);
	return (result);
}
