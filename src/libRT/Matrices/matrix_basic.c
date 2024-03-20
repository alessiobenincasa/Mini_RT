/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:29:41 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/19 16:00:19 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_matrix	create_matrix(int rows, int cols, float elements[])
{
	t_matrix	m;

	m.rows = rows;
	m.cols = cols;
	m.elements = (float *)malloc(rows * cols * sizeof(float));
	if (elements != NULL)
		ft_memcpy(m.elements, elements, rows * cols * sizeof(float));
	else
		ft_memset(m.elements, 0, rows * cols * sizeof(float));
	return (m);
}

void	free_matrix(t_matrix *m)
{
	free(m->elements);
	m->elements = NULL;
}

float get_element(t_matrix m, int row, int col)
{
    if (row >= 0 && row < m.rows && col >= 0 && col < m.cols)
        return (m.elements[row * m.cols + col]);
    return (0.0f);
}

int matrices_equal(t_matrix a, t_matrix b)
{
    int i = 0;
    
    if (a.rows != b.rows || a.cols != b.cols)
        return 0;
    while (i < a.rows * a.cols)
    {
        if (fabs(a.elements[i] - b.elements[i]) > EPSILON)
            return (0);
        i++;
    }
    return(1);
}

t_matrix	transpose_matrix(t_matrix matrix)
{
	t_matrix	transposed;
	int			i;
	int			j;
	int			originalIndex;
	int			transposedIndex;

	transposed.rows = matrix.cols;
	transposed.cols = matrix.rows;
	transposed.elements = (float *)malloc(sizeof(float) * transposed.rows
			* transposed.cols);
	if (transposed.elements == NULL)
	{
		perror("Memory allocation error for transposed matrix");
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (++i < matrix.rows)
	{
		j = -1;
		while (++j < matrix.cols)
		{
			originalIndex = i * matrix.cols + j;
			transposedIndex = j * transposed.cols + i;
			transposed.elements[transposedIndex] = matrix.elements[originalIndex];
		}
	}
	return (transposed);
}
