/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:29:01 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/18 13:52:18 by albeninc         ###   ########.fr       */
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

# define WIDTH 1920
# define HEIGHT 1200
# define MLX_ERROR 1
# define M_PI 3.14159265358979323846
# define EPSILON 0.00001

typedef struct s_color
{
	float		red;
	float		green;
	float		blue;
}				t_color;

typedef struct s_scene_state
{
	int			ambient_light_found;
	int			camera_found;
}				t_scene_state;

typedef struct s_vector
{
	double x, y, z;
}				t_vector;

typedef struct s_ambient
{
	double		ratio;
	int color[3]; // RGB
}				t_ambient;

typedef struct s_camera
{
	t_vector	position;
	t_vector	orientation;
	double		fov;
}				t_camera;

typedef struct s_light
{
	t_vector	position;
	double		intensity;
	int color[3]; // RGB
}				t_light;

typedef struct s_sphere
{
	t_vector	center;
	double		diameter;
	int color[3]; // RGB
}				t_sphere;

typedef struct s_plane
{
	t_vector	point;
	t_vector	normal;
	int color[3]; // RGB
}				t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	direction;
	double		diameter;
	double		height;
	int color[3]; // RGB
}				t_cylinder;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct s_img
{
	void		*img_ptr;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_camera	camera;
}				t_vars;

typedef struct s_tuple
{
	double x, y, z, w;
}				t_tuple;

typedef struct s_projectile
{
	t_tuple		position;
	t_tuple		velocity;
}				t_projectile;

typedef struct s_environnement
{
	t_tuple		wind;
	t_tuple		gravity;
}				t_environnement;

typedef struct s_canvas
{
	int			height;
	int			width;
	t_color		*pixels;
}				t_canvas;

typedef struct s_matrix
{
	int			rows;
	int			cols;
	float		*elements;

}				t_matrix;

t_color			color(float red, float green, float blue);
t_matrix		multiply_matrices(t_matrix a, t_matrix b);
int				matrices_equal(t_matrix a, t_matrix b);
float			get_element(t_matrix m, int row, int col);
t_matrix		create_matrix(int rows, int cols, float elements[]);
t_color			pixel_at(t_canvas c, int x, int y);
void			write_pixel(t_canvas *c, int x, int y, t_color color);
t_canvas		canvas(int width, int height);
t_projectile	tick(t_environnement env, t_projectile proj);
t_vector		cross(t_tuple v, t_tuple w);
double			dot(t_tuple a, t_tuple b);
double			magnitude(t_tuple t);
t_tuple			normalize(t_tuple v);
t_tuple			divide_tuple_scalar(t_tuple a, double scalar);
t_tuple			multiply_tuple_scalar(t_tuple a, double scalar);
t_tuple			negate_tuple(t_tuple t);
int				tuple_equals(t_tuple a, t_tuple b);
t_tuple			substract_tuples(t_tuple a, t_tuple b);
t_tuple			add_tuples(t_tuple a, t_tuple b);
int				equal(double a, double b);
t_tuple			point(double x, double y, double z);
t_tuple			tuple(double x, double y, double z, double w);
t_tuple			vector(double x, double y, double z);
t_color			hadarmard_product(t_color c, t_color b);
t_color			multiply_color_scalar(t_color c, float scalar);
t_color			subtract_colors(t_color c1, t_color c2);
t_color			add_colors(t_color c1, t_color c2);
void			free_matrix(t_matrix *m);
t_matrix		identity_matrix(void);
t_tuple			multiply_matrix_tuple(t_matrix m, t_tuple t);
t_matrix		transpose_matrix(t_matrix matrix);
t_matrix		submatrix(t_matrix matrix, int remove_row, int remove_col);
float			minor(t_matrix matrix, int row, int col);
float			cofactor(t_matrix matrix, int row, int col);
float			determinant(t_matrix M);
int				is_invertible(t_matrix A);
t_matrix		inverse(t_matrix A);
t_matrix		translation(float x, float y, float z);

#endif
