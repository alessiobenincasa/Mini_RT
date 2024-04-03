/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_lights.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:13:13 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/03 14:03:34 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static t_light	*get_extra_light(char *line)
{
	t_light	*l;
	char	*value;

	l = initialize_scene_light();
	if (!l)
		return (NULL);
	value = NULL;
	if (get_coordinates(value, &line, &(l->position)))
		return (free(l), error("Problem getting coordinates"), NULL);
	if (get_float_val(value, &line, &(l->energy)))
		return (free(l), error("Problem getting energy"), NULL);
	if (l->energy < 0 || l->energy > 1)
		return (free(l), error("Light intensity value incorrect"), NULL);
	if (parse_colors(value, &line, &(l->intensity)) != 0)
		return (free(l), error("Incorrect RGB values for light"), NULL);
	return (l);
}

int	add_extra_light(t_scene_data *scene_data, char *line)
{
	t_light	*light;
	t_list	*new_node;

	light = get_extra_light(line);
	if (!light)
		return (error("failed to get extra lights data"), 1);
	new_node = ft_lstnew(light);
	if (!new_node)
		return (free(light), 1);
	new_node->type = EXTRA_LIGHT;
	if (!scene_data->extra_lights)
		scene_data->extra_lights = new_node;
	else
		ft_lstadd_back(&(scene_data->extra_lights), new_node);
	return (0);
}
