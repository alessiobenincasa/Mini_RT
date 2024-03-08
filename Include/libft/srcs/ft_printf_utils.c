/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:43:06 by svolodin          #+#    #+#             */
/*   Updated: 2023/12/06 10:52:39 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pf_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	pf_putstr(char *s)
{
	if (!s)
		return (pf_putstr("(null)"));
	write(1, s, ft_strlen(s));
	return (ft_strlen(s));
}

int	pf_putnbr(int n)
{
	long	num;
	int		count;

	num = n;
	count = 0;
	if (num < 0)
	{
		pf_putchar('-');
		num = -num;
		count++;
	}
	if (num > 9)
	{
		count += pf_putnbr(num / 10);
		count += pf_putnbr(num % 10);
	}
	else
	{
		pf_putchar(num + '0');
		count++;
	}
	return (count);
}

int	pf_unsigned_putnbr(unsigned int n)
{
	int	count;

	count = 0;
	if (n > 9)
	{
		count += pf_unsigned_putnbr(n / 10);
		count += pf_unsigned_putnbr(n % 10);
	}
	else
	{
		pf_putchar(n + '0');
		count++;
	}
	return (count);
}
