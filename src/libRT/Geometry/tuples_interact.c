/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_interact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/04 09:15:16 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_tuple	add_tuples(t_tuple a, t_tuple b);
t_tuple	subtract_tuples(t_tuple a, t_tuple b);
t_tuple	negate_tuple(t_tuple t);
t_tuple	reflect(t_tuple incident, t_tuple normal);
int		tuple_equals(t_tuple a, t_tuple b);

t_tuple	add_tuples(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	result.w = a.w + b.w;
	return (result);
}

t_tuple	subtract_tuples(t_tuple a, t_tuple b)
{
	t_tuple	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	result.w = a.w - b.w;
	return (result);
}
t_tuple	negate_tuple(t_tuple t)
{
	t_tuple	result;

	result.x = -t.x;
	result.y = -t.y;
	result.z = -t.z;
	result.w = -t.w;
	return (result);
}

t_tuple	reflect(t_tuple incident, t_tuple normal)
{
	t_tuple	result;
	float	dot_product;

	dot_product = dot(incident, normal);
	result.x = incident.x - 2 * dot_product * normal.x;
	result.y = incident.y - 2 * dot_product * normal.y;
	result.z = incident.z - 2 * dot_product * normal.z;
	result.w = 0;
	return (result);
}

int	tuple_equals(t_tuple a, t_tuple b)
{
	if (equal(a.x, b.x) && equal(a.y, b.y) && equal(a.z, b.z) && equal(a.w,
			b.w))
		return (1);
	return (0);
}
