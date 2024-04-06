/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrices.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:29:41 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 11:33:24 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

typedef struct s_shear_params
{
	float	xy;
	float	xz;
	float	yx;
	float	yz;
	float	zx;
	float	zy;
}			t_shear_params;

//*---------------------- 🧮 Matrices 🧮 ----------------------*//

// todo           ~~~ Matrix basic operations ~~~				*//
t_matrix	create_matrix(int rows, int cols, float elements[]);
void		free_matrix(t_matrix *m);
float		get_element(t_matrix m, int row, int col);
int			matrices_equal(t_matrix a, t_matrix b);
t_matrix	transpose_matrix(t_matrix matrix);

// todo             ~~~ Matrix transformation ~~~				*//
t_matrix	translation(float x, float y, float z);
t_matrix	scaling(float x, float y, float z);
t_matrix	shearing(t_shear_params params);

// todo              ~~~ Matrix rotations		~~~				*//
t_matrix	rotation_x(float radians);
t_matrix	rotation_y(float radians);
t_matrix	rotation_z(float radians);

// todo          ~~~ Matrix utility functions   ~~~				*//
t_matrix	submatrix(t_matrix matrix, int remove_row, int remove_col);
float		minor_matrix(t_matrix matrix, int row, int col);
float		cofactor(t_matrix matrix, int row, int col);
float		determinant(t_matrix M);

// todo          ~~~ Matrix advanced operations  ~~~			*//
t_matrix	multiply_matrices(t_matrix a, t_matrix b);
t_tuple		mult_mat_tup(t_matrix m, t_tuple t);
t_matrix	inverse(t_matrix A);
int			is_invertible(t_matrix A);
t_matrix	identity_matrix(void);
