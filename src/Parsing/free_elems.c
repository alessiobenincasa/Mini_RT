/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_elems.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 13:24:22 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/01 17:04:55 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void free_sphere(t_sphere *s)
{
	free(s->transform.elements);
}

static void free_plane(t_plane *p)
{
	free(p->transform.elements);
}
static void free_cyl(t_cylinder *c)
{
	free(c->transform.elements);
}
static void free_cone(t_cone *c)
{
	free(c->transform.elements);
}

void	free_shapes(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->type == SPHERE)
			free_sphere((t_sphere *)temp->content);
		else if (temp->type == PLANE)
			free_plane((t_plane *)temp->content);
		else if (temp->type == CYLINDER)
			free_cyl((t_cylinder *)temp->content);
		else if (temp->type == CONE)
			free_cone((t_cone *)temp->content);
		free(temp->content);
		free(temp);
	}
}

void	free_extra_lights(t_list *list)
{
	t_list	*temp;

	while (list)
	{
		temp = list;
		list = list->next;
		if (temp->type == EXTRA_LIGHT)
			free(list->content);
		free(temp);
	}
}

void	free_scene_data(t_scene_data *scene)
{
	if (!scene)
		return ;
	free_shapes(scene->shapes);
	free_extra_lights(scene->extra_lights);
	if (scene->ambient_light)
		free(scene->ambient_light);
	if (scene->camera)
		free(scene->camera);
	if (scene->light)
		free(scene->light);
}
