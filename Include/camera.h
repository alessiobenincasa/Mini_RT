/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:59:29 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/05 09:00:04 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

//*----------------------- 📷 Camera 📷 -----------------------*//

typedef struct s_camera
{
	int			hsize;
	int			vsize;
	double		fov;
	t_matrix	transform;
	double		pixel_size;
	double		half_width;
	double		half_height;
	t_tuple		position;
	t_tuple		orientation;
}				t_camera;

t_camera		camera(int hsize, int vsize, double fov);
t_ray			ray_for_pixel(t_camera camera, int px, int py);
t_camera		prepare_camera(t_camera *cam);
