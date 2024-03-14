/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:24:32 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/14 18:48:32 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void render_scene(t_vars *vars, t_sphere sphere, t_plane plane, t_light light) {
    int y = 0;
    int x;
    while (y < HEIGHT) {
        x = 0;
        while (x < WIDTH) {
            t_ray ray = {
                .origin = {0, 0, 0},
                .direction = normalize((t_vector){
                    x - WIDTH / 2,
                    y - HEIGHT / 2,
                    -WIDTH / (2 * tan(M_PI / 6))
                })
            };
            
            float t_sphere = intersect_ray_sphere(ray, sphere);
            float t_plane = intersect_ray_plane(ray, plane);
            int color = create_trgb(0, 0, 0, 255);

            if (t_sphere < INFINITY && (t_sphere < t_plane || t_plane == INFINITY)) {
                t_vector intersection_point = vector_add(ray.origin, vector_scale(ray.direction, t_sphere));
                t_vector normal = normalize(vector_sub(intersection_point, sphere.center));
                t_vector light_dir = normalize(vector_sub(light.position, intersection_point));
                double diff = fmax(dot(normal, light_dir), 0.0) * light.intensity;
                color = adjust_color_by_light(sphere.color, diff);
            } else if (t_plane != INFINITY) {
                color = create_trgb(0, plane.color[0], plane.color[1], plane.color[2]);
            }

            my_mlx_pixel_put(vars, x, y, color);
            x++;
        }
        y++;
    }
}

int main(void) {
    t_vars vars;
    t_sphere g_sphere = {
        .center = {0, 0, -20},
        .diameter = 10.0,
        .color = {255, 0, 0}
    };

    t_plane g_plane = {
        .point = {0.0, -5.0, 0.0},
        .normal = {0.0, 1.0, 0.0},
        .color = {0, 255, 0}
    };

    t_light g_light = {
        .position = {-20.0, 20.0, 20.0},
        .intensity = 0.7,
        .color = {255, 255, 255},
	};
	vars.camera.fov = 90;
	
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "MiniRT - Scene");
    vars.img.img_ptr = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
    vars.img.addr = mlx_get_data_addr(vars.img.img_ptr, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
    mlx_key_hook(vars.win, key_hook, &vars);
	render_scene(&vars, g_sphere, g_plane, g_light);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
    mlx_loop(vars.mlx);

    return 0;
}


