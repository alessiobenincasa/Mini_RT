/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/04 09:43:36 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_tuple	multiply_tuple_scalar(t_tuple a, double scalar);
t_tuple	divide_tuple_scalar(t_tuple a, double scalar);
t_tuple	normalize(t_tuple v);
double	magnitude(t_tuple t);
double	dot(t_tuple a, t_tuple b);

t_tuple	multiply_tuple_scalar(t_tuple a, double scalar)
{
	t_tuple	result;

	result.x = a.x * scalar;
	result.y = a.y * scalar;
	result.z = a.z * scalar;
	result.w = a.w * scalar;
	return (result);
}

t_tuple	divide_tuple_scalar(t_tuple a, double scalar)
{
	t_tuple	result;

	result.x = a.x / scalar;
	result.y = a.y / scalar;
	result.z = a.z / scalar;
	result.w = a.w / scalar;
	return (result);
}

t_tuple	normalize(t_tuple v)
{
	double	magnitude;
	t_tuple	normalized_vector;

	magnitude = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	if (magnitude == 0.0)
		return (v);
	normalized_vector.x = v.x / magnitude;
	normalized_vector.y = v.y / magnitude;
	normalized_vector.z = v.z / magnitude;
	return (normalized_vector);
}

double	magnitude(t_tuple t)
{
	double	res;

	res = sqrt(t.x * t.x + t.y * t.y + t.z * t.z);
	return (res);
}

double	dot(t_tuple a, t_tuple b)
{
	double	res;

	res = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return (res);
}
