/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:32:25 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 11:36:07 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "all.h"

//*--------------------- 🪩 Ray-Tracing 🪩 --------------------*//

// todo               ~~~      Rays       ~~~                  *//
typedef struct s_ray
{
	t_tuple			origin;
	t_tuple			direction;
}					t_ray;

t_ray				transform(t_ray ray, t_matrix m);
t_ray				ray(t_tuple origin, t_tuple direction);
t_tuple				position(t_ray r, double t);

// todo               ~~~  Intersections  ~~~                  *//

typedef union s_object_union
{
	t_sphere		*sphere;
	t_plane			*plane;
	t_cylinder		*cylinder;
	t_cone			*cone;
}					t_object_union;
typedef struct s_intersection
{
	double			t;
	t_object_union	object;
	t_id_type		type;
}					t_intersection;

typedef struct s_intersections
{
	t_intersection	*intersections;
	int				count;
	int				capacity;
}					t_intersections;

t_intersection		intersection(double t, t_sphere *object);
t_intersections		intersect_sphere(t_sphere *s, t_ray r);
t_intersection		*hit(t_intersections *xs);

// todo               ~~~  Intersect handle  ~~~                  *//
void				add_intersection(t_intersections *xs, t_intersection inter);
int					compare_intersections(const void *a, const void *b);
void				sort_intersections(t_intersections *intersections);

// todo               ~~~     Material		~~~               *//

typedef struct s_material
{
	t_color			color;
	double			ambient;
	double			diffuse;
	double			specular;
	double			shininess;
	t_pattern		*pattern;
	t_texture		*texture;
}					t_material;

t_material			material(void);

// todo              ~~~      	Light			~~~              	*//
typedef struct s_light
{
	t_tuple			position;
	t_color			intensity;
	double			energy;
}					t_light;

t_light				point_light(t_tuple position, t_color intensity);
t_color				lighting(t_material m, t_light light, t_comps comps,
						int in_shadow);

// todo               ~~~     	Scene			~~~       			*//
typedef struct s_scene_state
{
	int				ambient_light_found;
	int				camera_found;
}					t_scene_state;

typedef struct s_ambient
{
	double			ratio;
	t_color			color;
}					t_ambient;

#endif
