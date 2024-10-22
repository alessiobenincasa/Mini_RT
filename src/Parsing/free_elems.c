/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_elems.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:24:22 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 10:18:08 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	free_shapes(t_list *list, t_scene_data *s)
{
	t_list	*temp;

	temp = NULL;
	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->type == SPHERE)
		{
			free_s_motif((t_sphere *)temp->content, s->mlx);
			free_s((t_sphere *)temp->content);
		}
		else if (temp->type == PLANE)
			free_p((t_plane *)temp->content);
		else if (temp->type == CYLINDER)
			free_cyl((t_cylinder *)temp->content);
		else if (temp->type == CONE)
			free_c((t_cone *)temp->content);
		free(temp);
	}
}

void	free_extra_lights(t_list *list)
{
	t_list	*temp;

	temp = NULL;
	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->type == EXTRA_LIGHT)
			free(temp->content);
		free(temp);
	}
}

void	free_scene_data(t_scene_data *scene)
{
	if (!scene)
		return ;
	free_shapes(scene->shapes, scene);
	free_extra_lights(scene->extra_lights);
	if (scene->ambient_light)
		free(scene->ambient_light);
	if (scene->camera)
		free(scene->camera);
	if (scene->light)
		free(scene->light);
}
