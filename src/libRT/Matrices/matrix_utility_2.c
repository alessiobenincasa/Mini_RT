/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utility_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:48:13 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/06 12:10:43 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_submatrix_info	init_submatrix_info(t_matrix *sub, const t_matrix *original,
		int remove_row, int remove_col)
{
	t_submatrix_info	info;

	info.sub = sub;
	info.original = original;
	info.remove_row = remove_row;
	info.remove_col = remove_col;
	info.sub_i = 0;
	info.sub_j = 0;
	return (info);
}

void	process_submatrix_row(t_submatrix_info *info, int i)
{
	int	j;

	j = 0;
	info->sub_j = 0;
	while (j < info->original->cols)
	{
		if (j != info->remove_col)
		{
			info->sub->elements[info->sub_i * info->sub->cols
				+ info->sub_j] = info->original->elements[i
				* info->original->cols + j];
			info->sub_j++;
		}
		j++;
	}
}

void	copy_to_submatrix(t_matrix *sub, t_matrix matrix, int remove_row,
		int remove_col)
{
	t_submatrix_info	info;
	int					i;

	info = init_submatrix_info(sub, &matrix, remove_row, remove_col);
	i = 0;
	while (i < matrix.rows)
	{
		if (i != remove_row)
		{
			process_submatrix_row(&info, i);
			info.sub_i++;
		}
		i++;
	}
}

void	transpose_elements(t_matrix *transposed, const t_matrix *matrix)
{
	int	i;
	int	j;
	int	o;
	int	t;

	i = 0;
	while (i < matrix->rows)
	{
		j = 0;
		while (j < matrix->cols)
		{
			o = i * matrix->cols + j;
			t = j * transposed->cols + i;
			transposed->elements[t] = matrix->elements[o];
			j++;
		}
		i++;
	}
}

void	set_shear_params(t_matrix *result, t_shear_params params)
{
	int	i;

	i = 0;
	while (i < 16)
	{
		result->elements[i] = 0;
		i++;
	}
	result->elements[0] = 1;
	result->elements[5] = 1;
	result->elements[10] = 1;
	result->elements[15] = 1;
	result->elements[1] = params.xy;
	result->elements[2] = params.xz;
	result->elements[4] = params.yx;
	result->elements[6] = params.yz;
	result->elements[8] = params.zx;
	result->elements[9] = params.zy;
}
