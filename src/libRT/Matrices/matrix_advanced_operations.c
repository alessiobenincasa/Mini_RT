/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_advanced_operations.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/05 09:08:44 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_matrix	multiply_matrices(t_matrix a, t_matrix b);
t_tuple		mult_mat_tup(t_matrix m, t_tuple t);
t_matrix	inverse(t_matrix A);
int			is_invertible(t_matrix A);
t_matrix	identity_matrix(void);

t_matrix multiply_matrices(t_matrix a, t_matrix b)
{
    if (a.cols != b.rows)
        return create_matrix(0, 0, NULL);
    
    t_matrix c = create_matrix(a.rows, b.cols, NULL);
    int i = 0;

    while (i < a.rows) {
        int j = 0;
        while (j < b.cols) {
            float sum = 0;
            int k = 0;
            while (k < a.cols) {
                sum += a.elements[i * a.cols + k] * b.elements[k * b.cols + j];
                k++;
            }
            c.elements[i * c.cols + j] = sum;
            j++;
        }
        i++;
    }
    
    return c;
}

t_tuple mult_mat_tup(t_matrix m, t_tuple t)
{
    float elements[4] = {t.x, t.y, t.z, t.w};
    t_matrix result = multiply_matrices(m, create_matrix(4, 1, elements));
    return tuple(result.elements[0], result.elements[1], result.elements[2], result.elements[3]);
}

t_matrix inverse(t_matrix A)
{
    float det = determinant(A);
    if (det == 0)
        exit(EXIT_FAILURE);

    t_matrix B;
    B.rows = A.rows;
    B.cols = A.cols;
    B.elements = ft_calloc(A.rows * A.cols, sizeof(float));
    int i = 0;
    while (i < A.rows)
    {
        int j = 0;
        while (j < A.cols)
        {
            float cof = cofactor(A, i, j);
            B.elements[j * B.cols + i] = cof / det;
            j++;
        }
        i++;
    }
    return B;
}

int is_invertible(t_matrix A)
{
    return determinant(A) != 0;
}

t_matrix identity_matrix(void)
{
    float elements[16] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    return create_matrix(4, 4, elements);
}
