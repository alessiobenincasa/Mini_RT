/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_advanced_operations.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/05 16:15:01 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_matrix	multiply_matrices(t_matrix a, t_matrix b);
t_tuple		multiply_matrix_tuple(t_matrix m, t_tuple t);
t_matrix	inverse(t_matrix A);
int			is_invertible(t_matrix A);
t_matrix	identity_matrix(void);

void register_matrix(t_matrix m)
{
    if (g_matrix_registry.count >= g_matrix_registry.capacity)
    {
        size_t new_capacity = g_matrix_registry.capacity == 0 ? 1 : g_matrix_registry.capacity * 2;
        t_matrix* new_matrices = realloc(g_matrix_registry.matrices, new_capacity * sizeof(t_matrix));
        if (!new_matrices) {
            exit(EXIT_FAILURE);
        }
        g_matrix_registry.matrices = new_matrices;
        g_matrix_registry.capacity = new_capacity;
    }
    g_matrix_registry.matrices[g_matrix_registry.count++] = m;
}

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
    register_matrix(c);
    return c;
}

t_tuple multiply_matrix_tuple(t_matrix m, t_tuple t)
{
    float elements[4] = {t.x, t.y, t.z, t.w};
    t_matrix result = multiply_matrices(m, create_matrix(4, 1, elements));
    register_matrix(result);
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
    register_matrix(B);
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
