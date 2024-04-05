/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:52:04 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/05 19:59:17 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_intersections	intersect_cylinder(t_cylinder *cyl, t_ray ray)
{
	t_intersections	xs;
	t_ray			tr_ray;
	double			radius;

	xs.count = 0;
	xs.intersections = NULL;
	tr_ray = transform(ray, inverse(cyl->transform));
	radius = cyl->diameter / 2;
	intersect_cylinder_sides(cyl, tr_ray, &xs, radius);
	if (cyl->closed && fabs(tr_ray.direction.y) > EPSILON)
		intersect_cylinder_caps(cyl, tr_ray, &xs, radius);
	return (xs);
}
