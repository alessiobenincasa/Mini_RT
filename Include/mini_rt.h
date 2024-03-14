/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:29:01 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/14 16:23:54 by albeninc         ###   ########.fr       */
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
}				t_vars;

int				validate_scene(char *filename);
void			parse_scene(char *filename);
void			my_mlx_pixel_put(t_vars *vars, int x, int y, int color);
int				make_color(float percent, int flag, int r, int g);
t_vector		vector_add(t_vector a, t_vector b);
void			render_cylinder_basic(t_vars *vars, t_cylinder cylinder);
void			render_plane(t_vars *vars, t_plane plane);
float			intersect_ray_plane(t_ray ray, t_plane plane);

t_vector		vector_sub(t_vector a, t_vector b);
t_vector		vector_cross(t_vector a, t_vector b);
t_vector		vector_scale(t_vector v, double s);
double			dot(t_vector a, t_vector b);
double			norm(t_vector v);
void			render(t_vars *vars, t_sphere sphere, t_light light);

t_vector		normalize(t_vector v);
int				create_trgb(int t, int r, int g, int b);

#endif
