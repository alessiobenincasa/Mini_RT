/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:47 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/08 00:05:05 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	strcmp_fdf(char *a)
{
	int		i;
	int		j;
	char	*b;

	b = ".fdf";
	i = 0;
	j = -1;
	while (a[i] != 0)
		i++;
	i -= 5;
	while (a[++i] != 0)
	{
		if (a[i] != b[++j])
			return (0);
	}
	return (1);
}

void	free_split(char **temp, int opt, t_vars *vars)
{
	int	i;

	if (opt == 1)
	{
		write (1, "Detected a non-digit!\n", 22);
		ft_close (vars);
	}
	if (opt == 2)
	{
		i = 0;
		while (temp[i])
			free(temp[i++]);
		free(temp);
	}
}
