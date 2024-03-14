/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shapes_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:18:39 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/14 14:37:10 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_sphere	*get_sphere_data(char *line)
{
	char		*value;
	t_sphere	*sphere;

	sphere = malloc(sizeof(t_sphere));
	value = strdup_upto_whitespace(line);
	line += ft_strlen(value);
	parse_coordinates(value, &(sphere->center));
	free(value);
	line += skip_spaces(line);
	value = strdup_upto_whitespace(line);
	sphere->diameter = ft_atof(value);
	line += ft_strlen(value);
	free(value);
	line += skip_spaces(line);
	value = strdup_upto_whitespace(line);
	parse_colors(value, sphere->color);
	free(value);

	return (sphere);
}
