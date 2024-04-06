/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:53:07 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 11:36:13 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "all.h"

//*----------------------- 🌀 Shapes 🌀 -----------------------*//

int				is_shape(t_id_type type);

// todo               ~~~    Spheres 	  ~~~                  *//
typedef struct s_sphere
{
	t_tuple		center;
	double		radius;
	t_material	material;
	t_matrix	transform;
	t_tuple		scale;
	char		*motif;
}				t_sphere;

t_sphere		sphere(void);
t_tuple			normal_at(t_sphere sphere, t_tuple p);

// todo               ~~~     Planes 	  ~~~                  *//
typedef struct s_plane
{
	t_tuple		point;
	t_tuple		normal;
	t_material	material;
	t_matrix	transform;
}				t_plane;

t_intersections	intersect_plane(t_plane *p, t_ray r);
t_plane			plane(void);

// todo               ~~~    Cylinder 	  ~~~                  *//

typedef struct s_cylinder
{
	t_tuple		center;
	t_tuple		direction;
	double		diameter;

	t_matrix	transform;
	double		minimum;
	double		maximum;
	int			closed;
	t_material	material;
}				t_cylinder;

t_cylinder		cylinder(void);
t_intersections	intersect_cylinder(t_cylinder *cyl, t_ray r);
t_tuple			local_normal_at_cylinder(t_cylinder cylinder, t_tuple point);
t_tuple			normal_at_cylinder(t_cylinder cylinder, t_tuple p);
void			add_intersection_cylinder(t_intersections *xs, double t,
					t_cylinder *cyl);
int				check_cap(t_ray ray, double t, double radius);

// todo               ~~~    	Cone 	  ~~~                  *//

typedef struct s_cone
{
	t_tuple		center;
	t_tuple		direction;
	int			inverted;

	t_matrix	transform;
	double		minimum;
	double		maximum;
	int			closed;
	t_material	material;
}				t_cone;

t_cone			cone(void);
t_tuple			local_normal_at_cone(t_cone cylinder, t_tuple point);
int				check_cap_cone(t_ray ray, double t, t_cone *cone, int is_lower);
void			add_intersection_cone(t_intersections *xs, double t,
					t_cone *cone);
t_intersections	intersect_cone(t_cone *cyl, t_ray ray);
t_tuple			normal_at_cone(t_cone cone, t_tuple p);

// todo               ~~~     Utils 	  ~~~                  *//
t_ray			transform_ray(t_ray r, t_matrix id_matrix);

#endif
