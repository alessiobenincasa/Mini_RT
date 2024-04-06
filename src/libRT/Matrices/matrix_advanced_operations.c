/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_advanced_operations.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 10:01:04 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_matrix	multiply_matrices(t_matrix a, t_matrix b);
t_tuple		mult_mat_tup(t_matrix m, t_tuple t);
t_matrix	inverse(t_matrix A);
int			is_invertible(t_matrix A);
t_matrix	identity_matrix(void);

void	register_matrix(t_matrix m)
{
	size_t		new_capacity;
	t_matrix	*new_matrices;

	if (g_matrix_registry.count >= g_matrix_registry.capacity)
	{
		new_capacity = g_matrix_registry.capacity == 0 ? 1 : g_matrix_registry.capacity
			* 2;
		new_matrices = realloc(g_matrix_registry.matrices, new_capacity
				* sizeof(t_matrix));
		if (!new_matrices)
		{
			exit(EXIT_FAILURE);
		}
		g_matrix_registry.matrices = new_matrices;
		g_matrix_registry.capacity = new_capacity;
	}
	g_matrix_registry.matrices[g_matrix_registry.count++] = m;
}
t_matrix	multiply_matrices(t_matrix a, t_matrix b)
{
	t_matrix	c;
	int			i;
	int			j;
	float		sum;
	int			k;

	if (a.cols != b.rows)
		return (create_matrix(0, 0, NULL));
	c = create_matrix(a.rows, b.cols, NULL);
	i = 0;
	while (i < a.rows)
	{
		j = 0;
		while (j < b.cols)
		{
			sum = 0;
			k = 0;
			while (k < a.cols)
			{
				sum += a.elements[i * a.cols + k] * b.elements[k * b.cols + j];
				k++;
			}
			c.elements[i * c.cols + j] = sum;
			j++;
		}
		i++;
	}
	return (c);
}

t_tuple	mult_mat_tup(t_matrix m, t_tuple t)
{
	float		elements[4] = {t.x, t.y, t.z, t.w};
	t_matrix	result;

	result = multiply_matrices(m, create_matrix(4, 1, elements));
	return (tuple(result.elements[0], result.elements[1], result.elements[2],
			result.elements[3]));
}

t_matrix	inverse(t_matrix A)
{
	float		det;
	t_matrix	B;
	int			i;
	int			j;
	float		cof;

	det = determinant(A);
	if (det == 0)
		exit(EXIT_FAILURE);
	B.rows = A.rows;
	B.cols = A.cols;
	B.elements = ft_calloc(A.rows * A.cols, sizeof(float));
	i = 0;
	while (i < A.rows)
	{
		j = 0;
		while (j < A.cols)
		{
			cof = cofactor(A, i, j);
			B.elements[j * B.cols + i] = cof / det;
			j++;
		}
		i++;
	}
	register_matrix(B);
	return (B);
}

int	is_invertible(t_matrix A)
{
	return (determinant(A) != 0);
}

t_matrix	identity_matrix(void)
{
	float	elements[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};

	return (create_matrix(4, 4, elements));
}
