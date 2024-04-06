/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 12:09:14 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_matrix	translation(float x, float y, float z);
t_matrix	scaling(float x, float y, float z);
t_matrix	shearing(t_shear_params params);

t_matrix	translation(float x, float y, float z)
{
	t_matrix	transform;

	transform.rows = 4;
	transform.cols = 4;
	transform.elements = ft_calloc(16, sizeof(float));
	if (!transform.elements)
		exit(EXIT_FAILURE);
	transform.elements[0] = 1;
	transform.elements[1] = 0;
	transform.elements[2] = 0;
	transform.elements[3] = x;
	transform.elements[4] = 0;
	transform.elements[5] = 1;
	transform.elements[6] = 0;
	transform.elements[7] = y;
	transform.elements[8] = 0;
	transform.elements[9] = 0;
	transform.elements[10] = 1;
	transform.elements[11] = z;
	transform.elements[12] = 0;
	transform.elements[13] = 0;
	transform.elements[14] = 0;
	transform.elements[15] = 1;
	register_matrix(transform);
	return (transform);
}

t_matrix	scaling(float x, float y, float z)
{
	t_matrix	scale;
	int			i;

	i = 0;
	scale.rows = 4;
	scale.cols = 4;
	scale.elements = ft_calloc(16, sizeof(float));
	if (!scale.elements)
		exit(EXIT_FAILURE);
	while (i < 16)
	{
		scale.elements[i] = 0;
		i++;
	}
	scale.elements[0] = x;
	scale.elements[5] = y;
	scale.elements[10] = z;
	scale.elements[15] = 1.0;
	register_matrix(scale);
	return (scale);
}

t_matrix	shearing(t_shear_params params)
{
	t_matrix	result;

	result.rows = 4;
	result.cols = 4;
	result.elements = ft_calloc(16, sizeof(float));
	if (!result.elements)
	{
		perror("Memory allocation error for shearing matrix");
		exit(EXIT_FAILURE);
	}
	set_shear_params(&result, params);
	register_matrix(result);
	return (result);
}
