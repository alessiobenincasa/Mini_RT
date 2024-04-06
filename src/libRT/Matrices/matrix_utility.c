/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 11:47:51 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_matrix			submatrix(t_matrix matrix, int remove_row, int remove_col);
float				minor_matrix(t_matrix matrix, int row, int col);
float				cofactor(t_matrix matrix, int row, int col);
float				determinant(t_matrix M);

t_matrix	submatrix(t_matrix matrix, int remove_row, int remove_col)
{
	t_matrix	sub;

	sub.rows = matrix.rows - 1;
	sub.cols = matrix.cols - 1;
	sub.elements = ft_calloc(sub.rows * sub.cols, sizeof(float));
	if (!sub.elements)
		exit(EXIT_FAILURE);
	copy_to_submatrix(&sub, matrix, remove_row, remove_col);
	return (sub);
}

float	minor_matrix(t_matrix matrix, int row, int col)
{
	t_matrix	sub;
	float		det;

	sub = submatrix(matrix, row, col);
	det = determinant(sub);
	free(sub.elements);
	return (det);
}

float	cofactor(t_matrix matrix, int row, int col)
{
	float	min;

	min = minor_matrix(matrix, row, col);
	if ((row + col) % 2 == 0)
		return (min);
	else
		return (-min);
}

float	determinant(t_matrix M)
{
	float	det;
	int		column;

	if (M.rows != M.cols)
		exit(EXIT_FAILURE);
	det = 0;
	if (M.rows == 2)
		det = M.elements[0] * M.elements[3] - M.elements[1] * M.elements[2];
	else
	{
		column = 0;
		while (column < M.cols)
		{
			det += M.elements[column] * cofactor(M, 0, column);
			column++;
		}
	}
	return (det);
}
