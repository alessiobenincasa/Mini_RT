/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:53:00 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 08:00:39 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

//*--------------------- 📚 𝙇𝙄𝘽𝙍𝘼𝙍𝙄𝙀𝙎 📚------------------------*//

# include "X11/X.h"
# include "X11/keysym.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

//*-------------------- 📖 𝘿𝙀𝙁𝙄𝙉𝙄𝙏𝙄𝙊𝙉𝙎 📖 ---------------------*//

# define WIDTH 25
# define HEIGHT 25
# define MLX_ERROR 1
# define EPSILON 0.00001
# define PI 3.14159265358979323846
# define HALF (WIDTH / 2)
# define PIXEL_SIZE 1
# define WALL_Z 10

# define BLUE "\x1B[94m"
# define GREEN "\x1B[32m"
# define RED "\x1B[31m"
# define RESET "\x1B[0m"

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
	double x, y, z, w;
}								t_tuple;

// todo               ~~~     Matrix 		~~~						*//
typedef struct s_matrix
{
	int							rows;
	int							cols;
	float						*elements;

}								t_matrix;
//*---------------------- 📚 Headers 📚 -------------------------*//

# include "../minilibx/mlx.h"
# include "camera.h"
# include "colors.h"
# include "geometry.h"
# include "graphics.h"
# include "libft/libft.h"
# include "matrices.h"
# include "parse.h"
# include "patterns.h"
# include "rt.h"
# include "shapes.h"
# include "world.h"

//*----------------------- ❔ Utils ❔ ----------------------*//

int								equal(double a, double b);
void							calculate_coefficients(t_ray ray, double *a,
									double *b, double *c);
void							intersect_cylinder_sides(t_cylinder *cyl,
									t_ray tr_ray, t_intersections *xs,
									double radius);
void							intersect_cylinder_caps(t_cylinder *cyl,
									t_ray tr_ray, t_intersections *xs,
									double radius);
void							register_matrix(t_matrix m);
typedef struct s_matrix_registry
{
	t_matrix					*matrices;
	size_t						count;
	size_t						capacity;
}								t_matrix_registry;

extern t_matrix_registry		g_matrix_registry;

#endif
