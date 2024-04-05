/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifiers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:28:21 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/05 13:56:44 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static char	*extract_identifier(const char *line)
{
	int		i;
	char	*id;

	i = 0;
	while (line[i] != '\t' && line[i] != ' ')
		i++;
	id = ft_calloc(i + 1, sizeof(char));
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

int	assign_type_from_identifier(char *identifier, t_id_type *type)
{
	if (ft_strcmp(identifier, "A") == 0)
		*type = AMBIENT_LIGHT;
	else if (ft_strcmp(identifier, "C") == 0)
		*type = CAMERA;
	else if (ft_strcmp(identifier, "L") == 0)
		*type = LIGHT;
	else if (ft_strcmp(identifier, "L2") == 0)
		*type = EXTRA_LIGHT;
	else if (ft_strcmp(identifier, "sp") == 0)
		*type = SPHERE;
	else if (ft_strcmp(identifier, "cy") == 0)
		*type = CYLINDER;
	else if (ft_strcmp(identifier, "pl") == 0)
		*type = PLANE;
	else if (ft_strcmp(identifier, "co") == 0)
		*type = CONE;
	else
		return (1);
	return (0);
}

int	get_identifier(char **line, t_id_type *type, t_scene_data *scene_data)
{
	char	*identifier;

	identifier = extract_identifier(*line);
	if (!identifier)
		return (error("Unknown type identifier"), 1);
	if (assign_type_from_identifier(identifier, type))
		return (free(identifier), 1);
	if (is_shape(*type))
		(scene_data->shape_count)++;
	*line += ft_strlen(identifier);
	*line += skip_spaces(*line);
	return (free(identifier), 0);
}
