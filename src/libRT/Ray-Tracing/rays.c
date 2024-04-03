/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/03 14:03:34 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_ray	transform(t_ray ray, t_matrix m);
t_ray	ray(t_tuple origin, t_tuple direction);
t_tuple	position(t_ray r, double t);

t_ray transform(t_ray ray, t_matrix m)
{
    t_ray transformed_ray;
    transformed_ray.origin = multiply_matrix_tuple(m, ray.origin);
    transformed_ray.direction = multiply_matrix_tuple(m, ray.direction);
    return transformed_ray;
}

t_ray ray(t_tuple origin, t_tuple direction)
{
    t_ray r;
    r.origin = origin;
    r.direction = direction;
    return r;
}

t_tuple position(t_ray r, double t)
{
    t_tuple distance = multiply_tuple_scalar(r.direction, t);
    return add_tuples(r.origin, distance);
}
