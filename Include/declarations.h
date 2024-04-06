/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   declarations.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:49:58 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 11:50:51 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECLARATIONS_H
# define DECLARATIONS_H

//*------------------ 📜 Pre-declarations 📜 -------------------*//

typedef struct s_ambient		t_ambient;
typedef struct s_camera			t_camera;
typedef struct s_canvas			t_canvas;
typedef struct s_color			t_color;
typedef struct s_cone			t_cone;
typedef struct s_comps			t_comps;
typedef struct s_cylinder		t_cylinder;
typedef struct s_img			t_img;
typedef struct s_init			t_init;
typedef struct s_intersection	t_intersection;
typedef struct s_intersections	t_intersections;
typedef struct s_light			t_light;
typedef struct s_material		t_material;
typedef struct s_matrix			t_matrix;
typedef struct s_object			t_object;
typedef union s_object_union	t_object_union;
typedef struct s_pattern		t_pattern;
typedef struct s_plane			t_plane;
typedef struct s_ray			t_ray;
typedef struct s_scene_data		t_scene_data;
typedef struct s_scene_state	t_scene_state;
typedef struct s_sphere			t_sphere;
typedef struct s_texture		t_texture;
typedef struct s_tuple			t_tuple;
typedef struct s_vector			t_vector;
typedef struct s_vars			t_vars;
typedef struct s_world			t_world;

// todo               ~~~     Tuples 		~~~						*//
typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}								t_tuple;

// todo               ~~~     Matrix 		~~~						*//
typedef struct s_matrix
{
	int							rows;
	int							cols;
	float						*elements;

}								t_matrix;

#endif