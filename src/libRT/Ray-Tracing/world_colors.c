/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/06 09:49:50 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static t_intersections	intersect_object(void *object, t_ray r, t_id_type type)
{
    t_intersections xs;

	xs.capacity = 0;
	xs.count = 0;
	xs.intersections = NULL;
	if (type == SPHERE)
		xs = intersect_sphere((t_sphere *)object, r);
	else if (type == PLANE)
		xs = intersect_plane((t_plane *)object, r);
	else if (type == CYLINDER)
		xs = intersect_cylinder((t_cylinder *)object, r);
	else if (type == CONE)
		xs = intersect_cone((t_cone *)object, r);

    return (xs);
}

t_intersections intersect_world(t_world *world, t_ray r)
{
    t_intersections xs;
	t_intersections temp_xs;
    t_list *current;
	int i;
	int j;
	
	xs.count = 0;
	xs.intersections = NULL;
	current = world->objects;
	i = -1;
	while (++i < world->object_count)
    {
        temp_xs = intersect_object(current->content, r, current->type);
		j = -1;
		while (++j < temp_xs.count)
            add_intersection(&xs, temp_xs.intersections[j]);
		if (temp_xs.intersections != NULL)
		{
            free(temp_xs.intersections);
            temp_xs.intersections = NULL;
		}
        current = current->next;
    }

    sort_intersections(&xs);
    return (xs);
}

t_color	color_at(t_world w, t_ray r)
{
	t_intersections	xs;
	t_intersection	*i;
	t_comps			comps;
	t_color			result;

	comps = comps_init();
	result = color(0,0,0);
	xs = intersect_world(&w, r);
	i = hit(&xs);
	if (!i)
		return (color(0, 0, 0));
	comps = prepare_computations(*i, r);
	result = shade_hit(w, comps);
	free(xs.intersections);
	return (result);
}

t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_tuple		forward = normalize(subtract_tuples(to, from));
	t_vector	left = cross(forward, normalize(up));
	t_vector	true_up = cross(vector(left.x ,left.y, left.z), forward);

	float orientation[16] = {
        left.x, left.y, left.z, 0,
        true_up.x, true_up.y, true_up.z, 0,
        -(forward.x), -(forward.y), -(forward.z), 0,
        0, 0, 0, 1
    };
	t_matrix result = create_matrix(4, 4, orientation);
    return (multiply_matrices(result, translation(-from.x, -from.y, -from.z)));
}
