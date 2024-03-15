/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:13:29 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/14 16:25:53 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_coordinates(char *input, t_vector *vec)
{
	char	*token;
	int		i;

	i = 0;
	token = ft_strtok(input, ',');
	while (token != NULL)
	{
		if (i == 0)
			vec->x = ft_atof(token);
		if (i == 1)
			vec->y = ft_atof(token);
		if (i == 2)
			vec->z = ft_atof(token);
		token = ft_strtok(NULL, ',');
		i++;
	}
}

int	parse_colors(char *input, int colors[3])
{
	char	*token;
	int		i;

	i = 0;
	token = ft_strtok(input, ',');
	while (token != NULL)
	{
		if (i == 0)
			colors[0] = ft_atoi(token);
		if (i == 1)
			colors[1] = ft_atoi(token);
		if (i == 2)
			colors[2] = ft_atoi(token);
		token = ft_strtok(NULL, ',');
		i++;
	}
	if (colors[0] < 0 || colors[0] > 255)
		return (1);
	else if (colors[1] < 0 || colors[1] > 255)
		return (2);
	else if (colors[2] < 0 || colors[2] > 255)
		return (3);
	return (0);
}
