/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:04:07 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/14 18:43:29 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_sphere g_sphere;
t_plane g_plane;
t_light g_light;

void	move_camera(t_camera *cam, t_vector direction, double distance)
{
	t_vector	displacement;

	displacement = vector_scale(normalize(direction), distance);
	cam->position = vector_add(cam->position, displacement);
}

void	rotate_camera(t_camera *cam, t_vector axis, double angle)
{
	double		rad;
	t_vector	direction;

	// simplification. La rotation réelle autour d'un axe arbitraire
	// nécessiterait l'utilisation de quaternions ou de matrices de rotation.
	// exemple simplifié pour la rotation autour de l'axe Y :
	(void)axis;
	rad = angle * M_PI / 180;
	direction = cam->orientation;
	direction.x = direction.x * cos(rad) + direction.z * sin(rad);
	direction.z = -direction.x * sin(rad) + direction.z * cos(rad);
	cam->orientation = normalize(direction);
}
int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 'w')
		vars->camera.fov = fmax(30, vars->camera.fov - 5);
	else if (keycode == 's')
		vars->camera.fov = fmin(120, vars->camera.fov + 5);
	render_scene(vars, g_sphere, g_plane, g_light);
	return (0);
}
