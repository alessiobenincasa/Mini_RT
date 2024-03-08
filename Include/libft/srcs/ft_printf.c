/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 10:38:24 by svolodin          #+#    #+#             */
/*   Updated: 2023/12/27 12:15:07 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	format_specifier(char c, va_list args)
{
	if (c == '%')
		return (pf_putchar('%'));
	if (c == 'c')
		return (pf_putchar(va_arg(args, int)));
	if (c == 's')
		return (pf_putstr(va_arg(args, char *)));
	if (c == 'd' || c == 'i')
		return (pf_putnbr(va_arg(args, int)));
	if (c == 'u')
		return (pf_unsigned_putnbr(va_arg(args, unsigned int)));
	if (c == 'x')
		return (pf_print_hex(va_arg(args, unsigned int), 0));
	if (c == 'X')
		return (pf_print_hex(va_arg(args, unsigned int), 1));
	if (c == 'p')
		return (pf_print_pointer(va_arg(args, unsigned long long)));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	size_t	i;
	size_t	char_count;

	va_start(args, s);
	i = -1;
	char_count = 0;
	while (s[++i])
	{
		if (s[i] == '%')
			char_count += format_specifier(s[++i], args);
		else
			char_count += pf_putchar(s[i]);
	}
	va_end(args);
	return (char_count);
}
