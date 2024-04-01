/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 09:18:39 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/01 18:21:07 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	check_coordinates(t_tuple vec)
{
	if (vec.x < -1 || vec.x > 1)
		return (1);
	else if (vec.y < -1 || vec.y > 1)
		return (2);
	else if (vec.z < -1 || vec.z > 1)
		return (3);
	return (0);
}

t_sphere	*get_sphere_data(char *line, double amb, void *mlx)
{
	t_sphere	*s;
	char		*value;

	s = malloc(sizeof(t_sphere));
	if (!s)
		return (NULL);
	*s = sphere();
	s->material.ambient = amb;
	get_next_value(&value, &line);
	parse_coordinates(value, &(s->center));
	free(value);
	get_next_value(&value, &line);
	s->radius = ft_atof(value);
	free(value);
	get_next_value(&value, &line);
	if (parse_colors(value, &(s->material.color)) != 0)
		return (free(value), free(s), error("RGB Colors for Sphere are incorrect"), NULL);
	free(value);
	get_next_value(&value, &line);
	if (value == NULL)
		return (s);
	parse_coordinates(value, &(s->scale));
	free(value);
	s->transform = scaling(s->scale.x, s->scale.y, s->scale.z);
	get_next_value(&value, &line);
	if (value == NULL)
		return (s);
	s->motif = ft_strdup(value);
	free(value);
	if (ft_strcmp(s->motif, "Stripe") == 0)
		s->material.pattern = stripe_pattern(color(1,1,1), color(0,0,0));
	else
	{
		t_texture *texture = load_texture(mlx, "textures/earth.xpm");
		s->material.texture = texture;
	}
	return (s);
}

t_plane	*get_plane_data(char *line, double amb)
{
	t_plane	*plane;
	char	*value;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	get_next_value(&value, &line);
	parse_coordinates(value, &(plane->point));
	free(value);
	get_next_value(&value, &line);
	parse_coordinates(value, &(plane->normal));
	free(value);
	if (check_coordinates(plane->normal) != 0)
		return (free(plane), error("Plane vector value incorrect"), NULL);
	get_next_value(&value, &line);
	plane->material = material();
	plane->material.diffuse = 0.6;
	plane->material.specular = 0;
	plane->material.shininess = 50;
	if (parse_colors(value, &(plane->material.color)) != 0)
	{
		free(value);
		free(plane);
		return (error("RGB Colors for Plane are incorrect"), NULL);
	}
	free(value);
	plane->material.ambient = amb;	
	return (plane);
}

t_cylinder	*get_cylinder_data(char *line, double amb)
{
	t_cylinder	*cyl;
	char		*value;

	cyl = malloc(sizeof(t_cylinder));
	if (!cyl)
		return (NULL);
	*cyl = cylinder();
	get_next_value(&value, &line);
	parse_coordinates(value, &(cyl->center));
	free(value);
	get_next_value(&value, &line);
	parse_coordinates(value, &(cyl->direction));
	free(value);
	if (check_coordinates(cyl->direction) != 0)
		return (free(cyl), error("Cylinder vector value incorrect"), NULL);
	get_next_value(&value, &line);
	cyl->diameter = ft_atof(value);
	free(value);
	get_next_value(&value, &line);
	cyl->maximum = ft_atof(value);
	free(value);
	get_next_value(&value, &line);
	if (parse_colors(value, &(cyl->material.color)) != 0)
	{
		free(value);
		free(cyl);
		return (error("RGB Colors for Plane are incorrect"), NULL);
	}
	free(value);
	cyl->material.ambient = amb;

	t_matrix rotation = multiply_matrices(rotation_x(cyl->direction.x), multiply_matrices(rotation_y(cyl->direction.y), rotation_z(cyl->direction.z)));
	cyl->transform = multiply_matrices(rotation, cyl->transform);
	cyl->transform = multiply_matrices(translation(cyl->center.x, cyl->center.y, cyl->center.z), cyl->transform);
	
	return (cyl);
}

t_cone	*get_cone_data(char *line, double amb)
{
	t_cone		*co;
	char		*value;

	co = malloc(sizeof(t_cone));
	if (!co)
		return (NULL);
	*co = cone();
	get_next_value(&value, &line);
	parse_coordinates(value, &(co->center));
	free(value);
	get_next_value(&value, &line);
	parse_coordinates(value, &(co->direction));
	free(value);
	if (check_coordinates(co->direction) != 0)
		return (free(co), error("Cone vector value incorrect"), NULL);
	get_next_value(&value, &line);
	co->maximum = ft_atof(value);
	free(value);
	get_next_value(&value, &line);
	if (parse_colors(value, &(co->material.color)) != 0)
	{
		free(value);
		free(co);
		return (error("RGB Colors for Plane are incorrect"), NULL);
	}
	free(value);
	co->material.ambient = amb;

	t_matrix rotation = multiply_matrices(rotation_x(co->direction.x), multiply_matrices(rotation_y(co->direction.y), rotation_z(co->direction.z)));
	co->transform = multiply_matrices(rotation, co->transform);
	co->transform = multiply_matrices(translation(co->center.x, co->center.y, co->center.z), co->transform);

	return (co);
}
