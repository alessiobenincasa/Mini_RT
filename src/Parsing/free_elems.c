/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_elems.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:24:22 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/26 13:40:20 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void free_sphere(t_sphere *s)
{
	free(s->transform.elements);
}

void	free_scene_data(t_scene_data *scene)
{
	t_list	*current;
	t_list	*temp;

	if (!scene)
		return ;
	current = scene->shapes;
	while (current)
	{
		temp = current;
		current = current->next;
		if (temp->type == SPHERE)
		{
			printf("[🧹]Freeing sphere\n");
			free_sphere((t_sphere *)temp->content);
		}
		else if (temp->type == PLANE)
			printf("[🧹]Freeing plane\n");
		else if (temp->type == CYLINDER)
			printf("[🧹]Freeing cylinder\n");
		free(temp->content);
		free(temp);
	}
	if (scene->ambient_light)
		free(scene->ambient_light);
	if (scene->camera)
		free(scene->camera);
	if (scene->light)
		free(scene->light);
}
