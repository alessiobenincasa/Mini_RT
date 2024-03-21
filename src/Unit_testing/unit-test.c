// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   unit-test.c                                        :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/03/18 11:07:54 by albeninc          #+#    #+#             */
// /*   Updated: 2024/03/20 11:20:50 by albeninc         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

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

Test(matrix_operations, submatrix_of_3x3_is_2x2) {
    t_matrix A = {
        .rows = 3,
        .cols = 3,
        .elements = (float[]){1, 5, 0, -3, 2, 7, 0, 6, -3}
    };

    t_matrix expected = {
        .rows = 2,
        .cols = 2,
        .elements = (float[]){-3, 2, 0, 6} 
    };

    t_matrix result = submatrix(A, 0, 2);

    int i = 0;
    while (i < expected.rows * expected.cols)
    {
        cr_assert_float_eq(result.elements[i], expected.elements[i], 0.001, "Element %d is %f but expected %f", i, result.elements[i], expected.elements[i]);
        i++;
    }
    free(result.elements);
}

Test(matrix_operations, submatrix_of_4x4_is_3x3)
{
    t_matrix A = {
        .rows = 4,
        .cols = 4,
        .elements = (float[]){-6, 1, 1, 6, -8, 5, 8, 6, -1, 0, 8, 2, -7, 1, -1, 1}
    };

    t_matrix expected = {
        .rows = 3,
        .cols = 3,
        .elements = (float[]){-6, 1, 6, -8, 8, 6, -7, -1, 1}
    };

    t_matrix result = submatrix(A, 2, 1);

    int i = 0;
    while (i < expected.rows * expected.cols) {
        cr_assert_float_eq(result.elements[i], expected.elements[i], 0.001, "Element %d is %f but expected %f", i, result.elements[i], expected.elements[i]);
        i++;
    }
    free(result.elements);
}

Test(matrix_operations, calculating_minor_of_3x3_matrix)
{
    t_matrix A = {
        .rows = 3,
        .cols = 3,
        .elements = malloc(9 * sizeof(float))
    };
    
    int i = 0;
    float elementsA[] = {3, 5, 0, 2, -1, -7, 6, -1, 5};
    while (i < 9) 
    {
        A.elements[i] = elementsA[i];
        i++;
    }

    t_matrix B = submatrix(A, 1, 0);

    float detB = determinant(B);
    cr_assert_float_eq(detB, 25, 0.001, "Determinant of B was expected to be 25, but got %f", detB);

    float minorA = minor(A, 1, 0);
    cr_assert_float_eq(minorA, 25, 0.001, "Minor of A, removing row 1 and col 0, was expected to be 25, but got %f", minorA);

    free(A.elements);
    free(B.elements);
}

Test(matrix_operations, calculating_cofactor_of_3x3_matrix)
{
    t_matrix A = {
        .rows = 3,
        .cols = 3,
        .elements = malloc(9 * sizeof(float))
    };
    A.elements[0] = 3; A.elements[1] = 5; A.elements[2] = 0;
    A.elements[3] = 2; A.elements[4] = -1; A.elements[5] = -7;
    A.elements[6] = 6; A.elements[7] = -1; A.elements[8] = 5;

    float minorA_00 = minor(A, 0, 0);
    float cofactorA_00 = cofactor(A, 0, 0);
    cr_assert_float_eq(minorA_00, -12, 0.001);
    cr_assert_float_eq(cofactorA_00, -12, 0.001);

    float minorA_10 = minor(A, 1, 0);
    float cofactorA_10 = cofactor(A, 1, 0);
    cr_assert_float_eq(minorA_10, 25, 0.001);
    cr_assert_float_eq(cofactorA_10, -25, 0.001);

    free(A.elements);
}

Test(determinant_tests, determinant_of_3x3_matrix)
{
    t_matrix A = {
        .rows = 3,
        .cols = 3,
        .elements = malloc(9 * sizeof(float))
    };
    float elements[] = {1, 2, 6, -5, 8, -4, 2, 6, 4};
    int i = 0;
    while (i < 9)
    {
        A.elements[i] = elements[i];
        i++;
    }
    cr_expect_eq(cofactor(A, 0, 0), 56, "Expected cofactor(A, 0, 0) to be 56");
    cr_expect_eq(cofactor(A, 0, 1), 12, "Expected cofactor(A, 0, 1) to be 12");
    cr_expect_eq(cofactor(A, 0, 2), -46, "Expected cofactor(A, 0, 2) to be -46");
    cr_expect_eq(determinant(A), -196, "Expected determinant(A) to be -196");

    free(A.elements);
}

Test(determinant_tests, determinant_of_4x4_matrix)
{
    t_matrix A = {
        .rows = 4,
        .cols = 4,
        .elements = malloc(16 * sizeof(float))
    };
    float elements[] = {-2, -8, 3, 5, -3, 1, 7, 3, 1, 2, -9, 6, -6, 7, 7, -9};
    int i = 0;
    while (i < 16)
    {
        A.elements[i] = elements[i];
        i++;
    }

    cr_expect_eq(cofactor(A, 0, 0), 690, "Expected cofactor(A, 0, 0) to be 690");
    cr_expect_eq(cofactor(A, 0, 1), 447, "Expected cofactor(A, 0, 1) to be 447");
    cr_expect_eq(cofactor(A, 0, 2), 210, "Expected cofactor(A, 0, 2) to be 210");
    cr_expect_eq(cofactor(A, 0, 3), 51, "Expected cofactor(A, 0, 3) to be 51");
    cr_expect_eq(determinant(A), -4071, "Expected determinant(A) to be -4071");

    free(A.elements);
}

Test(matrix_tests, invertible_matrix)
{
    t_matrix A = { .rows = 4, .cols = 4, .elements = (float[]){ 6, 4, 4, 4, 5, 5, 7, 6, 4, -9, 3, -7, 9, 1, 7, -6 } };
    cr_assert_eq(determinant(A), -2120);
    cr_assert(is_invertible(A));
}

Test(matrix_tests, noninvertible_matrix)
{
    t_matrix A = { .rows = 4, .cols = 4, .elements = (float[]){ -4, 2, -2, -3, 9, 6, 2, 6, 0, -5, 1, -5, 0, 0, 0, 0 } };
    cr_assert_eq(determinant(A), 0);
    cr_assert_not(is_invertible(A));
}

Test(matrix_tests, calculating_inverse_of_matrix)
{
    t_matrix A = { .rows = 4, .cols = 4, .elements = (float[]){ -5, 2, 6, -8, 1, -5, 1, 8, 7, 7, -6, -7, 1, -3, 7, 4 } };
    t_matrix B = inverse(A);
    cr_assert_float_eq(determinant(A), 532, 0.001);
    cr_assert_float_eq(cofactor(A, 2, 3), -160, 0.001);
    cr_assert_float_eq(B.elements[3 * B.cols + 2], -160.0 / 532, 0.001);
    cr_assert_float_eq(cofactor(A, 3, 2), 105, 0.001);
    cr_assert_float_eq(B.elements[2 * B.cols + 3], 105.0 / 532, 0.001);

    int i = 0;
    float expected_elements[] = { 0.21805, 0.45113, 0.24060, -0.04511, -0.80827, -1.45677, -0.44361, 0.52068, -0.07895, -0.22368, -0.05263, 0.19737, -0.52256, -0.81391, -0.30075, 0.30639 };
    while (i < 16) {
        cr_assert_float_eq(B.elements[i], expected_elements[i], 0.001, "Element %d is %f but expected %f", i, B.elements[i], expected_elements[i]);
        i++;
    }

    free(B.elements);
}

Test(matrix_inverse_tests, calculating_the_inverse_of_another_matrix)
{
    t_matrix A = {
        .rows = 4,
        .cols = 4,
        .elements = malloc(16 * sizeof(float))
    };
    float elementsA[] = {8, -5, 9, 2, 7, 5, 6, 1, -6, 0, 9, 6, -3, 0, -9, -4};
    ft_memcpy(A.elements, elementsA, 16 * sizeof(float));

    t_matrix expected = {
        .rows = 4,
        .cols = 4,
        .elements = malloc(16 * sizeof(float))
    };
    float elementsExpected[] = {-0.15385, -0.15385, -0.28205, -0.53846, -0.07692, 0.12308, 0.02564, 0.03077, 0.35897, 0.35897, 0.43590, 0.92308, -0.69231, -0.69231, -0.76923, -1.92308};
    ft_memcpy(expected.elements, elementsExpected, 16 * sizeof(float));

    t_matrix B = inverse(A);

    int i = 0;
    while (i < 16)
    {
        cr_assert_float_eq(B.elements[i], expected.elements[i], 0.0001);
        i++;
    }

    free(A.elements);
    free(B.elements);
    free(expected.elements);
}

Test(matrix_inverse_tests, multiplying_a_product_by_its_inverse)
{
    t_matrix A = {
        .rows = 4,
        .cols = 4,
        .elements = malloc(16 * sizeof(float))
    };
    float elementsA[] = {3, -9, 7, 3, 3, -8, 2, -9, -4, 4, 4, 1, -6, 5, -1, 1};
    int i = 0;
    while (i < 16) {
        A.elements[i] = elementsA[i];
        i++;
    }

    t_matrix B = {
        .rows = 4,
        .cols = 4,
        .elements = malloc(16 * sizeof(float))
    };
    float elementsB[] = {8, 2, 2, 2, 3, -1, 7, 0, 7, 0, 5, 4, 6, -2, 0, 5};
    i = 0;
    while (i < 16)
    {
        B.elements[i] = elementsB[i];
        i++;
    }
    t_matrix C = multiply_matrices(A, B);
    t_matrix B_inv = inverse(B);
    t_matrix result = multiply_matrices(C, B_inv);

    i = 0;
    while (i < 16)
    {
        cr_assert_float_eq(result.elements[i], A.elements[i], 0.0001, "Element %d is %f but expected %f", i, result.elements[i], A.elements[i]);
        i++;
    }
    free(A.elements);
    free(B.elements);
    free(C.elements);
    free(B_inv.elements);
    free(result.elements);
}
Test(matrix_transformations, multiplying_by_translation_matrix)
{
    t_matrix transform = translation(5, -3, 2);
    t_tuple p = point(-3, 4, 5);

    t_tuple result = multiply_matrix_tuple(transform, p);

    t_tuple expected = point(2, 1, 7);

    cr_assert_float_eq(result.x, expected.x, 0.0001);
    cr_assert_float_eq(result.y, expected.y, 0.0001);
    cr_assert_float_eq(result.z, expected.z, 0.0001);
    cr_assert_float_eq(result.w, expected.w, 0.0001);

    free(transform.elements);
}
Test(matrix_transformations, multiplying_by_inverse_of_translation_matrix)
{
    t_matrix transform = translation(5, -3, 2);
    t_matrix inv = inverse(transform);
    t_tuple p = point(-3, 4, 5);
    t_tuple result = multiply_matrix_tuple(inv, p);

    t_tuple expected = point(-8, 7, 3);

    cr_assert_float_eq(result.x, expected.x, 0.0001, "Expected x of %f, got %f", expected.x, result.x);
    cr_assert_float_eq(result.y, expected.y, 0.0001, "Expected y of %f, got %f", expected.y, result.y);
    cr_assert_float_eq(result.z, expected.z, 0.0001, "Expected z of %f, got %f", expected.z, result.z);
    cr_assert_float_eq(result.w, expected.w, 0.0001, "Expected w of %f, got %f", expected.w, result.w);

    free(transform.elements);
    free(inv.elements);
}

Test(matrix_transformations, translation_does_not_affect_vectors)
{
    t_matrix transform = translation(5, -3, 2);
    t_tuple v = vector(-3, 4, 5);
    
   
    t_tuple result = multiply_matrix_tuple(transform, v);
    cr_assert_float_eq(result.x, v.x, 0.0001, "X component should remain unchanged. Expected %f, got %f", v.x, result.x);
    cr_assert_float_eq(result.y, v.y, 0.0001, "Y component should remain unchanged. Expected %f, got %f", v.y, result.y);
    cr_assert_float_eq(result.z, v.z, 0.0001, "Z component should remain unchanged. Expected %f, got %f", v.z, result.z);
    cr_assert_float_eq(result.w, v.w, 0.0001, "W component (indicating a vector) should remain 0. Expected %f, got %f", v.w, result.w);

    free(transform.elements);
}

Test(matrix_transformations, scaling_matrix_applied_to_point)
{
    t_matrix transform = scaling(2, 3, 4);
    t_tuple p = point(-4, 6, 8);
    t_tuple result = multiply_matrix_tuple(transform, p);

    t_tuple expected = point(-8, 18, 32);

    cr_assert_float_eq(result.x, expected.x, 0.0001);
    cr_assert_float_eq(result.y, expected.y, 0.0001);
    cr_assert_float_eq(result.z, expected.z, 0.0001);
    cr_assert_float_eq(result.w, expected.w, 0.0001);

    free(transform.elements);
}

Test(matrix_transformations, scaling_matrix_applied_to_vector)
{
    t_matrix transform = scaling(2, 3, 4);
    t_tuple v = vector(-4, 6, 8);
    t_tuple result = multiply_matrix_tuple(transform, v);

    t_tuple expected = vector(-8, 18, 32);

    cr_assert_float_eq(result.x, expected.x, 0.0001);
    cr_assert_float_eq(result.y, expected.y, 0.0001);
    cr_assert_float_eq(result.z, expected.z, 0.0001);
    cr_assert_float_eq(result.w, expected.w, 0.0001);

    free(transform.elements);
}

Test(matrix_transformations, inverse_scaling_matrix_applied_to_vector)
{
    t_matrix transform = scaling(2, 3, 4);
    t_matrix inv = inverse(transform);
    t_tuple v = vector(-4, 6, 8);
    t_tuple result = multiply_matrix_tuple(inv, v);

    t_tuple expected = vector(-2, 2, 2);

    cr_assert_float_eq(result.x, expected.x, 0.0001);
    cr_assert_float_eq(result.y, expected.y, 0.0001);
    cr_assert_float_eq(result.z, expected.z, 0.0001);
    cr_assert_float_eq(result.w, expected.w, 0.0001);

    free(transform.elements);
    free(inv.elements);
}

Test(matrix_transformations, reflection_is_scaling_by_negative_value)
{
    t_matrix transform = scaling(-1, 1, 1);
    t_tuple p = point(2, 3, 4);
    t_tuple result = multiply_matrix_tuple(transform, p);

    t_tuple expected = point(-2, 3, 4);

    cr_assert_float_eq(result.x, expected.x, 0.0001, "X component after reflection incorrect. Expected %f, got %f", expected.x, result.x);
    cr_assert_float_eq(result.y, expected.y, 0.0001, "Y component should remain unchanged. Expected %f, got %f", expected.y, result.y);
    cr_assert_float_eq(result.z, expected.z, 0.0001, "Z component should remain unchanged. Expected %f, got %f", expected.z, result.z);
    cr_assert_float_eq(result.w, expected.w, 0.0001, "W component (indicating a point) should remain 1. Expected %f, got %f", expected.w, result.w);

    free(transform.elements);
}


Test(matrix_transformations, rotating_point_around_x_axis)
{
    t_tuple p = point(0, 1, 0);
    t_matrix half_quarter = rotation_x(M_PI / 4);
    t_matrix full_quarter = rotation_x(M_PI / 2);

    t_tuple half_rotated = multiply_matrix_tuple(half_quarter, p);
    t_tuple full_rotated = multiply_matrix_tuple(full_quarter, p);

    cr_assert_float_eq(half_rotated.x, 0, 0.0001);
    cr_assert_float_eq(half_rotated.y, sqrt(2)/2, 0.0001);
    cr_assert_float_eq(half_rotated.z, sqrt(2)/2, 0.0001);

    cr_assert_float_eq(full_rotated.x, 0, 0.0001);
    cr_assert_float_eq(full_rotated.y, 0, 0.0001);
    cr_assert_float_eq(full_rotated.z, 1, 0.0001);

    free(half_quarter.elements);
    free(full_quarter.elements);
}

Test(matrix_transformations, inverse_rotating_point_around_x_axis)
{
    t_tuple p = point(0, 1, 0);
    t_matrix half_quarter = rotation_x(M_PI / 4);
    t_matrix inv = inverse(half_quarter);

    t_tuple inv_rotated = multiply_matrix_tuple(inv, p);

    cr_assert_float_eq(inv_rotated.x, 0, 0.0001);
    cr_assert_float_eq(inv_rotated.y, sqrt(2)/2, 0.0001);
    cr_assert_float_eq(inv_rotated.z, -sqrt(2)/2, 0.0001);

    free(half_quarter.elements);
    free(inv.elements);
}


Test(matrix_transformations, rotating_point_around_y_axis)
{
    t_tuple p = point(0, 0, 1);
    t_matrix half_quarter = rotation_y(M_PI / 4);
    t_matrix full_quarter = rotation_y(M_PI / 2);

    t_tuple half_rotated = multiply_matrix_tuple(half_quarter, p);
    t_tuple full_rotated = multiply_matrix_tuple(full_quarter, p);

    cr_assert_float_eq(half_rotated.x, sqrt(2)/2, 0.0001, "Expected x to be √2/2, got %f", half_rotated.x);
    cr_assert_float_eq(half_rotated.y, 0, 0.0001, "Expected y to be 0, got %f", half_rotated.y);
    cr_assert_float_eq(half_rotated.z, sqrt(2)/2, 0.0001, "Expected z to be √2/2, got %f", half_rotated.z);

    cr_assert_float_eq(full_rotated.x, 1, 0.0001, "Expected x to be 1, got %f", full_rotated.x);
    cr_assert_float_eq(full_rotated.y, 0, 0.0001, "Expected y to be 0, got %f", full_rotated.y);
    cr_assert_float_eq(full_rotated.z, 0, 0.0001, "Expected z to be 0, got %f", full_rotated.z);

    free(half_quarter.elements);
    free(full_quarter.elements);
}



Test(matrix_transformations, shearing_transformation_moves_x_in_proportion_to_y)
{
    t_matrix transform = shearing(1, 0, 0, 0, 0, 0);
    t_tuple p = point(2, 3, 4);
    t_tuple result = multiply_matrix_tuple(transform, p);

    cr_assert_float_eq(result.x, 5, 0.0001, "After shearing, x should be 5, got %f", result.x);
    cr_assert_float_eq(result.y, 3, 0.0001, "Y should remain unchanged, got %f", result.y);
    cr_assert_float_eq(result.z, 4, 0.0001, "Z should remain unchanged, got %f", result.z);

    free(transform.elements);
}

Test(matrix_transformations, shearing_transformation_moves_x_in_proportion_to_z)
{
    t_matrix transform = shearing(0, 1, 0, 0, 0, 0);
    t_tuple p = point(2, 3, 4);
    t_tuple result = multiply_matrix_tuple(transform, p);
    cr_assert_float_eq(result.x, 6, 0.0001);
    cr_assert_float_eq(result.y, 3, 0.0001);
    cr_assert_float_eq(result.z, 4, 0.0001);
    free(transform.elements);
}

Test(matrix_transformations, shearing_transformation_moves_y_in_proportion_to_x)
{
    t_matrix transform = shearing(0, 0, 1, 0, 0, 0);
    t_tuple p = point(2, 3, 4);
    t_tuple result = multiply_matrix_tuple(transform, p);
    cr_assert_float_eq(result.x, 2, 0.0001);
    cr_assert_float_eq(result.y, 5, 0.0001);
    cr_assert_float_eq(result.z, 4, 0.0001);
    free(transform.elements);
}

Test(matrix_transformations, shearing_transformation_moves_y_in_proportion_to_z)
{
    t_matrix transform = shearing(0, 0, 0, 1, 0, 0);
    t_tuple p = point(2, 3, 4);
    t_tuple result = multiply_matrix_tuple(transform, p);
    cr_assert_float_eq(result.x, 2, 0.0001);
    cr_assert_float_eq(result.y, 7, 0.0001);
    cr_assert_float_eq(result.z, 4, 0.0001);
    free(transform.elements);
}

Test(matrix_transformations, shearing_transformation_moves_z_in_proportion_to_x)
{
    t_matrix transform = shearing(0, 0, 0, 0, 1, 0);
    t_tuple p = point(2, 3, 4);
    t_tuple result = multiply_matrix_tuple(transform, p);
    cr_assert_float_eq(result.x, 2, 0.0001);
    cr_assert_float_eq(result.y, 3, 0.0001);
    cr_assert_float_eq(result.z, 6, 0.0001);
    free(transform.elements);
}

Test(matrix_transformations, shearing_transformation_moves_z_in_proportion_to_y)
{
    t_matrix transform = shearing(0, 0, 0, 0, 0, 1);
    t_tuple p = point(2, 3, 4);
    t_tuple result = multiply_matrix_tuple(transform, p);
    cr_assert_float_eq(result.x, 2, 0.0001);
    cr_assert_float_eq(result.y, 3, 0.0001);
    cr_assert_float_eq(result.z, 7, 0.0001);
    free(transform.elements);
}

Test(matrix_transformations, individual_transformations_applied_in_sequence)
{
    t_tuple p = point(1, 0, 1);
    t_matrix A = rotation_x(M_PI / 2);
    t_matrix B = scaling(5, 5, 5);
    t_matrix C = translation(10, 5, 7);

    t_tuple p2 = multiply_matrix_tuple(A, p);
    cr_assert_float_eq(p2.x, 1, 0.0001);
    cr_assert_float_eq(p2.y, -1, 0.0001);
    cr_assert_float_eq(p2.z, 0, 0.0001);

    t_tuple p3 = multiply_matrix_tuple(B, p2);
    cr_assert_float_eq(p3.x, 5, 0.0001);
    cr_assert_float_eq(p3.y, -5, 0.0001);
    cr_assert_float_eq(p3.z, 0, 0.0001);

    t_tuple p4 = multiply_matrix_tuple(C, p3);
    cr_assert_float_eq(p4.x, 15, 0.0001);
    cr_assert_float_eq(p4.y, 0, 0.0001);
    cr_assert_float_eq(p4.z, 7, 0.0001);

    free(A.elements);
    free(B.elements);
    free(C.elements);
}

Test(matrix_transformations, chained_transformations_applied_in_reverse_order)
{
    t_tuple p = point(1, 0, 1);
    t_matrix A = rotation_x(M_PI / 2);
    t_matrix B = scaling(5, 5, 5);
    t_matrix C = translation(10, 5, 7);

    t_matrix T = multiply_matrices(multiply_matrices(C, B), A);

    t_tuple result = multiply_matrix_tuple(T, p);
    cr_assert_float_eq(result.x, 15, 0.0001);
    cr_assert_float_eq(result.y, 0, 0.0001);
    cr_assert_float_eq(result.z, 7, 0.0001);

    free(A.elements);
    free(B.elements);
    free(C.elements);
    free(T.elements);
}

Test(ray_creation, querying_a_ray)
{
    t_tuple origin = point(1, 2, 3);
    t_tuple direction = vector(4, 5, 6);
    t_ray r = ray(origin, direction);


    cr_assert_float_eq(r.origin.x, origin.x, 0.00001, "Ray's origin x-coordinate did not match.");
    cr_assert_float_eq(r.origin.y, origin.y, 0.00001, "Ray's origin y-coordinate did not match.");
    cr_assert_float_eq(r.origin.z, origin.z, 0.00001, "Ray's origin z-coordinate did not match.");

    cr_assert_float_eq(r.direction.x, direction.x, 0.00001, "Ray's direction x-coordinate did not match.");
    cr_assert_float_eq(r.direction.y, direction.y, 0.00001, "Ray's direction y-coordinate did not match.");
    cr_assert_float_eq(r.direction.z, direction.z, 0.00001, "Ray's direction z-coordinate did not match.");
}

Test(ray_operations, computing_a_point_from_a_distance)
{
    t_ray r = ray(point(2, 3, 4), vector(1, 0, 0));

    t_tuple p0 = position(r, 0);
    cr_assert(tuple_equals(p0, point(2, 3, 4)), "Position at t=0 did not match expected point.");

    t_tuple p1 = position(r, 1);
    cr_assert(tuple_equals(p1, point(3, 3, 4)), "Position at t=1 did not match expected point.");

    t_tuple p_minus1 = position(r, -1);
    cr_assert(tuple_equals(p_minus1, point(1, 3, 4)), "Position at t=-1 did not match expected point.");

    t_tuple p2_5 = position(r, 2.5);
    cr_assert(tuple_equals(p2_5, point(4.5, 3, 4)), "Position at t=2.5 did not match expected point.");
}

Test(sphere_intersections, ray_intersects_sphere_at_two_points)
{
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_sphere s = sphere();
    t_intersections xs = intersect(&s, r);

    cr_assert_eq(xs.count, 2, "Expected 2 intersections but got %d.", xs.count);
    cr_assert_float_eq(xs.intersections[0].t, 4.0, 1e-6, "First intersection t value was not 4.0.");
    cr_assert_float_eq(xs.intersections[1].t, 6.0, 1e-6, "Second intersection t value was not 6.0.");

    free(xs.intersections);
}

Test(sphere_intersections, ray_intersects_sphere_at_a_tangent)
{
    t_ray r = ray(point(0, 1, -5), vector(0, 0, 1));
    t_sphere s = sphere();
    t_intersections xs = intersect(&s, r);

    cr_assert_eq(xs.count, 2, "Expected 2 intersections but got %d.", xs.count);
    cr_assert_float_eq(xs.intersections[0].t, 5.0, 1e-6, "First intersection t value was not 4.0.");
    cr_assert_float_eq(xs.intersections[1].t, 5.0, 1e-6, "Second intersection t value was not 6.0.");

    free(xs.intersections);
}
Test(sphere_intersections, ray_misses_sphere)
{
    t_ray r = ray(point(0, 2, -5), vector(0, 0, 1));
    t_sphere s = sphere();
    t_intersections xs = intersect(&s, r);

    cr_assert_eq(xs.count, 0, "Expected 2 intersections but got %d.", xs.count);

    free(xs.intersections);
}

Test(sphere_intersections, A_ray_originates_inside_a_sphere)
{
    t_ray r = ray(point(0, 0, 0), vector(0, 0, 1));
    t_sphere s = sphere();
    t_intersections xs = intersect(&s, r);

    cr_assert_eq(xs.count, 2, "Expected 2 intersections but got %d.", xs.count);
    cr_assert_float_eq(xs.intersections[0].t, -1.0, 1e-6, "First intersection t value was not 4.0.");
    cr_assert_float_eq(xs.intersections[1].t, 1.0, 1e-6, "Second intersection t value was not 6.0.");

    free(xs.intersections);
}

Test(sphere_intersections, A_ray_originates_behind_a_sphere)
{
    t_ray r = ray(point(0, 0, 5), vector(0, 0, 1));
    t_sphere s = sphere();
    t_intersections xs = intersect(&s, r);

    cr_assert_eq(xs.count, 2, "Expected 2 intersections but got %d.", xs.count);
    cr_assert_float_eq(xs.intersections[0].t, -6.0, 1e-6, "First intersection t value was not 4.0.");
    cr_assert_float_eq(xs.intersections[1].t, -4.0, 1e-6, "Second intersection t value was not 6.0.");

    free(xs.intersections);
}

Test(intersection_tests, encapsulates_t_and_object)
{
    t_sphere s = sphere();
    t_intersection i = intersection(3.5, &s);


    cr_assert_float_eq(i.t, 3.5, 1e-6, "Intersection t value was not set correctly.");
    cr_assert_eq(i.sphere, &s, "Intersection object was not set correctly.");
}
Test(intersection_collections, aggregating_intersections)
{
    t_sphere s = sphere();
    t_intersection intersectionArray[] = {intersection(1, &s), intersection(2, &s)};

    t_intersections xs = intersections(2, intersectionArray);

    cr_assert_eq(xs.count, 2, "The intersection count should be 2.");
    cr_assert_float_eq(xs.intersections[0].t, 1, 1e-6, "First intersection's t value should be 1.");
    cr_assert_float_eq(xs.intersections[1].t, 2, 1e-6, "Second intersection's t value should be 2.");

    free(xs.intersections);
}

Test(intersection_operations, intersect_sets_object_on_intersection)
{
    t_sphere s = sphere();
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_intersections xs = intersect(&s, r);

    cr_assert_eq(xs.count, 2, "Intersection count should be 2.");
    cr_assert_eq(xs.intersections[0].sphere, &s, "First intersection object did not match.");
    cr_assert_eq(xs.intersections[1].sphere, &s, "Second intersection object did not match.");

    if (xs.intersections != NULL)
        free(xs.intersections);
}

Test(intersection_hit, all_intersections_positive_t)
{
    t_sphere s = sphere();
    t_intersection intersectionsArray[] = {intersection(1, &s), intersection(2, &s)};
    t_intersections xs = intersections(2, intersectionsArray);

    t_intersection *i = hit(&xs);
    cr_assert(i != NULL, "Expected a hit but got NULL.");
    cr_assert_float_eq(i->t, 1, 1e-6, "The hit should be at t=1.");
    
    free(xs.intersections);
}

Test(hit_tests, hit_with_some_negative_t)
{
    t_sphere s = sphere();
    t_intersection i1 = intersection(-1, &s);
    t_intersection i2 = intersection(1, &s);
    t_intersection all_intersections[] = {i1, i2};
    t_intersections xs = intersections(2, all_intersections);

    t_intersection *hit_result = hit(&xs);
    cr_assert_not_null(hit_result, "Expected a hit but got NULL.");
    cr_assert_float_eq(hit_result->t, 1, 1e-6, "The hit should be at t=1.");

    free(xs.intersections);
}

Test(hit_tests, hit_with_all_negative_t)
{
    t_sphere s = sphere();
    t_intersection i1 = intersection(-2, &s);
    t_intersection i2 = intersection(-1, &s);
    t_intersection all_intersections[] = {i1, i2};
    t_intersections xs = intersections(2, all_intersections);

    t_intersection *hit_result = hit(&xs);
    cr_assert_null(hit_result, "Expected no hit but got one.");

    free(xs.intersections);
}

Test(hit_tests, hit_is_lowest_nonnegative_intersection)
{
    t_sphere s = sphere();
    t_intersection i1 = intersection(5, &s);
    t_intersection i2 = intersection(7, &s);
    t_intersection i3 = intersection(-3, &s);
    t_intersection i4 = intersection(2, &s);
    t_intersection all_intersections[] = {i1, i2, i3, i4};
    t_intersections xs = intersections(4, all_intersections);

    t_intersection *hit_result = hit(&xs);
    cr_assert_not_null(hit_result, "Expected a hit but got NULL.");
    cr_assert_float_eq(hit_result->t, 2, 1e-6, "The hit should be at t=2.");

    free(xs.intersections);
}

Test(ray_transformations, translating_a_ray)
{
    t_ray r = ray(point(1, 2, 3), vector(0, 1, 0));
    t_matrix m = translation(3, 4, 5);

    t_ray r2 = transform(r, m);

    cr_assert(tuple_equals(r2.origin, point(4, 6, 8)), "Translated ray origin did not match expected point.");
    cr_assert(tuple_equals(r2.direction, vector(0, 1, 0)), "Translated ray direction did not match expected vector.");
}

Test(ray_transformations, scaling_a_ray)
{
    t_ray r = ray(point(1, 2, 3), vector(0, 1, 0));
    t_matrix m = scaling(2, 3, 4);

    t_ray r2 = transform(r, m);

    cr_assert(tuple_equals(r2.origin, point(2, 6, 12)), "Scaled ray origin did not match expected point.");
    cr_assert(tuple_equals(r2.direction, vector(0, 3, 0)), "Scaled ray direction did not match expected vector.");
}

Test(sphere_transformations, sphere_default_transformation)
{
    t_sphere s = sphere();
    t_matrix identity = identity_matrix();
    
    cr_assert(matrices_equal(s.transform, identity), "Sphere's default transformation is not the identity matrix.");
}

Test(sphere_transformations, changing_spheres_transformation)
{
    t_sphere s = sphere();
    t_matrix t = translation(2, 3, 4);
    
    set_transform(&s, t);
    cr_assert(matrices_equal(s.transform, t), "Sphere's transformation was not set correctly.");
}

Test(sphere_intersections, intersecting_a_scaled_sphere_with_a_ray)
{
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_sphere s = sphere();
    set_transform(&s, scaling(2, 2, 2));

    t_intersections xs = intersect(&s, r);

    cr_assert_eq(xs.count, 2, "Expected 2 intersections but got %d.", xs.count);
    cr_assert_float_eq(xs.intersections[0].t, 3, 1e-6, "First intersection t value was not 3.");
    cr_assert_float_eq(xs.intersections[1].t, 7, 1e-6, "Second intersection t value was not 7.");
    free(xs.intersections);
}

Test(sphere_intersections, intersecting_a_translated_sphere_with_a_ray)
{
    t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
    t_sphere s = sphere();
    set_transform(&s, translation(5, 0, 0));

    t_intersections xs = intersect(&s, r);

    cr_assert_eq(xs.count, 0, "Expected 0 intersections but got %d.", xs.count);

}


Test(sphere_normals, normal_on_sphere_at_point_on_x_axis)
{
    t_sphere s = sphere();
    t_tuple point = {1, 0, 0, 1};
    t_tuple expected = {1, 0, 0, 0};
    t_tuple normal = normal_at(s, point);
    cr_assert_eq(normal.x, expected.x);
    cr_assert_eq(normal.y, expected.y);
    cr_assert_eq(normal.z, expected.z);
}

Test(sphere_normals, normal_on_sphere_at_point_on_y_axis)
{
    t_sphere s = sphere();
    t_tuple point = {0, 1, 0, 1};
    t_tuple expected = {0, 1, 0, 0};
    t_tuple normal = normal_at(s, point);
    cr_assert_eq(normal.x, expected.x);
    cr_assert_eq(normal.y, expected.y);
    cr_assert_eq(normal.z, expected.z);
}

Test(sphere_normals, normal_on_sphere_at_point_on_z_axis)
{
    t_sphere s = sphere();
    t_tuple point = {0, 0, 1, 1};
    t_tuple expected = {0, 0, 1, 0};
    t_tuple normal = normal_at(s, point);
    cr_assert_eq(normal.x, expected.x);
    cr_assert_eq(normal.y, expected.y);
    cr_assert_eq(normal.z, expected.z);
}

Test(sphere_normals, normal_on_sphere_at_nonaxial_point)
{
    t_sphere s = sphere();
    double val = sqrt(3) / 3;
    t_tuple point = {val, val, val, 1};
    t_tuple expected = {val, val, val, 0};
    t_tuple normal = normal_at(s, point);
    cr_assert_float_eq(normal.x, expected.x, 1e-6);
    cr_assert_float_eq(normal.y, expected.y, 1e-6);
    cr_assert_float_eq(normal.z, expected.z, 1e-6);
}

Test(sphere_normals, normal_is_a_normalized_vector)
{
    t_sphere s = sphere();
    double val = sqrt(3) / 3;
    t_tuple point = {val, val, val, 1};
    t_tuple normal = normal_at(s, point);
    t_tuple normalized_normal = normalize(normal); 
    cr_assert_float_eq(normal.x, normalized_normal.x, 1e-6);
    cr_assert_float_eq(normal.y, normalized_normal.y, 1e-6);
    cr_assert_float_eq(normal.z, normalized_normal.z, 1e-6);
}

Test(matrix_transformations, rotating_point_around_z_axis)
{

    t_tuple p = {0, 1, 0, 1};

    t_matrix half_quarter = rotation_z(M_PI / 4);
    t_matrix full_quarter = rotation_z(M_PI / 2);


    t_tuple expected_half = {-sqrt(2)/2, sqrt(2)/2, 0, 1};
    t_tuple expected_full = {-1, 0, 0, 1};
    
    t_tuple result_half = multiply_matrix_tuple(half_quarter, p);
    t_tuple result_full = multiply_matrix_tuple(full_quarter, p);

    cr_assert_float_eq(result_half.x, expected_half.x, 1e-6);
    cr_assert_float_eq(result_half.y, expected_half.y, 1e-6);
    cr_assert_float_eq(result_half.z, expected_half.z, 1e-6);

    cr_assert_float_eq(result_full.x, expected_full.x, 1e-6);
    cr_assert_float_eq(result_full.y, expected_full.y, 1e-6);
    cr_assert_float_eq(result_full.z, expected_full.z, 1e-6);
}


Test(sphere_transformed_normals, normal_on_translated_sphere)
{
    t_sphere s = sphere();
    set_transform(&s, translation(0, 1, 0));
    t_tuple point = {0, 1.70711, -0.70711, 1};
    t_tuple expected_normal = {0, 0.70711, -0.70711, 0};
    t_tuple normal = normal_at(s, point);

    cr_assert_float_eq(normal.x, expected_normal.x, 1e-5);
    cr_assert_float_eq(normal.y, expected_normal.y, 1e-5);
    cr_assert_float_eq(normal.z, expected_normal.z, 1e-5);
}

Test(sphere_transformed_normals, normal_on_transformed_sphere)
{
    t_sphere s = sphere();
    t_matrix m = multiply_matrices(scaling(1, 0.5, 1), rotation_z(M_PI / 5));
    set_transform(&s, m);
    double sqrt2over2 = sqrt(2) / 2;
    t_tuple point = {0, sqrt2over2, -sqrt2over2, 1};
    t_tuple expected_normal = {0, 0.97014, -0.24254, 0};
    t_tuple normal = normal_at(s, point);

    cr_assert_float_eq(normal.x, expected_normal.x, 1e-5);
    cr_assert_float_eq(normal.y, expected_normal.y, 1e-5);
    cr_assert_float_eq(normal.z, expected_normal.z, 1e-5);
}

Test(reflection, vector_approaching_at_45_degrees)
{
    t_tuple v = {1, -1, 0, 0};
    t_tuple n = {0, 1, 0, 0};
    t_tuple expected = {1, 1, 0, 0};

    t_tuple r = reflect(v, n);

    cr_assert_float_eq(r.x, expected.x, 1e-6, "Expected x component: %f, but got: %f", expected.x, r.x);
    cr_assert_float_eq(r.y, expected.y, 1e-6, "Expected y component: %f, but got: %f", expected.y, r.y);
    cr_assert_float_eq(r.z, expected.z, 1e-6, "Expected z component: %f, but got: %f", expected.z, r.z);
}
Test(reflection, Reflecting_a_vector_off_a_slanted_surface)
{
    t_tuple v = {0, -1, 0, 0};
    double sqrt2over2 = sqrt(2) / 2;
    t_tuple n = {sqrt2over2, sqrt2over2, 0, 0};
    t_tuple expected = {1, 0, 0, 0};

    t_tuple r = reflect(v, n);

    cr_assert_float_eq(r.x, expected.x, 1e-6, "Expected x component: %f, but got: %f", expected.x, r.x);
    cr_assert_float_eq(r.y, expected.y, 1e-6, "Expected y component: %f, but got: %f", expected.y, r.y);
    cr_assert_float_eq(r.z, expected.z, 1e-6, "Expected z component: %f, but got: %f", expected.z, r.z);
}

// Test(light_attributes, point_light_has_position_intensity_and_color)
// {
//     t_vector position = {0, 0, 0};
//     double intensity = 1.0;      
//     int color[3] = {255, 255, 255};


//     t_light light = point_light(position, intensity, color);

//     cr_assert_eq(light.position.x, position.x, "Light position x did not match");
//     cr_assert_eq(light.position.y, position.y, "Light position y did not match");
//     cr_assert_eq(light.position.z, position.z, "Light position z did not match");
//     cr_assert_eq(light.intensity, intensity, "Light intensity did not match");
//     cr_assert_eq(light.color[0], color[0], "Light color red did not match");
//     cr_assert_eq(light.color[1], color[1], "Light color green did not match");
//     cr_assert_eq(light.color[2], color[2], "Light color blue did not match");
// }

Test(default_material, material_properties)
{
    t_material m = material();

    cr_assert_eq(m.color.red, 1, "Expected default color red component to be 1");
    cr_assert_eq(m.color.green, 1, "Expected default color green component to be 1");
    cr_assert_eq(m.color.blue, 1, "Expected default color blue component to be 1");
    cr_assert_float_eq(m.ambient, 0.1, 1e-6, "Expected default ambient to be 0.1");
    cr_assert_float_eq(m.diffuse, 0.9, 1e-6, "Expected default diffuse to be 0.9");
    cr_assert_float_eq(m.specular, 0.9, 1e-6, "Expected default specular to be 0.9");
    cr_assert_float_eq(m.shininess, 200.0, 1e-6, "Expected default shininess to be 200.0");
}

Test(sphere_properties, sphere_has_default_material)
{
    t_sphere s = sphere();
    t_material default_mat = material();

    cr_assert_float_eq(s.material.ambient, default_mat.ambient, 1e-6, "Ambient property mismatch.");
    cr_assert_float_eq(s.material.diffuse, default_mat.diffuse, 1e-6, "Diffuse property mismatch.");
}

Test(sphere_properties, sphere_can_be_assigned_material)
{
    t_sphere s = sphere();
    t_material m = material();
    m.ambient = 1;

    s.material = m;

    cr_assert_eq(s.material.ambient, m.ambient, "Failed to assign custom material to sphere.");
}

Test(sphere_properties, sphere_material_assignment)
{
    t_sphere s = sphere();
    t_material m = material();
    m.ambient = 1.0;

    s.material = m;

    cr_assert_float_eq(s.material.ambient, m.ambient, 1e-6, "Failed to correctly assign custom material's ambient property to the sphere.");
}

Test(lighting_scenarios, lighting_with_eye_between_light_and_surface)
{
    t_material m = material();
    t_tuple position = {0, 0, 0, 1};

    t_tuple eyev = {0, 0, -1, 0};
    t_tuple normalv = {0, 0, -1, 0};
    t_light light = {
        .position = {0, 0, -10},
        .intensity = {1, 1, 1}
    };

    t_color result = lighting(m, light, position, eyev, normalv);


    t_color expected = {1.9f, 1.9f, 1.9f}; 
    cr_assert_float_eq(result.red, expected.red, 1e-6, "Red component mismatch.");
    cr_assert_float_eq(result.green, expected.green, 1e-6, "Green component mismatch.");
    cr_assert_float_eq(result.blue, expected.blue, 1e-6, "Blue component mismatch.");
}

Test(lighting_scenarios, lighting_with_eye_opposite_surface_light_offset_45)
{
    t_material m = material();
    t_tuple position = {0, 0, 0, 1};
    t_tuple eyev = {0, 0, -1, 0};
    t_tuple normalv = {0, 0, -1, 0};
    t_light light = {
        .position = {0, 10, -10},
        .intensity = {1, 1, 1}
    };

    t_color result = lighting(m, light, position, eyev, normalv);
    t_color expected = {0.7364f, 0.7364f, 0.7364f};

    cr_assert_float_eq(result.red, expected.red, 1e-4);
    cr_assert_float_eq(result.green, expected.green, 1e-4);
    cr_assert_float_eq(result.blue, expected.blue, 1e-4);
}

Test(lighting_scenarios, lighting_with_eye_in_path_of_reflection_vector)
{
    t_material m = material();
    t_tuple position = {0, 0, 0, 1};
    t_tuple eyev = {0, -sqrt(2)/2, -sqrt(2)/2, 0};
    t_tuple normalv = {0, 0, -1, 0};
    t_light light = {
        .position = {0, 10, -10},
        .intensity = {1, 1, 1}
    };

    t_color result = lighting(m, light, position, eyev, normalv);
    t_color expected = {1.6364f, 1.6364f, 1.6364f};

    cr_assert_float_eq(result.red, expected.red, 1e-4);
    cr_assert_float_eq(result.green, expected.green, 1e-4);
    cr_assert_float_eq(result.blue, expected.blue, 1e-4);
}

Test(lighting_scenarios, lighting_with_light_behind_surface)
{
    t_material m = material();
    t_tuple position = {0, 0, 0, 1};
    t_tuple eyev = {0, 0, -1, 0};
    t_tuple normalv = {0, 0, -1, 0};
    t_light light = {
        .position = {0, 0, 10},
        .intensity = {1, 1, 1}
    };

    t_color result = lighting(m, light, position, eyev, normalv);
    t_color expected = {0.1f, 0.1f, 0.1f};

    cr_assert_float_eq(result.red, expected.red, 1e-4);
    cr_assert_float_eq(result.green, expected.green, 1e-4);
    cr_assert_float_eq(result.blue, expected.blue, 1e-4);
}

Test(world_tests, creating_a_world)
{

    t_world w = world();

    cr_assert_null(w.objects, "World should contain no objects upon initialization.");
    cr_assert_eq(w.object_count, 0, "World's object count should be 0 upon initialization.");

    cr_assert_null(w.light, "World should have no light source upon initialization.");
}


// Test(default_world_intersections, should_return_expected_values)
// {
//     t_vector l = tuple_to_vector(vector(-10, 10, -10));
//     int     colors[3] = {1, 1, 1};
//     t_light light = point_light(l, 1, colors);

//     t_sphere s1 = sphere();
//     s1.material.color[0] = 0.8;
//     s1.material.color[1] = 1.0; 
//     s1.material.color[2] = 0.6;
//     s1.material.diffuse = 0.7;
//     s1.material.specular = 0.2;

//     t_sphere s2 = sphere();
//     s2.transform = scaling(0.5, 0.5, 0.5);

//     t_world w;
//     w.light = &light;
//     w.object_count = 2;
//     w.objects = malloc(sizeof(t_object) * 2);
//     w.objects[0].data = &s1;
//     w.objects[1].data = &s2;

//     t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
//     t_intersections xs = intersect_world(&w, r);

//     cr_assert_eq(xs.count, 4, "Expected 4 intersections, got %d", xs.count);
//     cr_assert_float_eq(xs.intersections[0].t, 4.0, 0.0001, "Expected t = 4, got %f", xs.intersections[0].t);
//     cr_assert_float_eq(xs.intersections[1].t, 4.5, 0.0001, "Expected t = 4.5, got %f", xs.intersections[1].t);
//     cr_assert_float_eq(xs.intersections[2].t, 5.5, 0.0001, "Expected t = 5.5, got %f", xs.intersections[2].t);
//     cr_assert_float_eq(xs.intersections[3].t, 6.0, 0.0001, "Expected t = 6, got %f", xs.intersections[3].t);

// }

// Test(precomputations, precomputing_the_state_of_an_intersection)
// {
//     t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
//     t_sphere shape = sphere();
//     t_intersection i = intersection(4, &shape);
    
//     t_comps comps = prepare_computations(i, r);

//     cr_assert_float_eq(comps.t, i.t, 1e-6, "Expected comps.t to equal i.t");
//     cr_assert(comps.sphere == i.sphere, "Expected comps.object to equal i.object");
    
//     cr_assert_float_eq(comps.point.x, 0, 1e-6, "Expected comps.point.x to be 0");
//     cr_assert_float_eq(comps.point.y, 0, 1e-6, "Expected comps.point.y to be 0");
//     cr_assert_float_eq(comps.point.z, -1, 1e-6, "Expected comps.point.z to be -1");

//     cr_assert_float_eq(comps.eyev.x, 0, 1e-6, "Expected comps.eyev.x to be 0");
//     cr_assert_float_eq(comps.eyev.y, 0, 1e-6, "Expected comps.eyev.y to be 0");
//     cr_assert_float_eq(comps.eyev.z, -1, 1e-6, "Expected comps.eyev.z to be -1");

//     cr_assert_float_eq(comps.normalv.x, 0, 1e-6, "Expected comps.normalv.x to be 0");
//     cr_assert_float_eq(comps.normalv.y, 0, 1e-6, "Expected comps.normalv.y to be 0");
//     cr_assert_float_eq(comps.normalv.z, -1, 1e-6, "Expected comps.normalv.z to be -1");
// }

// Test(precomputations, The_hit_when_an_intersection_occurs_on_the_outside)
// {
//     t_ray r = ray(point(0, 0, -5), vector(0, 0, 1));
//     t_sphere shape = sphere();
//     t_intersection i = intersection(4, &shape);
            
//     t_comps comps = prepare_computations(i, r);

//     cr_assert(comps.inside == 0, "Expected comps.object to equal i.object");
// }

// Test(precomputations, the_hit_when_an_intersection_occurs_on_the_outside)
// {
//     t_ray r = ray(point(0, 0, 0), vector(0, 0, 1));
//     t_sphere shape = sphere();
//     t_intersection i = intersection(1, &shape);
    
//     t_comps comps = prepare_computations(i, r);

//     cr_assert_float_eq(comps.t, i.t, 1e-6, "Expected comps.t to equal i.t");
//     cr_assert(comps.sphere == i.sphere, "Expected comps.object to equal i.object");
    
//     cr_assert_float_eq(comps.point.x, 0, 1e-6, "Expected comps.point.x to be 0");
//     cr_assert_float_eq(comps.point.y, 0, 1e-6, "Expected comps.point.y to be 0");
//     cr_assert_float_eq(comps.point.z, 1, 1e-6, "Expected comps.point.z to be -1");

//     cr_assert_float_eq(comps.eyev.x, 0, 1e-6, "Expected comps.eyev.x to be 0");
//     cr_assert_float_eq(comps.eyev.y, 0, 1e-6, "Expected comps.eyev.y to be 0");
//     cr_assert_float_eq(comps.eyev.z, -1, 1e-6, "Expected comps.eyev.z to be -1");

//     cr_assert_float_eq(comps.normalv.x, 0, 1e-6, "Expected comps.normalv.x to be 0");
//     cr_assert_float_eq(comps.normalv.y, 0, 1e-6, "Expected comps.normalv.y to be 0");
//     cr_assert_float_eq(comps.normalv.z, -1, 1e-6, "Expected comps.normalv.z to be -1");

//     cr_assert(comps.inside == 1, "Expected comps.inside to be true");
// }


