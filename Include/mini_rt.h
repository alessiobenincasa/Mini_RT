/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:29:01 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/08 16:22:16 by albeninc         ###   ########.fr       */
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

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1200
# define MLX_ERROR 1

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
	int			fov;
}				t_camera;

typedef struct s_light
{
	t_vector	position;
	double		brightness;
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
	t_vector	normal;
	double		diameter;
	double		height;
	int color[3]; // RGB
}				t_cylinder;

int				validate_scene(char *filename);
void			parse_scene(char *filename);

#endif
