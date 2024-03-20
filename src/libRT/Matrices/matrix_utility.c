/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utility.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:58:32 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/19 16:00:16 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_matrix submatrix(t_matrix matrix, int remove_row, int remove_col)
{
    t_matrix sub;
    sub.rows = matrix.rows - 1;
    sub.cols = matrix.cols - 1;
    sub.elements = malloc(sub.rows * sub.cols * sizeof(float));

    if (!sub.elements) 
        exit(EXIT_FAILURE);
    int i = 0, sub_i = 0;
    while (i < matrix.rows)
    {
        if (i != remove_row)
        {
            int j = 0, sub_j = 0;
            while (j < matrix.cols)
            {
                if (j != remove_col)
                {
                    sub.elements[sub_i * sub.cols + sub_j] = matrix.elements[i * matrix.cols + j];
                    sub_j++;
                }
                j++;
            }
            sub_i++;
        }
        i++;
    }
    
    return sub;
}

float minor(t_matrix matrix, int row, int col)
{
    t_matrix sub = submatrix(matrix, row, col);
    float det = determinant(sub);
    free(sub.elements);
    return det;
}
float cofactor(t_matrix matrix, int row, int col)
{
    float min = minor(matrix, row, col);
    if ((row + col) % 2 == 0)
        return min;
    
    else
        return -min;
}

float determinant(t_matrix M)
{
    if (M.rows != M.cols)
        exit(EXIT_FAILURE);
    
    float det = 0;
    if (M.rows == 2)
        det = M.elements[0] * M.elements[3] - M.elements[1] * M.elements[2];
    else 
    {
        int column = 0;
        while (column < M.cols)
        {
            det += M.elements[column] * cofactor(M, 0, column);
            column++;
        }
    }
    return det;
}
