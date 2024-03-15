/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:11:43 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/15 09:50:42 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	add_shape_to_list(t_scene_data *scene_data, t_list *new_node)
{
	if (scene_data->shapes == NULL)
		scene_data->shapes = new_node;
	else
		ft_lstadd_back(&(scene_data->shapes), new_node);
}

int	check_coordinates(t_vector vec)
{
	if (vec.x < -1 || vec.x > 1)
		return (1);
	else if (vec.y < -1 || vec.y > 1)
		return (2);
	else if (vec.z < -1 || vec.z > 1)
		return (3);
	return (0);
}

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
	add_shape_to_list(scene_data, new_node);
	return (0);
}


t_plane		*get_plane_data(char *line)
{
	char		*value;
	t_plane		*plane;

	plane = malloc(sizeof(t_plane));
	value = strdup_upto_whitespace(line);
	line += ft_strlen(value);
	line += skip_spaces(line);
	parse_coordinates(value, &(plane->point));
	free(value);
	value = strdup_upto_whitespace(line);
	line += ft_strlen(value);
	line += skip_spaces(line);
	parse_coordinates(value, &(plane->normal));
	free(value);
	if (check_coordinates(plane->normal) != 0)
		return (error("Plane normalized vector value incorrect"), NULL);
	value = strdup_upto_whitespace(line);
	if (parse_colors(value, plane->color) != 0)
	{
		free(value);
		return (error("RGB Colors for Plane are incorrect"), NULL);
	}
	free(value);
	return (plane);
}

static int	add_plane_to_list(t_scene_data *scene_data, char *line)
{
	t_plane 	*plane;
	t_list		*new_node;
	
	plane = get_plane_data(line);
	if (!plane)
		return (1);
	new_node = ft_lstnew(plane);
	if (!new_node)
		return (free(plane), 1);
	add_shape_to_list(scene_data, new_node);
	return (0);
}

int	add_shape_data(t_identifier_type type, t_scene_data *scene_data, char *line)
{
	if (type == SPHERE)
	{
		if (add_sphere_to_list(scene_data, line) != 0)
			return (error("Failed to add sphere"), 1);
    }
	if (type == PLANE)
	{
		if (add_plane_to_list(scene_data, line) != 0)
			return (error("Failed to add plane"), 1);
    }
	return (0);
}
