/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:27:10 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/01 18:01:17 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	is_shape(t_identifier_type type)
{
	return (type == SPHERE || type == CYLINDER || type == PLANE || type == CONE);
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

static void	set_data_to_zero(t_scene_data *scene_data)
{
	scene_data->shape_count = 0;
	scene_data->shapes = NULL;
	scene_data->initialised.ambient_light = 0;
	scene_data->initialised.camera = 0;
	scene_data->initialised.light = 0;
	scene_data->ambient_light = malloc(sizeof(t_ambient));
	scene_data->ambient_light->color = color(1, 1, 1);
	scene_data->ambient_light->ratio = 0.1;
	scene_data->camera = malloc(sizeof(t_camera));
	// scene_data->camera->position = point(0, 0, 0);
	// scene_data->camera->orientation = vector(0, 1, 0);
	scene_data->light = NULL;
	scene_data->extra_lights = NULL;
}

static int	load_scene_data(t_scene_data *scene_data, int fd)
{
	char	*line;

	set_data_to_zero(scene_data);
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

void	*init_data(t_scene_data *scene_data, int ac, char **av, void *mlx)
{
	int	fd;

	if (invalid_input(ac, av))
		return (NULL);
	scene_data->mlx = mlx;
	fd = open(av[1], O_RDONLY);
	if (load_scene_data(scene_data, fd))
		return (NULL);
	close(fd);
	return ((int *)1);
}
