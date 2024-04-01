/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:53:00 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/01 16:45:46 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

//*--------------------- 📚 𝙇𝙄𝘽𝙍𝘼𝙍𝙄𝙀𝙎 📚------------------------*//

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

//*-------------------- 📖 𝘿𝙀𝙁𝙄𝙉𝙄𝙏𝙄𝙊𝙉𝙎 📖 ---------------------*//

# define WIDTH 400
# define HEIGHT 400
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
typedef struct s_environnement	t_environnement;
typedef struct s_img			t_img;
typedef struct s_init			t_init;
typedef struct s_intersection	t_intersection;
typedef struct s_intersections	t_intersections;
typedef struct s_light			t_light;
typedef struct s_material		t_material;
typedef struct s_object			t_object;
typedef struct s_plane			t_plane;
typedef struct s_projectile		t_projectile;
typedef struct s_ray			t_ray;
typedef struct s_scene_data		t_scene_data;
typedef struct s_scene_state	t_scene_state;
typedef struct s_sphere			t_sphere;
typedef struct s_tuple			t_tuple;
typedef struct s_vector			t_vector;
typedef struct s_vars			t_vars;
typedef struct s_world			t_world;

//*----------------------- 👁️ 𝙋𝘼𝙍𝙎𝙀 👁️ -----------------------*//
typedef struct s_init
{
	int							ambient_light;
	int							camera;
	int							light;
}								t_init;

typedef struct s_scene_data
{
	t_ambient					*ambient_light;
	t_camera					*camera;
	t_light						*light;
	t_init						initialised;
	t_list						*shapes;
	t_list						*extra_lights;
	int							shape_count;
}								t_scene_data;

// todo              ~~~  parse errors  ~~~                  *//
int								invalid_input(int ac, char **av);
void							error(char *str);

// todo              ~~~   data init    ~~~                  *//
void							*init_data(t_scene_data *scene_data, int ac,
									char **av);
int								get_identifier(char **line,
									t_identifier_type *type,
									t_scene_data *scene_data);

// todo              ~~~ value extract  ~~~                  *//
void							parse_coordinates(char *input, t_tuple *vec);
int								parse_colors(char *input, t_color *colors);

// todo              ~~~     utils      ~~~                  *//
double							ft_atof(const char *str);
int								skip_spaces(char *str);
char							*strdup_upto_whitespace(const char *s);
void							get_next_value(char **value, char **line);

// todo              ~~~   get shapes   ~~~                  *//
t_sphere						*get_sphere_data(char *line, double amb);
t_plane							*get_plane_data(char *line, double amb);
t_cylinder						*get_cylinder_data(char *line, double amb);
t_cone							*get_cone_data(char *line, double amb);

// todo              ~~~  add elements  ~~~                  *//
int								add_shape_data(t_identifier_type type,
									t_scene_data *scene_data, char *line);
int								add_capital_element(t_identifier_type type,
									t_scene_data *scene_data, char *line);

// todo              ~~~  cap elem init ~~~                  *//
t_light							*initialize_scene_light(void);
int								add_extra_light(t_scene_data *scene_data,
									char *line);

// todo              ~~~     frees      ~~~                  *//
void							free_scene_data(t_scene_data *scene);

// todo              ~~~     print      ~~~                  *//
void							print_camera(const t_camera *camera);
void							print_identifier_type(t_identifier_type type);
void							print_sphere(const t_sphere *sphere);
void							print_ambient(const t_ambient *ambient);
void							print_light(const t_light *light);
void							print_plane(const t_plane *plane);
void							print_cylinder(const t_cylinder *cylinder);
void							print_cone(const t_cone *cone);
void							print_color(const t_color *color);
void							print_tuple(t_tuple tuple);
void							print_camera_direction(t_tuple from, t_tuple to,
									t_tuple up);

//*----------------------- 🎨 Colors 🎨 -----------------------*//

typedef struct s_color
{
	float						red;
	float						green;
	float						blue;
}								t_color;

// todo               ~~~      Colors     ~~~
t_color							color(float red, float green, float blue);
t_color							pixel_at(t_canvas c, int x, int y);
int								convert_color_to_int(t_color color);
void							set_color(t_color *color, float red,
									float green, float blue);

// todo               ~~~ Colors Interact ~~~
t_color							hadarmard_product(t_color c, t_color b);
t_color							multiply_color_scalar(t_color c, float scalar);
t_color							subtract_colors(t_color c1, t_color c2);
t_color							add_colors(t_color c1, t_color c2);
t_color							multiply_colors(t_color color1, t_color color2);

//*---------------------- 🧮 Matrices 🧮 ----------------------*//

typedef struct s_matrix
{
	int							rows;
	int							cols;
	float						*elements;

}								t_matrix;

// todo           ~~~ Matrix basic operations
t_matrix						create_matrix(int rows, int cols,
									float elements[]);
void							free_matrix(t_matrix *m);
float							get_element(t_matrix m, int row, int col);
int								matrices_equal(t_matrix a, t_matrix b);
t_matrix						transpose_matrix(t_matrix matrix);

// todo             ~~~ Matrix transformation
t_matrix						translation(float x, float y, float z);
t_matrix						scaling(float x, float y, float z);
t_matrix						shearing(float xy, float xz, float yx, float yz,
									float zx, float zy);

// todo              ~~~ Matrix rotations
t_matrix						rotation_x(float radians);
t_matrix						rotation_y(float radians);
t_matrix						rotation_z(float radians);

// todo          ~~~ Matrix utility functions
t_matrix						submatrix(t_matrix matrix, int remove_row,
									int remove_col);
float							minor_matrix(t_matrix matrix, int row, int col);
float							cofactor(t_matrix matrix, int row, int col);
float							determinant(t_matrix M);

// todo          ~~~ Matrix advanced operations
t_matrix						multiply_matrices(t_matrix a, t_matrix b);
t_tuple							multiply_matrix_tuple(t_matrix m, t_tuple t);
t_matrix						inverse(t_matrix A);
int								is_invertible(t_matrix A);
t_matrix						identity_matrix(void);

//*---------------------- 📐 Geometry 📐 ----------------------*//

// todo               ~~~     Tuples
typedef struct s_tuple
{
	double x, y, z, w;
}								t_tuple;

// todo              ~~~ Tuple conversion
t_tuple							tuple(double x, double y, double z, double w);
t_tuple							point(double x, double y, double z);
t_tuple							vector(double x, double y, double z);

// todo              ~~~ Tuples interact
t_tuple							add_tuples(t_tuple a, t_tuple b);
t_tuple							subtract_tuples(t_tuple a, t_tuple b);
t_tuple							negate_tuple(t_tuple t);
t_tuple							reflect(t_tuple incident, t_tuple normal);
int								tuple_equals(t_tuple a, t_tuple b);

// todo              ~~~ Tuple Operations
t_tuple							multiply_tuple_scalar(t_tuple a, double scalar);
t_tuple							divide_tuple_scalar(t_tuple a, double scalar);
t_tuple							normalize(t_tuple v);
double							magnitude(t_tuple t);
double							dot(t_tuple a, t_tuple b);

// todo               ~~~     Vectors
typedef struct s_vector
{
	double x, y, z;
}								t_vector;

t_vector						cross(t_tuple v, t_tuple w);
t_vector						tuple_to_vector(t_tuple t);
t_tuple							vector_to_tuple(t_vector v);

//*--------------------- 🪩 Ray-Tracing 🪩 --------------------*//

// todo               ~~~      Rays
typedef struct s_ray
{
	t_tuple						origin;
	t_tuple						direction;
}								t_ray;

t_ray							transform(t_ray ray, t_matrix m);
t_ray							ray(t_tuple origin, t_tuple direction);
t_tuple							position(t_ray r, double t);

// todo               ~~~  Intersections

typedef union s_object_union
{
	t_sphere					*sphere;
	t_plane						*plane;
	t_cylinder					*cylinder;
	t_cone						*cone;
}								t_object_union;
typedef struct s_intersection
{
	double						t;
	t_object_union				object;
	t_identifier_type			type;
}								t_intersection;

typedef struct s_intersections
{
	t_intersection				*intersections;
	int							count;
	int							capacity;
}								t_intersections;

t_intersection					intersection(double t, t_sphere *object);
t_intersections					intersections(int count,
									t_intersection *inter_arr);
t_intersections					intersect_sphere(t_sphere *s, t_ray r);
t_intersection					*hit(t_intersections *xs);

// todo               ~~~  Intersect handle
void							add_intersection(t_intersections *xs,
									t_intersection inter);
int								compare_intersections(const void *a,
									const void *b);
void							sort_intersections(t_intersections *intersections);

// todo             ~~~     Material
typedef struct s_material
{
	t_color						color;
	double						ambient;
	double						diffuse;
	double						specular;
	double						shininess;
}								t_material;

t_material						material(void);

// todo             ~~~      Light
typedef struct s_light
{
	t_tuple						position;
	t_color						intensity;
	double						energy;
}								t_light;

t_light							point_light(t_tuple position,
									t_color intensity);
t_color							lighting(t_material m, t_light light,
									t_tuple position, t_tuple eyev,
									t_tuple normalv, int in_shadow);

// todo               ~~~     Scene
typedef struct s_scene_state
{
	int							ambient_light_found;
	int							camera_found;
}								t_scene_state;

typedef struct s_ambient
{
	double						ratio;
	t_color						color;
}								t_ambient;

//*----------------------- 🌀 Shapes 🌀 -----------------------*//

int								is_shape(t_identifier_type type);

// todo               ~~~    Spheres
typedef struct s_sphere
{
	t_tuple						center;
	double						radius;
	t_material					material;
	t_matrix					transform;
}								t_sphere;

t_sphere						sphere(void);
void							set_transform(t_sphere *s, t_matrix t);
t_tuple							normal_at(t_sphere sphere, t_tuple p);

// todo               ~~~    Cylinder

// todo               ~~~     Planes
typedef struct s_plane
{
	t_tuple						point;
	t_tuple						normal;
	t_material					material;
	t_matrix					transform;
}								t_plane;

t_intersections					intersect_plane(t_plane *p, t_ray r);
t_plane							plane(void);

//*---------------------- 🖥️ Graphics 🖥️ ----------------------*//

// todo               ~~~     Canvas
typedef struct s_canvas
{
	int							height;
	int							width;
	t_color						*pixels;
}								t_canvas;

t_canvas						canvas(int width, int height);
void							write_pixel(t_canvas *c, int x, int y,
									t_color color);

// todo               ~~~     MLX Utils
typedef struct s_img
{
	void						*img_ptr;
	char						*addr;
	int							bits_per_pixel;
	int							line_length;
	int							endian;
}								t_img;

typedef struct s_vars
{
	void						*mlx;
	void						*win;
	t_img						img;
}								t_vars;

void							my_mlx_pixel_put(t_vars *vars, int x, int y,
									int color);

//*----------------------- 🌌 Physics 🌌 ----------------------*//

typedef struct s_projectile
{
	t_tuple						position;
	t_tuple						velocity;
}								t_projectile;

typedef struct s_environnement
{
	t_tuple						wind;
	t_tuple						gravity;
}								t_environnement;

// todo               ~~~     Shadows
int								is_shadowed(t_world world, t_tuple point,
									t_tuple light_pos);

//*------------------------ 🌍 World 🌍 -----------------------*//
typedef struct s_object
{
	int							id;
	void						*data;
}								t_object;

typedef struct s_world
{
	t_list						*objects;
	int							object_count;
	t_light						light;
	t_list						*extra_lights;
}								t_world;

typedef struct s_comps
{
	double						t;
	t_object_union				object;
	t_identifier_type			type;
	t_tuple						point;
	t_tuple						eyev;
	t_tuple						normalv;
	t_tuple						over_point;
	int							inside;
}								t_comps;

// todo               ~~~    World Init
t_world							world(void);

// todo               ~~~    World colors
t_intersections					intersect_world(t_world *world, t_ray r);
t_comps							prepare_computations(t_intersection i, t_ray r);
t_color							shade_hit(t_world world, t_comps comps);
t_color							color_at(t_world w, t_ray r);
t_matrix						view_transform(t_tuple from, t_tuple to,
									t_tuple up);

//*----------------------- 📷 Camera 📷 -----------------------*//

typedef struct s_camera
{
	int							hsize;
	int							vsize;
	double						fov;
	t_matrix					transform;
	double						pixel_size;
	double						half_width;
	double						half_height;
	t_tuple						position;
	t_tuple						orientation;
}								t_camera;

t_camera						camera(int hsize, int vsize, double fov);
t_ray							ray_for_pixel(t_camera camera, int px, int py);
t_canvas						render(t_camera cam, t_world w);

//*----------------------- ❔ Utils ❔ ----------------------*//

t_projectile					tick(t_environnement env, t_projectile proj);
int								equal(double a, double b);

//*-----------------------  Cylinder  -----------------------*//

typedef struct s_cylinder
{
	t_tuple						center;
	t_tuple						direction;
	double						diameter;

	t_matrix					transform;
	double						minimum;
	double						maximum;
	int							closed;
	t_material					material;
}								t_cylinder;

t_cylinder						cylinder(void);
t_intersections					intersect_cylinder(t_cylinder *cyl,
									t_ray r);
t_tuple							local_normal_at_cylinder(t_cylinder cylinder,
									t_tuple point);
t_tuple							normal_at_cylinder(t_cylinder cylinder,
									t_tuple p);
void							add_intersection_cylinder(t_intersections *xs,
									double t, t_cylinder *cyl);
int								check_cap(t_ray ray, double t, double radius);

//*-------------------------  Cone  -------------------------*//

typedef struct s_cone
{
	t_tuple						center;
	t_tuple						direction;
	int							inverted;

	t_matrix					transform;
	double						minimum;
	double						maximum;
	int							closed;
	t_material					material;
}								t_cone;

t_cone							cone(void);
t_tuple							local_normal_at_cone(t_cone cylinder,
									t_tuple point);
int								check_cap_cone(t_ray ray, double t,
									t_cone *cone, int is_lower);
void							add_intersection_cone(t_intersections *xs,
									double t, t_cone *cone);
t_intersections					intersect_cone(t_cone *cyl, t_ray ray);
t_tuple							normal_at_cone(t_cone cone, t_tuple p);

#endif
