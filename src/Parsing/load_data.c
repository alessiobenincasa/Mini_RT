/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:27:10 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/13 14:00:38 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

char	*ft_strdup_space(const char *s)
{
	size_t	len;
	size_t	i;
	char	*result;

	len = 0;
	while (s[len] && s[len] != ' ')
		len++;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len)
		result[i] = s[i];
	result[i] = '\0';
	return (result);
}

void parse_coordinates(char *input, t_vector *vec)
{
    char *token;
    int i = 0;

    token = strtok(input, ",");
    while (token != NULL)
    {
        if (i == 0) vec->x = ft_atof(token);
        if (i == 1) vec->y = ft_atof(token);
        if (i == 2) vec->z = ft_atof(token);
        
        token = strtok(NULL, ",");
        i++;
    }
}

void	get_sphere_data(t_scene_data *scene_data, char *line)
{
	char 	*value;
	t_sphere sphere;
	
	sphere = scene_data->sphere;
	while (ft_isalpha(*line) || *line == ' ')
		line++;
	value = ft_strdup_space(line);
	line += ft_strlen(value);
	parse_coordinates(value, &sphere.center);
}

static int	add_to_struct(t_scene_data *scene_data, char *line)
{
	t_identifier_type	type;

	(void)scene_data;
	if (get_identifier(line, &type) != 0)
	{
		error("Unknown identifier encountered");
		return (1);
	}
	print_identifier_type(type);
	if (type == SPHERE)
		get_sphere_data(scene_data, line);
	return (0);
}

static int	load_scene_data(t_scene_data *scene_data, int fd)
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
