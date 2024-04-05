/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 19:32:52 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/05 19:34:29 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_cone	cone(void)
{
	t_cone	cone;

	cone.transform = identity_matrix();
	cone.minimum = 0;
	cone.maximum = 3;
	cone.closed = 1;
	cone.inverted = 1;
	cone.material = material();
	cone.material.specular = 0;
	cone.material.diffuse = 0.6;
	cone.material.shininess = 50;
	return (cone);
}

void	calculate_coefficients(t_ray ray, double *a, double *b, double *c)
{
	*a = pow(ray.direction.x, 2) - pow(ray.direction.y, 2)
		+ pow(ray.direction.z, 2);
	*b = 2 * ray.origin.x * ray.direction.x - 2 * ray.origin.y * ray.direction.y
		+ 2 * ray.origin.z * ray.direction.z;
	*c = pow(ray.origin.x, 2) - pow(ray.origin.y, 2) + pow(ray.origin.z, 2);
}
