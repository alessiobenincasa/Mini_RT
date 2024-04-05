/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/05 09:08:44 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_sphere		sphere(void);
t_tuple			normal_at(t_sphere sphere, t_tuple p);

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

t_tuple	normal_at(t_sphere s, t_tuple p)
{
	t_tuple	obj_point;
	t_tuple	obj_norm;
	t_tuple	wrld_norm;

	obj_point = mult_mat_tup(inverse(s.transform), p);
	obj_norm = subtract_tuples(obj_point, point(s.center.x, s.center.y,
				s.center.z));
	wrld_norm = mult_mat_tup(transpose_matrix(inverse(s.transform)),
			obj_norm);
	wrld_norm.w = 0;
	wrld_norm = normalize(wrld_norm);
	return (wrld_norm);
}
