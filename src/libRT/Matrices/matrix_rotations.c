/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/02 11:23:19 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_matrix	rotation_x(float radians);
t_matrix	rotation_y(float radians);
t_matrix	rotation_z(float radians);

t_matrix rotation_x(float radians)
{
    t_matrix result = {4, 4, ft_calloc(16, sizeof(float))};
    if (!result.elements)
        exit(EXIT_FAILURE);
        
    int i = 0;
    while (i < 16) {
        result.elements[i] = 0;
        i++;
    }
    result.elements[0] = 1;
    result.elements[5] = cos(radians);
    result.elements[6] = -sin(radians);
    result.elements[9] = sin(radians);
    result.elements[10] = cos(radians);
    result.elements[15] = 1;
    return result;
}
t_matrix rotation_y(float radians)
{
    int i = 0;
    t_matrix result = {4, 4, ft_calloc(16, sizeof(float))};
    if (!result.elements)
        exit(EXIT_FAILURE);

    while (i < 16)
    {
        result.elements[i] = 0;
        i++;
    }
    result.elements[0] = cos(radians);
    result.elements[2] = sin(radians);
    result.elements[5] = 1;
    result.elements[8] = -sin(radians);
    result.elements[10] = cos(radians);
    result.elements[15] = 1;

    return result;
}

t_matrix rotation_z(float radians)
{
    float *elements = NULL;
    
    t_matrix m = create_matrix(4, 4, elements);

    m.elements[0 * m.cols + 0] = cosf(radians);
    m.elements[0 * m.cols + 1] = -sinf(radians);
    m.elements[1 * m.cols + 0] = sinf(radians);
    m.elements[1 * m.cols + 1] = cosf(radians);
    m.elements[2 * m.cols + 2] = 1;
    m.elements[3 * m.cols + 3] = 1;

    return m;
}
