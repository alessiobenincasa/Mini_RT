/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:13:29 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/27 15:14:39 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	initialize_tuple(t_tuple *tuple)
{
	if (tuple != NULL)
	{
		tuple->x = 0.0;
		tuple->y = 0.0;
		tuple->z = 0.0;
		tuple->w = 0.0;
	}
}

void	parse_coordinates(char *input, t_tuple *vec)
{
	char	*token;
	int		i;

	i = 0;
	initialize_tuple(vec);
	token = strtok(input, ",");
	while (token != NULL)
	{
		if (i == 0)
			vec->x = ft_atof(token);
		if (i == 1)
			vec->y = ft_atof(token);
		if (i == 2)
			vec->z = ft_atof(token);
		token = strtok(NULL, ",");
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
	token = strtok(input, ",");
	while (token != NULL)
	{
		if (i == 0)
			colors->red = ft_atoi(token);
		if (i == 1)
			colors->green = ft_atoi(token);
		if (i == 2)
			colors->blue = ft_atoi(token);
		token = strtok(NULL, ",");
		i++;
	}
	if (colors->red < 0.0 || colors->red > 255.0)
		return (1);
	else if (colors->green < 0.0 || colors->green > 255.0)
		return (2);
	else if (colors->blue < 0.0 || colors->blue > 255.0)
		return (3);
	convert_rgb_to_one(colors);
	return (0);
}
