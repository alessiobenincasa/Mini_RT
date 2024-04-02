/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:50:11 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/02 16:50:53 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	check_oneone(t_tuple tup)
{
	if (tup.x < -1 || tup.x > 1)
		return (1);
	else if (tup.y < -1 || tup.y > 1)
		return (2);
	else if (tup.z < -1 || tup.z > 1)
		return (3);
	return (0);
}

int	get_coordinates(char *value, char **line, t_tuple *coordinates)
{
	get_next_value(&value, line);
	if (value == NULL)
		return (1);
	parse_coordinates(value, coordinates);
	free(value);
	return (0);
}

int	get_float_val(char *value, char **line, double *save)
{
	get_next_value(&value, line);
	if (value == NULL)
		return (1);
	*save = ft_atof(value);
	free(value);
	return (0);
}

int	get_char_val(char *value, char **line, char **save)
{
	get_next_value(&value, line);
	if (value == NULL)
		return (1);
	*save = ft_strdup(value);
	free(value);
	return (0);
}

t_matrix	ro_tr(t_tuple dir, t_tuple cent, t_matrix trans)
{
	t_matrix	rotation;
	t_matrix	result;

	rotation = multiply_matrices(rotation_x(dir.x),
			multiply_matrices(rotation_y(dir.y), rotation_z(dir.z)));
	result = multiply_matrices(rotation, trans);
	result = multiply_matrices(translation(cent.x, cent.y, cent.z), result);
	return (result);
}
