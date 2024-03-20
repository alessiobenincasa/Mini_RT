/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:29:01 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/20 15:26:44 by svolodin         ###   ########.fr       */
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

# define WIDTH 1200
# define HEIGHT 1200
# define MLX_ERROR 1
# define M_PI 3.14159265358979323846
# define EPSILON 0.00001
# define PI 3.14159265358979323846
# define HALF (WIDTH / 2)
# define PIXEL_SIZE 1
# define WALL_Z 10


//*------------------ 📜 Pre-declarations 📜 -------------------*//

typedef struct s_scene_state t_scene_state;
typedef struct s_vector t_vector;
typedef struct s_ambient t_ambient;
typedef struct s_camera t_camera;
typedef struct s_light t_light;
typedef struct s_plane t_plane;
typedef struct s_cylinder t_cylinder;
typedef struct s_tuple t_tuple;
typedef struct s_projectile t_projectile;
typedef struct s_environnement t_environnement;
typedef struct s_canvas t_canvas;
typedef struct s_ray t_ray;
typedef struct s_material t_material;
typedef struct s_sphere t_sphere;
typedef struct s_intersection t_intersection;
typedef struct s_intersections t_intersections;
typedef struct s_img t_img;
typedef struct s_vars t_vars;


//*----------------------- 🎨 Colors 🎨 -----------------------*//

typedef struct s_color
{
	float			red;
	float			green;
	float			blue;
}					t_color;

t_color				hadarmard_product(t_color c, t_color b);
t_color				multiply_color_scalar(t_color c, float scalar);
t_color				subtract_colors(t_color c1, t_color c2);
t_color				pixel_at(t_canvas c, int x, int y);
t_color				color(float red, float green, float blue);
t_color				add_colors(t_color c1, t_color c2);
	
//*---------------------- 🧮 Matrices 🧮 ----------------------*//	

typedef struct s_matrix
{
	int				rows;
	int				cols;
	float			*elements;

}					t_matrix;

// Basic matrix operations
t_matrix			create_matrix(int rows, int cols, float elements[]);
void				free_matrix(t_matrix *m);
float				get_element(t_matrix m, int row, int col);						
int					matrices_equal(t_matrix a, t_matrix b);
t_matrix			transpose_matrix(t_matrix matrix);

// Matrix transformation
t_matrix			translation(float x, float y, float z);
t_matrix			scaling(float x, float y, float z);
t_matrix			shearing(float xy, float xz, float yx, float yz, float zx, float zy);

// Matrix rotations
t_matrix			rotation_x(float radians);
t_matrix			rotation_y(float radians);
t_matrix			rotation_z(float radians);


// Matrix utility functions
t_matrix			submatrix(t_matrix matrix, int remove_row, int remove_col);
float				minor(t_matrix matrix, int row, int col);
float				cofactor(t_matrix matrix, int row, int col);
float				determinant(t_matrix M);

// Matrix advanced operations
t_matrix			multiply_matrices(t_matrix a, t_matrix b);
t_tuple				multiply_matrix_tuple(t_matrix m, t_tuple t);
t_matrix			inverse(t_matrix A);
int					is_invertible(t_matrix A);
t_matrix			identity_matrix(void);


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

typedef struct s_camera
{
	t_vector		position;
	t_vector		orientation;
	double			fov;
}					t_camera;

typedef struct s_light
{
	t_vector		position;
	double			intensity;
	int color[3]; // RGB
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

typedef struct s_tuple
{
	double x, y, z, w;
}					t_tuple;

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

typedef struct s_ray
{
	t_tuple			origin;
	t_tuple			direction;
}					t_ray;

typedef struct s_material
{
	int				color[3];
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


t_intersection		*hit(t_intersections *xs);
t_material			material(void);
t_intersections		intersections(int count,
						t_intersection *intersectionsArray);
t_light				point_light(t_vector position, double intensity,
						int color[3]);
t_sphere			sphere(void);
t_intersections		intersect(t_sphere *s, t_ray r);

void				convert_and_display_canvas(t_vars *vars, t_canvas canvas);
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
t_tuple				divide_tuple_scalar(t_tuple a, double scalar);
t_tuple				multiply_tuple_scalar(t_tuple a, double scalar);
t_tuple				negate_tuple(t_tuple t);
int					tuple_equals(t_tuple a, t_tuple b);
t_tuple				substract_tuples(t_tuple a, t_tuple b);
t_tuple				add_tuples(t_tuple a, t_tuple b);
int					equal(double a, double b);
t_ray				transform(t_ray ray, t_matrix m);
t_intersection		intersection(double t, t_sphere *object);
t_tuple				point(double x, double y, double z);
t_tuple				tuple(double x, double y, double z, double w);
t_tuple				vector(double x, double y, double z);
t_tuple				position(t_ray r, double t);
t_tuple				reflect(t_tuple incident, t_tuple normal);
t_tuple				normal_at(t_sphere sphere, t_tuple p);
t_tuple				vector_to_tuple(t_vector v);



t_ray				ray(t_tuple origin, t_tuple direction);
void				my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
int					create_trgb(int t, int r, int g, int b);

#endif
