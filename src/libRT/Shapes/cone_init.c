/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 08:48:46 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/05 08:48:54 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

t_cone	cone(void)
{
	t_cone	cone;

	cone.transform = identity_matrix();
	cone.minimum = 0;
	cone.maximum = 3;
	cone.closed = 1;
	cone.inverted = 1;
	cone.material = material();
	cone.material.specular = 0;
	cone.material.diffuse = 0.6;
	cone.material.shininess = 50;
	return (cone);
}
