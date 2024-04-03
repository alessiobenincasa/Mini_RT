/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transformation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/03 14:03:34 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_matrix	translation(float x, float y, float z);
t_matrix	scaling(float x, float y, float z);
t_matrix	shearing(float xy, float xz, float yx, float yz, float zx,
				float zy);

t_matrix translation(float x, float y, float z)
{
    t_matrix transform = {
        .rows = 4,
        .cols = 4,
        .elements = ft_calloc(16, sizeof(float))
    };
    if (!transform.elements)
        exit(EXIT_FAILURE);
    
    int index = 0;
    float elements[] = {
        1, 0, 0, x,
        0, 1, 0, y,
        0, 0, 1, z,
        0, 0, 0, 1
    };
    while (index < 16) 
    {
        transform.elements[index] = elements[index];
        index++;
    }
    return transform;
}

t_matrix scaling(float x, float y, float z)
{
    int i = 0;
    t_matrix scale = {4, 4, ft_calloc(16, sizeof(float))};
    if (!scale.elements)
        exit(EXIT_FAILURE);
    while (i < 16)
    {
        scale.elements[i] = 0;
        i++;
    }
    scale.elements[0] = x;
    scale.elements[5] = y;
    scale.elements[10] = z;
    scale.elements[15] = 1.0;
    return scale;
}


t_matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy)
{
    t_matrix result = {4, 4, ft_calloc(16, sizeof(float))};
    int i = 0;
    if (!result.elements)
        exit(EXIT_FAILURE);
        
    while (i < 16)
    {
        result.elements[i] = 0;
        i++;
    }
    result.elements[0] = 1;
    result.elements[5] = 1;
    result.elements[10] = 1;
    result.elements[15] = 1;


    result.elements[1] = xy; 
    result.elements[2] = xz;
    result.elements[4] = yx;
    result.elements[6] = yz;
    result.elements[8] = zx;
    result.elements[9] = zy;

    return result;
}
