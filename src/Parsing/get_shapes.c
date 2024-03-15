/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:18:39 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/15 16:53:50 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	check_coordinates(t_vector vec)
{
	if (vec.x < -1 || vec.x > 1)
		return (1);
	else if (vec.y < -1 || vec.y > 1)
		return (2);
	else if (vec.z < -1 || vec.z > 1)
		return (3);
	return (0);
}

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
	if (parse_colors(value, sphere->color) != 0)
	{
		free(value);
		return (error("RGB Colors for Sphere are incorrect"), NULL);
	}
	free(value);
	return (sphere);
}

t_plane	*get_plane_data(char *line)
{
	char	*value;
	t_plane	*plane;

	plane = malloc(sizeof(t_plane));
	value = strdup_upto_whitespace(line);
	line += ft_strlen(value);
	line += skip_spaces(line);
	parse_coordinates(value, &(plane->point));
	free(value);
	value = strdup_upto_whitespace(line);
	line += ft_strlen(value);
	line += skip_spaces(line);
	parse_coordinates(value, &(plane->normal));
	free(value);
	if (check_coordinates(plane->normal) != 0)
		return (error("Plane normalized vector value incorrect"), NULL);
	value = strdup_upto_whitespace(line);
	if (parse_colors(value, plane->color) != 0)
	{
		free(value);
		return (error("RGB Colors for Plane are incorrect"), NULL);
	}
	free(value);
	return (plane);
}

t_cylinder	*get_cylinder_data(char *line)
{
	char		*value;
	t_cylinder	*cylinder;

	cylinder = malloc(sizeof(t_cylinder));
	value = strdup_upto_whitespace(line);
	line += ft_strlen(value);
	line += skip_spaces(line);
	parse_coordinates(value, &(cylinder->center));
	free(value);
	value = strdup_upto_whitespace(line);
	line += ft_strlen(value);
	line += skip_spaces(line);
	parse_coordinates(value, &(cylinder->direction));
	free(value);
	if (check_coordinates(cylinder->direction) != 0)
		return (error("Plane normalized vector value incorrect"), NULL);
	value = strdup_upto_whitespace(line);
	line += ft_strlen(value);
	line += skip_spaces(line);
	cylinder->diameter = ft_atof(value);
	free(value);
	value = strdup_upto_whitespace(line);
	line += ft_strlen(value);
	line += skip_spaces(line);
	cylinder->height = ft_atof(value);
	free(value);
	value = strdup_upto_whitespace(line);
	if (parse_colors(value, cylinder->color) != 0)
	{
		free(value);
		return (error("RGB Colors for Plane are incorrect"), NULL);
	}
	free(value);
	return (cylinder);
}
