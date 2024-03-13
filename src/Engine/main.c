/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:17:19 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/13 13:15:25 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_light	light = {.position = {-40.0, 50.0, 0.0}, .intensity = 0.6, .color = {10,
		0, 255}};

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

char	*extract_identifier(const char *line)
{
	int		i;
	char	*id;

	i = 0;
	while (line[i] != '\t' && line[i] != ' ')
		i++;
	id = malloc(sizeof(char) * i + 1);
	if (!id)
		return (NULL);
	i = 0;
	while (line[i] != '\t' && line[i] != ' ')
	{
		id[i] = line[i];
		i++;
	}
	id[i] = '\0';
	return (id);
}

int	get_identifier(char *line, t_identifier_type *type)
{
	char	*identifier;

	(void)type;
	identifier = extract_identifier(line);
	if (!identifier)
	{
		error("Unknown type identifier");
		return (1);
	}
	if (ft_strcmp(identifier, "A") == 0)
		*type = AMBIENT_LIGHT;
	else if (ft_strcmp(identifier, "C") == 0)
		*type = CAMERA;
	else if (ft_strcmp(identifier, "L") == 0)
		*type = LIGHT;
	else if (ft_strcmp(identifier, "sp") == 0)
		*type = SPHERE;
	else if (ft_strcmp(identifier, "cy") == 0)
		*type = CYLINDER;
	else if (ft_strcmp(identifier, "pl") == 0)
		*type = PLANE;
	else
		return (free(identifier), 1);
	return (free(identifier), 0);
}

void print_identifier_type(t_identifier_type type)
{
	printf("--> Identifier is : ");
    if (type == AMBIENT_LIGHT) {
        printf("AMBIENT_LIGHT\n");
    } else if (type == CAMERA) {
        printf("CAMERA\n");
    } else if (type == LIGHT) {
        printf("LIGHT\n");
    } else if (type == SPHERE) {
        printf("SPHERE\n");
    } else if (type == PLANE) {
        printf("PLANE\n");
    } else if (type == CYLINDER) {
        printf("CYLINDER\n");
    } else {
        printf("Unknown type\n");
    }
}

int	add_to_struct(t_scene_data *scene_data, char *line)
{
	t_identifier_type	type;

	(void)scene_data;
	if (get_identifier(line, &type) != 0)
	{
		error("Unknown identifier encountered");
		return (1);
	}
	print_identifier_type(type);
	return (0);
}

int	load_scene_data(t_scene_data *scene_data, int fd)
{
	char	*line;

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
		if (add_to_struct(scene_data, line) != 0)
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
	return ((int *)0);
}

int	main(int ac, char **av)
{
	t_vars			vars;
	t_scene_data	scene_data;

	if (init_data(&scene_data, ac, av) == NULL)
		return (1);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "MiniRT");
	vars.img.img_ptr = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img_ptr,
			&vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	// render(&vars, sphere, light);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
