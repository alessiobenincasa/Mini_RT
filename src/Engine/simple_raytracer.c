/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_raytracer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:38:45 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/08 19:19:52 by albeninc         ###   ########.fr       */
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

	oc = vector_sub(ray.origin, sphere.center);
	a = dot(ray.direction, ray.direction);
	b = 2.0 * dot(oc, ray.direction);
	float c = dot(oc, oc) - sphere.diameter * sphere.diameter / 4;
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

void put_pixel(int x, int y, int color[3]);
{

    //Utiliser la MLX pour afficher les pixels. premiere partie simplifier du projet.
}