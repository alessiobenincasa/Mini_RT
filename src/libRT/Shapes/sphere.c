/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/01 17:38:28 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_sphere	sphere(void);
void		set_transform(t_sphere *s, t_matrix t);
t_tuple		normal_at(t_sphere sphere, t_tuple p);

t_sphere	sphere(void)
{
	t_sphere	s;

	s.center = point(0, 0, 0);
	s.radius = 1;
	s.transform = identity_matrix();
	s.material = material();
	s.motif = NULL;
	s.scale = point(1, 1, 1);
	return (s);
}

void	set_transform(t_sphere *s, t_matrix t)
{
	if (s != NULL)
		s->transform = t;
}

t_tuple	normal_at(t_sphere sphere, t_tuple p)
{
	t_tuple	object_point;
	t_tuple	object_normal;
	t_tuple	world_normal;

	object_point = multiply_matrix_tuple(inverse(sphere.transform), p);
	object_normal = subtract_tuples(object_point, (t_tuple){sphere.center.x,
			sphere.center.y, sphere.center.z, 1});
	world_normal = multiply_matrix_tuple(transpose_matrix(inverse(sphere.transform)),
			object_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}
