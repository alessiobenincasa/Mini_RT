/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_hit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 10:22:35 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/05 10:26:17 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static t_material	extract_material_comps(t_comps comps)
{
	t_material	m;

	if (comps.type == SPHERE)
		m = comps.object.sphere->material;
	else if (comps.type == PLANE)
		m = comps.object.plane->material;
	else if (comps.type == CYLINDER)
		m = comps.object.cylinder->material;
	else if (comps.type == CONE)
		m = comps.object.cone->material;
	else
		m = material();
	return (m);
}

static t_color	render_additional_lights(t_color total_light, t_world w,
		t_comps c, t_material m)
{
	t_list	*current_light;
	t_light	*light;
	t_color	res;
	int		in_shadow;

	in_shadow = 0;
	light = NULL;
	res = color(0, 0, 0);
	current_light = w.extra_lights;
	while (current_light != NULL)
	{
		light = (t_light *)(current_light->content);
		in_shadow = is_shadowed(w, c.over_point, light->position);
		res = lighting(m, *light, c, in_shadow);
		total_light = add_colors(total_light, res);
		current_light = current_light->next;
	}
	return (total_light);
}

t_color	shade_hit(t_world world, t_comps comps)
{
	t_color		total_light;
	t_material	material;
	int			in_shadow;

	total_light = color(0, 0, 0);
	material = extract_material_comps(comps);
	in_shadow = 0;
	if (no_world_light(world.light))
	{
		total_light = lighting(material, world.light, comps, 0);
		return (total_light);
	}
	in_shadow = is_shadowed(world, comps.over_point, world.light.position);
	total_light = lighting(material, world.light, comps, in_shadow);
	if (world.extra_lights)
		total_light = render_additional_lights(total_light, world, comps,
				material);
	return (total_light);
}
