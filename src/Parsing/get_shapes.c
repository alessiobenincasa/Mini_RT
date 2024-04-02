/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:18:39 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/02 16:50:47 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	handle_motif(t_sphere *s, char *motif, void *mlx)
{
	if (ft_strncmp(motif, "Stripe", 6) == 0)
		s->material.pattern = stripe_pattern(color(1, 1, 1), color(0, 0, 0));
	else if (ft_strncmp(motif, "Earth", 5) == 0)
		s->material.texture = load_texture(mlx, "textures/earth.xpm");
	else
		return (1);
	return (0);
}

t_sphere	*get_sphere_data(char *line, double amb, void *mlx)
{
	t_sphere	*s;
	char		*value;

	s = ft_calloc(1, sizeof(t_sphere));
	if (!s)
		return (NULL);
	*s = sphere();
	s->material.ambient = amb;
	value = NULL;
	if (get_coordinates(value, &line, &(s->center)))
		return (free_s(s), error("Problem getting coordinates"), NULL);
	if (get_float_val(value, &line, &(s->radius)))
		return (free_s(s), error("Problem getting radius"), NULL);
	if (parse_colors(value, &line, &(s->material.color)) != 0)
		return (free_s(s), error("RGB Colors for Sphere are incorrect"), NULL);
	if (get_coordinates(value, &line, &(s->scale)))
		return (s);
	s->transform = scaling(s->scale.x, s->scale.y, s->scale.z);
	if (get_char_val(value, &line, &(s->motif)))
		return (s);
	if (handle_motif(s, s->motif, mlx))
		return (free_s(s), error("Problem handling motif"), NULL);
	return (s);
}

t_plane	*get_plane_data(char *line, double amb)
{
	t_plane	*p;
	char	*value;

	p = ft_calloc(1, sizeof(t_plane));
	if (!p)
		return (NULL);
	*p = plane();
	p->material.ambient = amb;
	value = NULL;
	if (get_coordinates(value, &line, &(p->point)))
		return (free_p(p), error("Problem getting coordinates"), NULL);
	if (get_coordinates(value, &line, &(p->normal)))
		return (free_p(p), error("Problem getting normal"), NULL);
	if (check_oneone(p->normal) != 0)
		return (free_p(p), error("Plane vector value incorrect"), NULL);
	if (parse_colors(value, &line, &(p->material.color)) != 0)
		return (free_p(p), error("RGB Colors for Plane are incorrect"), NULL);
	return (p);
}

t_cylinder	*get_cylinder_data(char *line, double amb)
{
	t_cylinder	*cyl;
	char		*value;

	cyl = ft_calloc(1, sizeof(t_cylinder));
	if (!cyl)
		return (NULL);
	*cyl = cylinder();
	cyl->material.ambient = amb;
	value = NULL;
	if (get_coordinates(value, &line, &(cyl->center)))
		return (free_cyl(cyl), error("Problem getting center"), NULL);
	if (get_coordinates(value, &line, &(cyl->direction)))
		return (free_cyl(cyl), error("Problem getting direction"), NULL);
	if (check_oneone(cyl->direction) != 0)
		return (free_cyl(cyl), error("Cylinder vector value incorrect"), NULL);
	if (get_float_val(value, &line, &(cyl->diameter)))
		return (free_cyl(cyl), error("Problem getting diameter"), NULL);
	if (get_float_val(value, &line, &(cyl->maximum)))
		return (free_cyl(cyl), error("Problem getting maximum"), NULL);
	if (parse_colors(value, &line, &(cyl->material.color)) != 0)
		return (free_cyl(cyl), error("RGB Colors for are incorrect"), NULL);
	cyl->transform = ro_tr(cyl->direction, cyl->center, cyl->transform);
	return (cyl);
}

t_cone	*get_cone_data(char *line, double amb)
{
	t_cone	*co;
	char	*value;

	co = ft_calloc(1, sizeof(t_cone));
	if (!co)
		return (NULL);
	*co = cone();
	co->material.ambient = amb;
	value = NULL;
	if (get_coordinates(value, &line, &(co->center)))
		return (free_c(co), error("Problem getting center"), NULL);
	if (get_coordinates(value, &line, &(co->direction)))
		return (free_c(co), error("Problem getting direction"), NULL);
	if (check_oneone(co->direction) != 0)
		return (free_c(co), error("Cone vector value incorrect"), NULL);
	if (get_float_val(value, &line, &(co->maximum)))
		return (free_c(co), error("Problem getting maximum"), NULL);
	if (parse_colors(value, &line, &(co->material.color)) != 0)
		return (free_c(co), error("RGB Colors for are incorrect"), NULL);
	co->transform = ro_tr(co->direction, co->center, co->transform);
	return (co);
}
