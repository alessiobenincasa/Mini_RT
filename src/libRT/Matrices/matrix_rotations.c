/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 10:56:45 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_matrix	rotation_x(float radians);
t_matrix	rotation_y(float radians);
t_matrix	rotation_z(float radians);

t_matrix	rotation_x(float radians)
{
	t_matrix	result;

	result.rows = 4;
	result.cols = 4;
	result.elements = ft_calloc(16, sizeof(float));
	if (!result.elements)
		exit(EXIT_FAILURE);
	result.elements[0] = 1.0;
	result.elements[5] = cos(radians);
	result.elements[6] = -sin(radians);
	result.elements[9] = sin(radians);
	result.elements[10] = cos(radians);
	result.elements[15] = 1.0;
	register_matrix(result);
	return (result);
}

t_matrix	rotation_y(float radians)
{
	t_matrix	result;

	result.rows = 4;
	result.cols = 4;
	result.elements = ft_calloc(16, sizeof(float));
	if (!result.elements)
		exit(EXIT_FAILURE);
	result.elements[0] = cos(radians);
	result.elements[2] = sin(radians);
	result.elements[5] = 1.0;
	result.elements[8] = -sin(radians);
	result.elements[10] = cos(radians);
	result.elements[15] = 1.0;
	register_matrix(result);
	return (result);
}

t_matrix	rotation_z(float radians)
{
	float		*elements;
	t_matrix	m;

	elements = NULL;
	m = create_matrix(4, 4, elements);
	m.elements[0 * m.cols + 0] = cosf(radians);
	m.elements[0 * m.cols + 1] = -sinf(radians);
	m.elements[1 * m.cols + 0] = sinf(radians);
	m.elements[1 * m.cols + 1] = cosf(radians);
	m.elements[2 * m.cols + 2] = 1;
	m.elements[3 * m.cols + 3] = 1;
	return (m);
}
