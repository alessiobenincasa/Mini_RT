/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspecial.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 21:43:35 by albeninc          #+#    #+#             */
/*   Updated: 2024/02/17 21:43:38 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isspecial(char symbol)
{
	char	*special_symbols;
	int		i;

	i = 0;
	special_symbols = "!\"#$%&'()*+,-./:;<=>?@[\\]^`{|}~";
	while (special_symbols[i])
	{
		if (symbol == special_symbols[i])
			return (1);
		i++;
	}
	return (0);
}
