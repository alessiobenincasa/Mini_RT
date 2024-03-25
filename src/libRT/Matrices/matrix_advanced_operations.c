/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_advanced_operations.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/25 11:13:37 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_matrix	multiply_matrices(t_matrix a, t_matrix b);
t_tuple		multiply_matrix_tuple(t_matrix m, t_tuple t);
t_matrix	inverse(t_matrix A);
int			is_invertible(t_matrix A);
t_matrix	identity_matrix(void);
