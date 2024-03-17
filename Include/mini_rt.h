/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:29:01 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/17 02:48:49 by albeninc         ###   ########.fr       */
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
} t_tuple;

typedef struct s_projectile
{
	t_tuple position;
	t_tuple velocity;
}	t_projectile;

typedef struct s_environnement
{
	t_tuple wind;
	t_tuple gravity;
}	t_environnement;



#endif
