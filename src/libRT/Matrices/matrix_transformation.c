/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/25 11:13:07 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_matrix	translation(float x, float y, float z);
t_matrix	scaling(float x, float y, float z);
t_matrix	shearing(float xy, float xz, float yx, float yz, float zx,
				float zy);