/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_advanced_operations.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 11:39:23 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_matrix				multiply_matrices(t_matrix a, t_matrix b);
t_tuple					mult_mat_tup(t_matrix m, t_tuple t);

void	register_matrix(t_matrix m)
{
	size_t		new_capacity;
	t_matrix	*new_matrices;

	if (g_matrix_registry.count >= g_matrix_registry.capacity)
	{
		if (g_matrix_registry.capacity == 0)
			new_capacity = 1;
		else
			new_capacity = g_matrix_registry.capacity * 2;
		new_matrices = realloc(g_matrix_registry.matrices, new_capacity
				* sizeof(t_matrix));
		if (!new_matrices)
			exit(EXIT_FAILURE);
		g_matrix_registry.matrices = new_matrices;
		g_matrix_registry.capacity = new_capacity;
	}
	g_matrix_registry.matrices[g_matrix_registry.count++] = m;
}

t_mult_matrices_info	init_mult_matrices_info(t_matrix *a, t_matrix *b,
		t_matrix *c)
{
	t_mult_matrices_info	info;

	info.a = a;
	info.b = b;
	info.c = c;
	info.i = 0;
	info.j = 0;
	return (info);
}

void	calculate_cell_value(t_mult_matrices_info *info)
{
	float	sum;
	int		k;

	sum = 0;
	k = 0;
	while (k < info->a->cols)
	{
		sum += info->a->elements[info->i * info->a->cols + k]
			* info->b->elements[k * info->b->cols + info->j];
		k++;
	}
	info->c->elements[info->i * info->c->cols + info->j] = sum;
}

t_matrix	multiply_matrices(t_matrix a, t_matrix b)
{
	t_matrix				c;
	t_mult_matrices_info	info;

	if (a.cols != b.rows)
		return (create_matrix(0, 0, NULL));
	c = create_matrix(a.rows, b.cols, NULL);
	info = init_mult_matrices_info(&a, &b, &c);
	while (info.i < a.rows)
	{
		info.j = 0;
		while (info.j < b.cols)
		{
			calculate_cell_value(&info);
			info.j++;
		}
		info.i++;
	}
	return (c);
}

t_tuple	mult_mat_tup(t_matrix m, t_tuple t)
{
	float		elements[4];
	t_matrix	result;

	elements[0] = t.x;
	elements[1] = t.y;
	elements[2] = t.z;
	elements[3] = t.w;
	result = multiply_matrices(m, create_matrix(4, 1, elements));
	return (tuple(result.elements[0], result.elements[1], result.elements[2],
			result.elements[3]));
}
