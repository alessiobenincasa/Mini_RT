/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit-test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 11:07:54 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/18 11:08:06 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include <criterion.h>

Test(matrix_operations, matrix_equality)
{
	float		elementsA[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
				15, 16};
	float		elementsB[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
				15, 16};
	t_matrix	A;
	t_matrix	B;

	A = create_matrix(4, 4, elementsA);
	B = create_matrix(4, 4, elementsB);
	cr_assert(matrices_equal(A, B),
		"Identical matrices are not considered equal.");
	free_matrix(&A);
	free_matrix(&B);
}

Test(matrix_operations, multiplying_a_matrix_by_the_identity_matrix)
{
    t_matrix A = create_matrix(4, 4, (float[16]){0, 1, 2, 4, 1, 2, 4, 8, 2, 4, 8, 16, 4, 8, 16, 32});
    t_matrix identity = identity_matrix();
    t_matrix result = multiply_matrices(A, identity);
    cr_assert(matrices_equal(result, A), "Multiplying by the identity matrix should return the original matrix.");
    free_matrix(&A);
    free_matrix(&result);
}

Test(matrix_operations, multiplying_the_identity_matrix_by_a_tuple)
{
    t_tuple a = tuple(1, 2, 3, 4);
    t_matrix identity = identity_matrix();
    t_tuple result = multiply_matrix_tuple(identity, a);
    cr_assert(tuple_equals(result, a), "Multiplying the identity matrix by a tuple should return the original tuple.");
    free_matrix(&identity);
}

Test(matrix_operations, transposing_a_matrix)
{
    
    float elementsA[] = {0, 9, 3, 0, 9, 8, 0, 8, 1, 8, 5, 3, 0, 0, 5, 8};
    t_matrix A = {4, 4, malloc(16 * sizeof(float))};
    ft_memcpy(A.elements, elementsA, 16 * sizeof(float)); 

    
    float elementsExpected[] = {0, 9, 1, 0, 9, 8, 8, 0, 3, 0, 5, 5, 0, 8, 3, 8};
    t_matrix expected = {4, 4, malloc(16 * sizeof(float))};
   ft_memcpy(expected.elements, elementsExpected, 16 * sizeof(float));

    
    t_matrix result = transpose_matrix(A);

    
    for (int i = 0; i < 16; i++) { 
        cr_assert_eq(result.elements[i], expected.elements[i], "Element at index %d is %f but expected %f", 
                     i, result.elements[i], expected.elements[i]);
    }

    
    free(A.elements);
    free(expected.elements);
    free(result.elements); 
}


Test(matrix_operations, determinant_of_2x2_matrix)
{
    t_matrix matrix = {
        .rows = 2,
        .cols = 2,
        .elements = (float[]){4, 3, 6, 8} 
    };

    float det = determinant(matrix);

    cr_assert_float_eq(det, 14, 0.001, "Expected determinant to be 14, but got %f", det);
}