/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shapes_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:11:43 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/14 14:21:02 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	add_sphere_to_list(t_scene_data *scene_data, char *line)
{
	t_sphere 	*sphere;
	t_list		*new_node;
	
	sphere = get_sphere_data(line);
	if (!sphere)
		return (1);
	new_node = ft_lstnew(sphere);
	if (!new_node)
		return (free(sphere), 1);
	if (scene_data->shapes == NULL)
		scene_data->shapes = new_node;
	else
		ft_lstadd_back(&(scene_data->shapes), new_node);
	return (0);
}

int	add_shape_data(t_identifier_type type, t_scene_data *scene_data, char *line)
{
	if (type == SPHERE)
	{
		if (add_sphere_to_list(scene_data, line) != 0)
			return (error("Failed to add sphere"), 1);
    }
	return (0);
}
