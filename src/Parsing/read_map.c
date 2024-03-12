/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 17:44:50 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/12 17:19:43 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double	ft_atof(const char *str)
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
/*
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
					ambient.ratio = atof(words[1]);
					ambient.color.r = atoi(words[2]);
					ambient.color.g = atoi(words[3]);
					ambient.color.b = atoi(words[4]);
				}
			}
			else if (ft_strcmp(words[0], "C") == 0)
			{
				if (words_count(words) >= 8)
				{
					camera.origin.x = atof(words[1]);
					camera.origin.y = atof(words[2]);
					camera.origin.z = atof(words[3]);
					camera.direction.x = atof(words[4]);
					camera.direction.y = atof(words[5]);
					camera.direction.z = atof(words[6]);
					camera.fov = atoi(words[7]);
				}
			}
			else if (ft_strcmp(words[0], "L") == 0)
			{
				if (words_count(words) >= 7)
				{
					light.position.x = atof(words[1]);
					light.position.y = atof(words[2]);
					light.position.z = atof(words[3]);
					light.intensity = atof(words[4]);
					light.color.r = atoi(words[5]);
					light.color.g = atoi(words[6]);
					light.color.b = atoi(words[7]);
				}
			}
		}
		else if (ft_strcmp(words[0], "sp") == 0)
			if (words_count(words) >= 6)

			{
				sphere.center.x = atof(words[1]);
				sphere.center.y = atof(words[2]);
				sphere.center.z = atof(words[3]);
				sphere.diameter = atof(words[4]);
				sphere.color.r = atoi(words[5]);
				sphere.color.g = atoi(words[6]);
				sphere.color.b = atoi(words[7]);
			}
			else if (ft_strcmp(words[0], "pl") == 0)
			{
				if (words_count(words) >= 9)

				{
					plane.point.x = atof(words[1]);
					plane.point.y = atof(words[2]);
					plane.point.z = atof(words[3]);
					plane.normal.x = atof(words[4]);
					plane.normal.y = atof(words[5]);
					plane.normal.z = atof(words[6]);
					plane.color.r = atoi(words[7]);
					plane.color.g = atoi(words[8]);
					plane.color.b = atoi(words[9]);
				}
			}
			else if (ft_strcmp(words[0], "cy") == 0)
			{
				if (words_count(words) >= 11)

				{
					cylinder.position.x = atof(words[1]);
					cylinder.position.y = atof(words[2]);
					cylinder.position.z = atof(words[3]);
					cylinder.direction.x = atof(words[4]);
					cylinder.direction.y = atof(words[5]);
					cylinder.direction.z = atof(words[6]);

					free_double_array(words);
				}
			}
		fclose(file);
	}
*/