/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:20:40 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/14 17:29:31 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float intersect_ray_plane(t_ray ray, t_plane plane) {
    float denom = dot(plane.normal, ray.direction);
    if (fabs(denom) > 1e-6) {
        t_vector p0l0 = vector_sub(plane.point, ray.origin);
        float t = dot(p0l0, plane.normal) / denom;
        return (t >= 0.0f) ? t : INFINITY;
    }
    return INFINITY;
}

void render_plane(t_vars *vars, t_plane plane) {
    int color;
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            t_ray ray = {
                .origin = {0, 0, 0},
                .direction = normalize((t_vector){
                    x - WIDTH / 2,
                    y - HEIGHT / 2,
                    -WIDTH / (2 * tan(M_PI / 6))
                })
            };
            float t = intersect_ray_plane(ray, plane);
            if (t < INFINITY) {
                color = create_trgb(0, plane.color[0], plane.color[1], plane.color[2]);
            } else {
                color = create_trgb(0, 20, 20, 20);
            }
            my_mlx_pixel_put(vars, x, y, color);
        }
    }
}



