/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/03 14:03:34 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_vector	cross(t_tuple v, t_tuple w);
t_vector	tuple_to_vector(t_tuple t);

t_vector	tuple_to_vector(t_tuple t)
{
	t_vector	v;

	v.x = t.x;
	v.y = t.y;
	v.z = t.z;
	return (v);
}

t_vector	cross(t_tuple v, t_tuple w)
{
	t_vector	result;

	result.x = v.y * w.z - v.z * w.y;
	result.y = v.z * w.x - v.x * w.z;
	result.z = v.x * w.y - v.y * w.x;
	return (result);
}
