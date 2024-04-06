/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:38:40 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/06 11:59:25 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_matrix	inverse(t_matrix A);
int			is_invertible(t_matrix A);
t_matrix	identity_matrix(void);

void	assign_inverse_elements(t_matrix *b, const t_matrix *A, float det)
{
	int		i;
	int		j;
	float	cof;

	i = 0;
	while (i < A->rows)
	{
		j = 0;
		while (j < A->cols)
		{
			cof = cofactor(*A, i, j);
			b->elements[j * b->cols + i] = cof / det;
			j++;
		}
		i++;
	}
}

t_matrix	inverse(t_matrix A)
{
	float		det;
	t_matrix	b;

	b.rows = A.rows;
	b.cols = A.cols;
	b.elements = ft_calloc(A.rows * A.cols, sizeof(float));
	if (!b.elements)
		exit(EXIT_FAILURE);
	det = determinant(A);
	if (det == 0)
		exit(EXIT_FAILURE);
	assign_inverse_elements(&b, &A, det);
	register_matrix(b);
	return (b);
}

int	is_invertible(t_matrix A)
{
	return (determinant(A) != 0);
}

t_matrix	identity_matrix(void)
{
	float	elements[16];

	elements[0] = 1;
	elements[1] = 0;
	elements[2] = 0;
	elements[3] = 0;
	elements[4] = 0;
	elements[5] = 1;
	elements[6] = 0;
	elements[7] = 0;
	elements[8] = 0;
	elements[9] = 0;
	elements[10] = 1;
	elements[11] = 0;
	elements[12] = 0;
	elements[13] = 0;
	elements[14] = 0;
	elements[15] = 1;
	return (create_matrix(4, 4, elements));
}
