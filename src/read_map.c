/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:02:57 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/08 00:11:12 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_scene(char *filename)
{
	FILE		*file;
	char		line[1024];
	char		identifier[3];
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;

	file = fopen(filename, "r");
	if (!file)
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	while (fgets(line, sizeof(line), file))
	{
		if (sscanf(line, "%2s", identifier) == 1)
		{
			if (ft_strcmp(identifier, "A") == 0)
			{
			}
			else if (ft_strcmp(identifier, "C") == 0)
			{
			}
			else if (ft_strcmp(identifier, "L") == 0)
			{
			}
			else if (ft_strcmp(identifier, "sp") == 0)
			{
			}
			else if (ft_strcmp(identifier, "pl") == 0)
			{
			}
			else if (ft_strcmp(identifier, "cy") == 0)
			{
			}
		}
	}
	fclose(file);
}
