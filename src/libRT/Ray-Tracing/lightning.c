/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/05 09:40:59 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

static t_color	tex_pix(t_texture *t, double u, double v)
{
	t_color	color;
	int		tex_x;
	int		tex_y;

	tex_x = (int)(u * (t->width - 1));
	tex_y = (int)(v * (t->height - 1));
	color = texture_img_get_pxl(t, tex_x, tex_y);
	return (color);
}

static t_color	get_color_at_point(t_material m, t_tuple position)
{
	t_color	color;
	double	u;
	double	v;

	u = 0;
	v = 0;
	if (m.texture != NULL)
	{
		point_on_sphere_to_uv(position, &u, &v);
		color = tex_pix(m.texture, u, v);
	}
	else if (m.pattern != NULL)
		color = stripe_at(m.pattern, position);
	else
		color = m.color;
	return (color);
}

typedef struct s_lustre
{
	t_color		eff;
	t_color		amb;
	t_color		diff;
	t_color		spec;
	t_tuple		lightv;
	t_tuple		reflectv;
	float		norm_light;
	float		refl_eyev;
}				t_lustre;

t_lustre	lustre_init(t_material m, t_tuple point, t_light light)
{
	t_lustre	l;
	t_color		color_at_point;

	color_at_point = get_color_at_point(m, point);
	if (no_world_light(light))
		l.eff = color_at_point;
	else
		l.eff = multiply_colors(color_at_point, light.intensity);
	l.amb = mult_clr_sclr(l.eff, m.ambient);
	l.diff = color(0, 0, 0);
	l.spec = color(0, 0, 0);
	l.lightv = vector(0, 0, 0);
	l.reflectv = vector(0, 0, 0);
	l.norm_light = 0;
	l.refl_eyev = 0;
	return (l);
}

t_color	lighting(t_material m, t_light light, t_comps comps, int in_shadow)
{
	t_lustre	l;
	t_color		total_light;
	
	l = lustre_init(m, comps.point, light);
	total_light = add_three_colors(l.amb, l.diff, l.spec);
	if (in_shadow || no_world_light(light))
		return (total_light);
	l.lightv = normalize(subtract_tuples(light.position, comps.point));
	l.norm_light = dot(l.lightv, comps.normalv);
	if (l.norm_light > 0)
	{
		l.diff = mult_clr_sclr(l.eff, m.diffuse * l.norm_light);
		l.reflectv = reflect(negate_tuple(l.lightv), comps.normalv);
		l.refl_eyev = dot(l.reflectv, comps.eyev);
		if (l.refl_eyev > 0)
		{
			l.spec = mult_clr_sclr(light.intensity, m.specular
					* powf(l.refl_eyev, m.shininess));
		}
	}
	total_light = add_three_colors(l.amb, l.diff, l.spec);
	return (total_light);
}
