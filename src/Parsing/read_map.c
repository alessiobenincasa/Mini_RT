/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:02:57 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/08 17:20:03 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	parse_scene(char *filename)
{
	FILE		*file;
	char		*line;
	int			fd;
	char		identifier[3];
	t_ambient	ambient;
	t_camera	camera;
	t_light		light;
	t_sphere	sphere;
	t_plane		plane;
	t_cylinder	cylinder;
	char		**words;

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
			}
			else if (ft_strcmp(words[0], "C") == 0)
			{
			}
			else if (ft_strcmp(words[0], "L") == 0)
			{
			}
			else if (ft_strcmp(words[0], "sp") == 0)
			{
			}
			else if (ft_strcmp(words[0], "pl") == 0)
			{
			}
			else if (ft_strcmp(words[0], "cy") == 0)
			{
			}
			free_double_array(words);
		}
	}
	fclose(file);
}
