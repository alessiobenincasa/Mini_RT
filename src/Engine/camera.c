/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:04:07 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/12 17:06:58 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	move_camera(t_camera *cam, t_vector direction, double distance)
{
	t_vector	displacement;

	displacement = vector_scale(normalize(direction), distance);
	cam->position = vector_add(cam->position, displacement);
}

void	rotate_camera(t_camera *cam, t_vector axis, double angle)
{
	// simplification. La rotation réelle autour d'un axe arbitraire
	// nécessiterait l'utilisation de quaternions ou de matrices de rotation.
	// exemple simplifié pour la rotation autour de l'axe Y :
	(void)axis;
	double rad = angle * M_PI / 180;
	t_vector direction = cam->orientation;
	direction.x = direction.x * cos(rad) + direction.z * sin(rad);
	direction.z = -direction.x * sin(rad) + direction.z * cos(rad);
	cam->orientation = normalize(direction);
}