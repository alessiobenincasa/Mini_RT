/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:29:01 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/26 16:22:50 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include "../minilibx/mlx.h"
# include "X11/X.h"
# include "X11/keysym.h"
# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 800
# define MLX_ERROR 1
# define M_PI 3.14159265358979323846
# define EPSILON 0.00001
# define PI 3.14159265358979323846
# define HALF (WIDTH / 2)
# define PIXEL_SIZE 1
# define WALL_Z 10

typedef struct s_color
{
	float			red;
	float			green;
	float			blue;
}					t_color;

typedef struct s_tuple
{
	double x, y, z, w;
}					t_tuple;

typedef struct s_scene_state
{
	int				ambient_light_found;
	int				camera_found;
}					t_scene_state;

typedef struct s_vector
{
	double x, y, z;
}					t_vector;

typedef struct s_ambient
{
	double			ratio;
	int color[3]; // RGB
}					t_ambient;

typedef struct s_light
{
	t_tuple			position;
	t_color			intensity;
}					t_light;

typedef struct s_plane
{
	t_vector		point;
	t_vector		normal;
	int color[3]; // RGB
}					t_plane;

typedef struct s_cylinder
{
	t_vector		center;
	t_vector		direction;
	double			diameter;
	double			height;
	int color[3]; // RGB
}					t_cylinder;

typedef struct s_projectile
{
	t_tuple			position;
	t_tuple			velocity;
}					t_projectile;

typedef struct s_environnement
{
	t_tuple			wind;
	t_tuple			gravity;
}					t_environnement;

typedef struct s_canvas
{
	int				height;
	int				width;
	t_color			*pixels;
}					t_canvas;

typedef struct s_matrix
{
	int				rows;
	int				cols;
	float			*elements;

}					t_matrix;

typedef struct s_ray
{
	t_tuple			origin;
	t_tuple			direction;
}					t_ray;

typedef struct s_material
{
	t_color			color;
	double			ambient;
	double			diffuse;
	double			specular;
	double			shininess;
}					t_material;

typedef struct s_sphere
{
	t_tuple			center;
	double			radius;
	t_material		material;
	t_matrix		transform;
	int				color[3];
}					t_sphere;

typedef struct s_intersection
{
	double			t;
	t_sphere		*sphere;
}					t_intersection;

typedef struct s_intersections
{
	t_intersection	*intersections;
	int				count;
}					t_intersections;

typedef struct s_img
{
	void			*img_ptr;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}					t_img;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_img			img;
}					t_vars;

typedef struct s_object
{
	int				id;
	void			*data;
}					t_object;

typedef struct s_world
{
	t_object		*objects;
	int				object_count;
	t_light			light;
}					t_world;

typedef struct s_comps
{
	double			t;
	t_sphere		*sphere;
	t_tuple			point;
	t_tuple			eyev;
	t_tuple			normalv;
	int				inside;
	t_tuple			over_point;

}					t_comps;

t_intersection		*hit(t_intersections *xs);
int					compare_intersection_t(const void *a, const void *b);
t_intersections		intersect_world(t_world *world, t_ray r);
t_world				world(void);
t_material			material(void);
t_color				shade_hit(t_world world, t_comps comps);
t_color				color(float red, float green, float blue);
t_intersections		intersections(int count,
						t_intersection *intersectionsArray);
t_matrix			rotation_x(float radians);
int					convert_color_to_int(t_color color);
t_comps				prepare_computations(t_intersection intersection,
						t_ray ray);
t_light				point_light(t_tuple position, t_color intensity);
t_sphere			sphere(void);
t_intersections		intersect(t_sphere *s, t_ray r);
t_matrix			scaling(float x, float y, float z);
t_matrix			multiply_matrices(t_matrix a, t_matrix b);
int					matrices_equal(t_matrix a, t_matrix b);
float				get_element(t_matrix m, int row, int col);
t_matrix			create_matrix(int rows, int cols, float elements[]);
void				convert_and_display_canvas(t_vars *vars, t_canvas canvas);
t_color				pixel_at(t_canvas c, int x, int y);
void				write_pixel(t_canvas *c, int x, int y, t_color color);
t_canvas			canvas(int width, int height);
t_vector			tuple_to_vector(t_tuple t);
void				set_transform(t_sphere *s, t_matrix t);
t_projectile		tick(t_environnement env, t_projectile proj);
t_vector			cross(t_tuple v, t_tuple w);
double				dot(t_tuple a, t_tuple b);
int					make_color(float percent, int flag, int r, int g);
double				magnitude(t_tuple t);
t_tuple				normalize(t_tuple v);
t_matrix			rotation_y(float radians);
t_tuple				divide_tuple_scalar(t_tuple a, double scalar);
t_tuple				multiply_tuple_scalar(t_tuple a, double scalar);
t_tuple				negate_tuple(t_tuple t);
int					tuple_equals(t_tuple a, t_tuple b);
t_tuple				subtract_tuples(t_tuple a, t_tuple b);
t_tuple				add_tuples(t_tuple a, t_tuple b);
int					equal(double a, double b);
t_color				lighting(t_material m, t_light light, t_tuple position,
						t_tuple eyev, t_tuple normalv, int in_shadow);
t_ray				transform(t_ray ray, t_matrix m);
t_intersection		intersection(double t, t_sphere *object);
t_tuple				point(double x, double y, double z);
t_tuple				tuple(double x, double y, double z, double w);
t_tuple				vector(double x, double y, double z);
t_tuple				position(t_ray r, double t);
t_color				hadarmard_product(t_color c, t_color b);
t_color				multiply_color_scalar(t_color c, float scalar);
t_color				subtract_colors(t_color c1, t_color c2);
t_tuple				reflect(t_tuple incident, t_tuple normal);
t_tuple				normal_at(t_sphere sphere, t_tuple p);
t_color				add_colors(t_color c1, t_color c2);
void				free_matrix(t_matrix *m);
t_tuple				vector_to_tuple(t_vector v);
t_matrix			identity_matrix(void);
t_tuple				multiply_matrix_tuple(t_matrix m, t_tuple t);
t_matrix			transpose_matrix(t_matrix matrix);
t_matrix			submatrix(t_matrix matrix, int remove_row, int remove_col);
float				minor(t_matrix matrix, int row, int col);
float				cofactor(t_matrix matrix, int row, int col);
t_matrix			rotation_z(float radians);
float				determinant(t_matrix M);
int					is_invertible(t_matrix A);
t_matrix			inverse(t_matrix A);
t_matrix			translation(float x, float y, float z);
t_matrix			shearing(float xy, float xz, float yx, float yz, float zx,
						float zy);
t_ray				ray(t_tuple origin, t_tuple direction);
void				my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
int					create_trgb(int t, int r, int g, int b);
t_world				default_world(void);
void				set_color(t_color *color, float red, float green,
						float blue);
t_color				color_at(t_world w, t_ray r);
void				free_world(t_world *w);
t_matrix			view_transform(t_tuple from, t_tuple to, t_tuple up);

//! Camera

typedef struct s_camera
{
	int				hsize;
	int				vsize;
	double			fov;
	t_matrix		transform;
	double			pixel_size;
	double			half_width;
	double			half_height;
}					t_camera;

t_camera			camera(int hsize, int vsize, double fov);
t_ray				ray_for_pixel(t_camera camera, int px, int py);
t_canvas			render(t_camera cam, t_world w);
void				render_scene(t_vars *vars);
t_canvas			render_scene2(void);

//! Shadow
int					is_shadowed(t_world world, t_tuple point);

//! Plane

typedef struct s_shape
{
	t_matrix		transform;
	t_ray			*saved_ray;
	t_material		material;
	t_intersections	(*local_intersect)(struct s_shape *, t_ray);
	t_tuple			(*local_normal_at)(struct s_shape *, t_tuple);
}					t_shape;

t_shape				*test_shape(void);
void				set_transform_shape(t_shape *s, t_matrix t);
t_intersections		intersect_shape(t_shape *shape, t_ray r);
t_tuple				normal_at_shape(t_shape *s, t_tuple p);
t_tuple				local_normal_at_test(t_shape *shape, t_tuple local_point);

#endif
