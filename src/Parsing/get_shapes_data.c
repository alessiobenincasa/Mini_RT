/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shapes_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:18:39 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/14 09:18:59 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	get_sphere_data(t_scene_data *scene_data, char *line)
{
	char		*value;
	
	while (ft_isalpha(*line))
		line++;
	line += skip_spaces(line);
	value = strdup_upto_whitespace(line);
	line += ft_strlen(value);
	parse_coordinates(value, &(scene_data->sphere.center));
	free(value);
	line += skip_spaces(line);
	value = strdup_upto_whitespace(line);
	scene_data->sphere.diameter = ft_atof(value);
	line += ft_strlen(value);
	free(value);
	line += skip_spaces(line);
	value = strdup_upto_whitespace(line);
	parse_colors(value, scene_data->sphere.color);
	free(value);
	printf("Data about Sphere:\nVectors: %lf, %lf, %lf\n",
		scene_data->sphere.center.x, scene_data->sphere.center.y,
		scene_data->sphere.center.z);
	printf("Diameter : %lf\n", scene_data->sphere.diameter);
	printf("Colors : %d, %d, %d\n", scene_data->sphere.color[0],
		scene_data->sphere.color[1], scene_data->sphere.color[2]);
}
