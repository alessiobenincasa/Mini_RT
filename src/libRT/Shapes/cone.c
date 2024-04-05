/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 14:27:48 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/05 08:51:02 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_tuple	local_normal_at_cone(t_cone cone, t_tuple point)
{
	double	dist;
	double	slant_height;
	double	height;
	double	y;

	dist = pow(point.x, 2) + pow(point.z, 2);
	if (dist < pow(cone.maximum / 2, 2))
	{
		if (point.y >= cone.maximum - EPSILON)
			return (vector(0, 1, 0));
		else if (point.y <= cone.minimum + EPSILON)
			return (vector(0, -1, 0));
	}
	slant_height = sqrt(dist);
	height = fabs(cone.maximum - cone.minimum);
	y = (cone.maximum / 2) / height * slant_height;
	if (cone.inverted)
		y = -y;
	return (vector(point.x, y, point.z));
}

t_tuple normal_at_cone(t_cone cone, t_tuple p)
{
    t_tuple object_point = multiply_matrix_tuple(inverse(cone.transform), p);
    t_tuple object = local_normal_at_cone(cone, object_point);
    t_matrix inverse_transform = inverse(cone.transform);
    t_matrix transposed = transpose_matrix(inverse_transform);
    t_tuple world_normal = multiply_matrix_tuple(transposed, object);
    world_normal.w = 0;

    return (normalize(world_normal));
}

int	check_cap_cone(t_ray ray, double t, t_cone *cone, int is_lower)
{
	double	x;
	double	z;
	double	cap;

	cap = 0;
	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if (is_lower)
		cap = cone->minimum;
	else
		cap = cone->maximum;
	if ((pow(x, 2) + pow(z, 2)) <= pow(cap, 2))
		return (1);
	return (0);
}

void	add_intersection_cone(t_intersections *xs, double t, t_cone *cone)
{
	xs->count++;
	xs->intersections = realloc(xs->intersections, xs->count
			* sizeof(t_intersection));
	xs->intersections[xs->count - 1].t = t;
	xs->intersections[xs->count - 1].object.cone = cone;
	xs->intersections[xs->count - 1].type = CONE;
}

void	process_cone_intersections(t_intersections *xs, double *roots,
		t_cone *cone, t_ray r)
{
	double	y;
	int		i;

	i = 0;
	y = 0;
	if (!roots)
		return ;
	while (i < 2)
	{
		y = r.origin.y + roots[i] * r.direction.y;
		if (y > cone->minimum && y < cone->maximum)
			add_intersection_cone(xs, roots[i], cone);
		i++;
	}
}
