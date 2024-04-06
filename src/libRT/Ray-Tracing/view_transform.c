/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:19:48 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 11:25:23 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

typedef struct s_view
{
	t_tuple		forward;
	t_vector	left;
	t_vector	true_up;
}				t_view;

t_view	transform_init(t_tuple from, t_tuple to, t_tuple up)
{
	t_view	data;

	data.forward = normalize(subtract_tuples(to, from));
	data.left = cross(data.forward, normalize(up));
	data.true_up = cross(vector(data.left.x, data.left.y, data.left.z),
			data.forward);
	return (data);
}

t_matrix	view_transform(t_tuple from, t_tuple to, t_tuple up)
{
	t_view		data;
	t_matrix	result;
	float		orientation[16];

	data = transform_init(from, to, up);
	orientation[0] = data.left.x;
	orientation[1] = data.left.y;
	orientation[2] = data.left.z;
	orientation[3] = 0;
	orientation[4] = data.true_up.x;
	orientation[5] = data.true_up.y;
	orientation[6] = data.true_up.z;
	orientation[7] = 0;
	orientation[8] = -(data.forward.x);
	orientation[9] = -(data.forward.y);
	orientation[10] = -(data.forward.z);
	orientation[11] = 0;
	orientation[12] = 0;
	orientation[13] = 0;
	orientation[14] = 0;
	orientation[15] = 1;
	result = create_matrix(4, 4, orientation);
	return (multiply_matrices(result, translation(-from.x, -from.y, -from.z)));
}
