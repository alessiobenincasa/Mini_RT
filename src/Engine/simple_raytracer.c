/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_raytracer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:38:45 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/14 10:37:06 by svolodin         ###   ########.fr       */
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

void	render(t_vars *vars, t_sphere sphere, t_light light)
{
	t_ray		ray;
	float		t;
	int			color;
	int			y;
	int			x;
	t_vector	intersection_point;
	t_vector	normal;
	t_vector	light_dir;
	double		diff;
	int			r;
	int			g;
	int			b;

	
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray.origin = (t_vector){0, 0, 0};
			ray.direction = normalize((t_vector){x - WIDTH / 2, y - HEIGHT / 2,
					-WIDTH / (2 * tan(M_PI / 6))});
			t = intersect_ray_sphere(ray, sphere);
			if (t < INFINITY)
			{
				intersection_point = vector_add(ray.origin,
						vector_scale(ray.direction, t));
				normal = normalize(vector_sub(intersection_point,
							sphere.center));
				light_dir = normalize(vector_sub(light.position,
							intersection_point));
				diff = fmax(dot(normal, light_dir), 0.0);
				r = fmin(sphere.color[0] * diff * light.intensity, 255);
				g = fmin(sphere.color[1] * diff * light.intensity, 255);
				b = fmin(sphere.color[2] * diff * light.intensity, 255);
				color = create_trgb(0, r, g, b);
			}
			else
			{
				color = create_trgb(0, 20, 20, 20);
			}
			my_mlx_pixel_put(vars, x, y, color);
			x++;
		}
		y++;
	}
}
