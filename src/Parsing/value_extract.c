/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:13:29 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/25 14:30:30 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_coordinates(char *input, t_tuple *vec)
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
	vec->w = 0;
}

static void	convert_rgb_to_one(t_color *color)
{
	if (color != NULL)
	{
		color->red /= 255;
		color->green /= 255;
		color->blue /= 255;
	}
}

int	parse_colors(char *input, t_color *colors)
{
	char	*token;
	int		i;

	i = 0;
	token = ft_strtok(input, ',');
	while (token != NULL)
	{
		if (i == 0)
			colors->red = ft_atoi(token);
		if (i == 1)
			colors->blue = ft_atoi(token);
		if (i == 2)
			colors->green = ft_atoi(token);
		token = ft_strtok(NULL, ',');
		i++;
	}
	if (colors->red < 0 || colors->red > 255)
		return (1);
	else if (colors->blue || colors->blue > 255)
		return (2);
	else if (colors->green < 0 || colors->green > 255)
		return (3);
	convert_rgb_to_one(colors);
	return (0);
}
