/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylindre.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 16:37:14 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/13 16:37:19 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	intersect_ray_cylinder(t_ray ray, t_cylinder cylinder)
{
	t_vector	oc;
	t_vector	d;
	t_vector	v;
	double		r;
	t_vector	w;
	t_vector	u;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	float		t1;
	float		t2;
	float		t;

	oc = vector_sub(ray.origin, cylinder.center);
	d = ray.direction;
	v = cylinder.direction;
	r = cylinder.diameter / 2;
	w = vector_cross(d, v);
	u = vector_cross(oc, v);
	a = dot(w, w);
	b = 2 * dot(w, u);
	c = dot(u, u) - (r * r * dot(v, v));
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return (INFINITY);
	}
	else
	{
		t1 = (-b - sqrt(discriminant)) / (2.0 * a);
		t2 = (-b + sqrt(discriminant)) / (2.0 * a);
		t = (t1 < t2 && t1 > 0) ? t1 : t2;
		return (t > 0 ? t : INFINITY);
	}
}

void	render_cylinder_basic(t_vars *vars, t_cylinder cylinder)
{
	t_ray	ray;
	float	t;
	int		color;
	int		cylinderColor;

	int y, x;
	cylinderColor = create_trgb(0, 255, 0, 0);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray.origin = (t_vector){0, 0, 0};
			ray.direction = normalize((t_vector){x - WIDTH / 2, y - HEIGHT / 2,
					-WIDTH / (2 * tan(M_PI / 6))});
			t = intersect_ray_cylinder(ray, cylinder);
			if (t < INFINITY)
			{
				color = cylinderColor;
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
