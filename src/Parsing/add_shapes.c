/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:11:43 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/31 18:29:50 by svolodin         ###   ########.fr       */
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

static int	add_sphere_to_list(t_identifier_type type, t_scene_data *scene_data, char *line)
{
	t_sphere 	*sphere;
	t_list		*new_node;
	
	sphere = get_sphere_data(line, scene_data->ambient_light->ratio);
	if (!sphere)
		return (error("failed to get sphere data"), 1);
	new_node = ft_lstnew(sphere);
	if (!new_node)
		return (free(sphere), 1);
	new_node->type = type;
	add_shape_to_list(scene_data, new_node);
	return (0);
}

static int	add_plane_to_list(t_identifier_type type, t_scene_data *scene_data, char *line)
{
	t_plane 	*plane;
	t_list		*new_node;
	
	plane = get_plane_data(line, scene_data->ambient_light->ratio);
	if (!plane)
		return (error("failed to get plane data"), 1);
	new_node = ft_lstnew(plane);
	if (!new_node)
		return (free(plane), 1);
	new_node->type = type;
	add_shape_to_list(scene_data, new_node);
	return (0);
}

static int	add_cylinder_to_list(t_identifier_type type, t_scene_data *scene_data, char *line)
{
	t_cylinder 	*cylinder;
	t_list		*new_node;
	
	cylinder = get_cylinder_data(line, scene_data->ambient_light->ratio);
	if (!cylinder)
		return (error("failed to get cylinder data"), 1);
	new_node = ft_lstnew(cylinder);
	if (!new_node)
		return (free(cylinder), 1);
	new_node->type = type;
	add_shape_to_list(scene_data, new_node);
	return (0);
}

static int	add_cone_to_list(t_identifier_type type, t_scene_data *scene_data, char *line)
{
	t_cone 		*cone;
	t_list		*new_node;
	
	cone = get_cone_data(line, scene_data->ambient_light->ratio);
	if (!cone)
		return (error("failed to get cone data"), 1);
	new_node = ft_lstnew(cone);
	if (!new_node)
		return (free(cone), 1);
	new_node->type = type;
	add_shape_to_list(scene_data, new_node);
	return (0);
}

int	add_shape_data(t_identifier_type type, t_scene_data *scene_data, char *line)
{
	if (type == SPHERE)
	{
		if (add_sphere_to_list(type, scene_data, line) != 0)
			return (error("Failed to add sphere"), 1);
    }
	else if (type == PLANE)
	{
		if (add_plane_to_list(type, scene_data, line) != 0)
			return (error("Failed to add plane"), 1);
    }
	else if (type == CYLINDER)
	{
		if (add_cylinder_to_list(type, scene_data, line) != 0)
			return (error("Failed to add cylinder"), 1);
    }
	else if (type == CONE)
	{
		if (add_cone_to_list(type, scene_data, line) != 0)
			return (error("Failed to add cone"), 1);
    }
	else
		return (error("Tried to add unknown shape"), 1);
	return (0);
}
