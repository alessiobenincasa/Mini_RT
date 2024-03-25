/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_basic_operations.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/25 11:13:00 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_matrix	create_matrix(int rows, int cols, float elements[]);
void		free_matrix(t_matrix *m);
float		get_element(t_matrix m, int row, int col);
int			matrices_equal(t_matrix a, t_matrix b);
t_matrix	transpose_matrix(t_matrix matrix);