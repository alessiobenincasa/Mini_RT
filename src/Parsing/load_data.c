/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:27:10 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/14 14:59:06 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	is_shape(t_identifier_type type)
{
	return (type == SPHERE || type == CYLINDER || type == PLANE);
}

int	orientation_incorrect(t_vector orientation)
{
	if (orientation.x < -1 || orientation.x > 1)
		return (1);
	else if (orientation.y < -1 || orientation.y > 1)
		return (2);
	else if (orientation.z < -1 || orientation.z > 1)
		return (3);
	return (0);
}

int	add_camera_to_list(t_scene_data *scene_data, char *line)
{
	char	*value;

	value = strdup_upto_whitespace(line);
	parse_coordinates(value, &(scene_data->camera.position));
	line += ft_strlen(value);
	line += skip_spaces(line);
	free(value);
	value = strdup_upto_whitespace(line);
	parse_coordinates(value, &(scene_data->camera.orientation));
	line += ft_strlen(value);
	line += skip_spaces(line);
	free(value);
	if (orientation_incorrect(scene_data->camera.orientation))
		return (error("Orientation Incorrect"), 1);
	value = strdup_upto_whitespace(line);
	scene_data->camera.fov = ft_atof(value);
	if (scene_data->camera.fov < 0 || scene_data->camera.fov > 180)
		return (error("FOV Incorrect"), 1);
	return (0);
}

int	add_capital_element(t_identifier_type type, t_scene_data *scene_data,
		char *line)
{
	if (type == CAMERA)
	{
		if (add_camera_to_list(scene_data, line) != 0)
			return (error("Failed to add camera to list"), 1);
		print_camera(&(scene_data->camera));
	}
	return (0);
}

static int	add_to_struct(t_scene_data *scene_data, char *line)
{
	t_identifier_type	type;

	if (get_identifier(&line, &type, scene_data) != 0)
	{
		error("Unknown identifier encountered");
		return (1);
	}
	print_identifier_type(type);
	if (is_shape(type))
	{
		if (add_shape_data(type, scene_data, line) != 0)
			return (error("Problem adding shape to list"), 1);
		return (0);
	}
	if (add_capital_element(type, scene_data, line) != 0)
		return (error("Problem adding capital element to list"), 1);
	return (0);
}

static int	load_scene_data(t_scene_data *scene_data, int fd)
{
	char	*line;

	scene_data->shape_count = 0;
	scene_data->shapes = NULL;
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (add_to_struct(scene_data, line))
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

void	*init_data(t_scene_data *scene_data, int ac, char **av)
{
	int	fd;

	if (invalid_input(ac, av))
		return (NULL);
	fd = open(av[1], O_RDONLY);
	if (load_scene_data(scene_data, fd))
		return (NULL);
	close(fd);
	return ((int *)1);
}
