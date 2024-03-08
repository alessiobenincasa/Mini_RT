/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:45:38 by svolodin          #+#    #+#             */
/*   Updated: 2023/12/10 14:55:30 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	print_reverse(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = ft_strlen(str);
	while (i--)
	{
		pf_putchar(str[i]);
		count++;
	}
	return (count);
}

int	pf_print_hex(unsigned long long n, int upr_case)
{
	unsigned long long	remainder;
	char				hex_val[9];
	char				*low_hex;
	char				*high_hex;
	int					i;

	ft_bzero(hex_val, 9);
	i = 0;
	low_hex = "0123456789abcdef";
	high_hex = "0123456789ABCDEF";
	if (n == 0)
		return (pf_putchar('0'));
	while (n > 0)
	{
		remainder = n % 16;
		if (upr_case)
			hex_val[i++] = high_hex[remainder];
		else
			hex_val[i++] = low_hex[remainder];
		n /= 16;
	}
	return (print_reverse(hex_val));
}

int	pf_putptr(unsigned long long n)
{
	char	*base;
	int		count;

	count = 0;
	base = "0123456789abcdef";
	if (n < 16)
	{
		pf_putchar(base[n]);
		return (1);
	}
	else
	{
		count += pf_putptr(n / 16);
		pf_putchar(base[n % 16]);
		return (count + 1);
	}
}

int	pf_print_pointer(unsigned long long n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (pf_putstr("(nil)"));
	count += pf_putstr("0x");
	count += pf_putptr(n);
	return (count);
}
