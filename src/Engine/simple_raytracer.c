/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_raytracer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:38:45 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/08 19:49:38 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	vector_add(t_vector a, t_vector b)
{
	return ((t_vector){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vector	vector_sub(t_vector a, t_vector b)
{
	return ((t_vector){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vector	vector_scale(t_vector v, double s)
{
	return ((t_vector){v.x * s, v.y * s, v.z * s});
}

double	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	norm(t_vector v)
{
	return (sqrt(dot(v, v)));
}

t_vector	normalize(t_vector v)
{
	double	n;

	n = norm(v);
	return (vector_scale(v, 1 / n));
}

float	intersect_ray_sphere(t_ray ray, t_sphere sphere)
{
	t_vector	oc;
	float		a;
	float		b;
	float		discriminant;
	float		t1;
	float		t2;
	float		t;
	float		c;

	oc = vector_sub(ray.origin, sphere.center);
	a = dot(ray.direction, ray.direction);
	b = 2.0 * dot(oc, ray.direction);
	c = dot(oc, oc) - sphere.diameter * sphere.diameter / 4;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (INFINITY);
	else
	{
		t1 = (-b - sqrt(discriminant)) / (2.0 * a);
		t2 = (-b + sqrt(discriminant)) / (2.0 * a);
		t = (t1 < t2 && t1 > 0) ? t1 : t2;
		return (t > 0 ? t : INFINITY);
	}
}

void	render(t_vars *vars, t_sphere sphere)
{
	t_ray	ray;
	float	t;
    int y;
    int x;

    y = 0;
    x = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			ray.origin = (t_vector){0, 0, 0};
			ray.direction = normalize((t_vector){x - WIDTH / 2, y - HEIGHT / 2,
					-WIDTH / (2 * tan(M_PI / 6))});
			t = intersect_ray_sphere(ray, sphere);
			if (t < INFINITY)
			{
				my_mlx_pixel_put(vars, x, y, sphere.color);
			}
            x++;
		}
        y++;
	}
}

int	main(void)
{
	t_vars vars;
	t_sphere sphere = {{0, 0, -50}, 20, 0xFF0000};

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "MiniRT");
	vars.img.img_ptr = mlx_new_image(vars.mlx, WIDTH, HEIGHT);
	vars.img.addr = mlx_get_data_addr(vars.img.img_ptr,
			&vars.img.bits_per_pixel, &vars.img.line_length, &vars.img.endian);
	render(&vars, sphere);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img.img_ptr, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}