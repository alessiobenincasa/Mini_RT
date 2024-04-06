/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 13:53:00 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 11:53:04 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALL_H
# define ALL_H

//*--------------------- 📚 𝙇𝙄𝘽𝙍𝘼𝙍𝙄𝙀𝙎 📚------------------------*//

# include "declarations.h"

# include "X11/X.h"
# include "X11/keysym.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

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

//*-------------------- 📖 𝘿𝙀𝙁𝙄𝙉𝙄𝙏𝙄𝙊𝙉𝙎 📖 ---------------------*//

# define WIDTH 25
# define HEIGHT 25
# define MLX_ERROR 1
# define EPSILON 0.00001
# define PI 3.14159265358979323846
# define PIXEL_SIZE 1
# define WALL_Z 10

# define BLUE "\x1B[94m"
# define GREEN "\x1B[32m"
# define RED "\x1B[31m"
# define RESET "\x1B[0m"

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
