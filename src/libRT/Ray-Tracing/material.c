/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/01 17:29:36 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_material	material(void);

t_material	material(void)
{
	t_material m;

	m.color.red = 1;
	m.color.green = 1;
	m.color.blue = 1;
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200.0;
	m.pattern = NULL;
	m.texture = NULL;
	return (m);
}