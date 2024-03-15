/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 16:24:32 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/15 01:43:04 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_sphere g_sphere;
t_plane g_plane;
t_light g_light;

void render_scene(t_vars *vars, t_sphere *sphere, t_plane *plane, t_light *light)
{
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
            
            float t_sphere_value = intersect_ray_sphere(ray, *sphere);
            float t_plane_value = intersect_ray_plane(ray, *plane);
            int color = create_trgb(0, 0, 0, 255);

            if (t_sphere_value < INFINITY && (t_sphere_value < t_plane_value || t_plane_value == INFINITY)) {
                t_vector intersection_point = vector_add(ray.origin, vector_scale(ray.direction, t_sphere_value));
                t_vector normal = normalize(vector_sub(intersection_point, sphere->center));
                t_vector light_dir = normalize(vector_sub(light->position, intersection_point));
                double diff = fmax(dot(normal, light_dir), 0.0) * light->intensity;
                color = adjust_color_by_light(sphere->color, diff);
            } else if (t_plane_value != INFINITY) {
                color = create_trgb(0, plane->color[0], plane->color[1], plane->color[2]);
            }

            my_mlx_pixel_put(vars, x, y, color);
            x++;
        }
        y++;
    }
}

int key_hook(int keycode, t_vars *vars) 
{
    if (keycode == 'w') {
        g_sphere.diameter = fmax(1, g_sphere.diameter + 1);
    } else if (keycode == 's') {
        g_sphere.diameter = fmin(100, g_sphere.diameter - 1);
    }

    render_scene(vars, &g_sphere, &g_plane, &g_light);
    mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img_ptr, 0, 0);
    return 0;
}

int main(void)
{
    t_vars vars;
    g_sphere = (t_sphere){
        .center = {0, 0, -20},
        .diameter = 10.0,
        .color = {255, 0, 0}
    };

    g_plane = (t_plane){
        .point = {0.0, -5.0, 0.0},
        .normal = {0.0, 1.0, 0.0},
        .color = {0, 255, 0}
    };

    g_light = (t_light){
        .position = {-20.0, 20.0, 20.0},
        .intensity = 0.7,
        .color = {255, 255, 255}
    };
    vars.camera.fov = 90;
    
    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "MiniRT - Scene");
    vars.img.img_ptr = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
    vars.img.addr = mlx_get_data_addr(vars.img.img_ptr, &vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
    mlx_key_hook(vars.win, key_hook, &vars);
    render_scene(&vars, &g_sphere, &g_plane, &g_light);
    mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
    mlx_loop(vars.mlx);

    return 0;
}