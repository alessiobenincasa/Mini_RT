/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:44:50 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/12 16:40:57 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double	ft_ft_atof(const char *str)
{
	double	result;
	double	sign;
	double	scale;

	result = 0.0;
	sign = 1.0;
	scale = 1.0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
	{
		sign = -1.0;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		result = (result * 10.0) + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			result = (result * 10.0) + (*str - '0');
			scale *= 10.0;
			str++;
		}
	}
	return (sign * (result / scale));
}

void	parse_scene(char *filename)
{
	FILE *file;
	char *line;
	int fd;
	char identifier[3];
	t_ambient ambient;
	t_camera camera;
	t_light light;
	t_sphere sphere;
	t_plane plane;
	t_cylinder cylinder;
	char **words;

	file = open(filename, "r");
	if (fd == -1)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		words = ft_split(line, ' ');
		if (words[0] != NULL)
		{
			if (ft_strcmp(words[0], "A") == 0)
			{
				if (words_count(words) >= 4)
				{
					ambient.ratio = ft_ft_atof(words[1]);
					ambient.color.r = ft_ft_atoi(words[2]);
					ambient.color.g = ft_ft_atoi(words[3]);
					ambient.color.b = ft_ft_atoi(words[4]);
				}
			}
			else if (ft_strcmp(words[0], "C") == 0)
			{
				if (words_count(words) >= 8)
				{
					camera.origin.x = ft_ft_atof(words[1]);
					camera.origin.y = ft_ft_atof(words[2]);
					camera.origin.z = ft_ft_atof(words[3]);
					camera.direction.x = ft_ft_atof(words[4]);
					camera.direction.y = ft_ft_atof(words[5]);
					camera.direction.z = ft_ft_atof(words[6]);
					camera.fov = ft_ft_atoi(words[7]);
				}
			}
			else if (ft_strcmp(words[0], "L") == 0)
			{
				if (words_count(words) >= 7)
				{
					light.position.x = ft_atof(words[1]);
					light.position.y = ft_atof(words[2]);
					light.position.z = ft_atof(words[3]);
					light.intensity = ft_atof(words[4]);
					light.color.r = ft_atoi(words[5]);
					light.color.g = ft_atoi(words[6]);
					light.color.b = ft_atoi(words[7]);
				}
			}
		}
		else if (ft_strcmp(words[0], "sp") == 0)
			if (words_count(words) >= 6)

			{
				sphere.center.x = ft_atof(words[1]);
				sphere.center.y = ft_atof(words[2]);
				sphere.center.z = ft_atof(words[3]);
				sphere.diameter = ft_atof(words[4]);
				sphere.color.r = ft_atoi(words[5]);
				sphere.color.g = ft_atoi(words[6]);
				sphere.color.b = ft_atoi(words[7]);
			}
			else if (ft_strcmp(words[0], "pl") == 0)
			{
				if (words_count(words) >= 9)

				{
					plane.point.x = ft_atof(words[1]);
					plane.point.y = ft_atof(words[2]);
					plane.point.z = ft_atof(words[3]);
					plane.normal.x = ft_atof(words[4]);
					plane.normal.y = ft_atof(words[5]);
					plane.normal.z = ft_atof(words[6]);
					plane.color.r = ft_atoi(words[7]);
					plane.color.g = ft_atoi(words[8]);
					plane.color.b = ft_atoi(words[9]);
				}
			}
			else if (ft_strcmp(words[0], "cy") == 0)
			{
				if (words_count(words) >= 11)

				{
					cylinder.position.x = ft_atof(words[1]);
					cylinder.position.y = ft_atof(words[2]);
					cylinder.position.z = ft_atof(words[3]);
					cylinder.direction.x = ft_atof(words[4]);
					cylinder.direction.y = ft_atof(words[5]);
					cylinder.direction.z = ft_atof(words[6]);

					free_double_array(words);
				}
			}
		fclose(file);
	}
