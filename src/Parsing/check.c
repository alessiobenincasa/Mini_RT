/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:32:00 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/03 14:03:34 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	error(char *str)
{
	int	i;

	i = -1;
	write(2, RED, ft_strlen(RED));
	while (str[++i])
		write(2, &str[i], 1);
	write(2, RESET, ft_strlen(RESET));
	write(2, "\n", 2);
}

int	invalid_input(int ac, char **av)
{
	int		fd;
	char	*dot;

	if (ac != 2)
	{
		error("Invalid amount of arguments given");
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		error("Can't open file, or file doesn't exist");
		return (3);
	}
	dot = ft_strchr(av[1], '.');
	if (!dot || ft_strcmp(dot + 1, "rt") != 0)
	{
		error("File is not of type .rt");
		return (2);
	}
	close(fd);
	return (0);
}
