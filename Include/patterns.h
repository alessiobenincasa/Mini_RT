/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:00:31 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 11:35:58 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATTERNS_H
# define PATTERNS_H

# include "all.h"

//*--------------------------  Pattern  --------------------------*//

typedef struct s_pattern
{
	t_color	a;
	t_color	b;
}			t_pattern;

t_pattern	*stripe_pattern(t_color color_a, t_color color_b);
t_color		stripe_at(t_pattern *pattern, t_tuple point);

//*------------------------ Bump mapping -------------------------*//
typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_texture;

t_texture	*load_texture(void *mlx_ptr, char *filepath);
void		point_on_sphere_to_uv(t_tuple point, double *u, double *v);
t_color		texture_img_get_pxl(t_texture *texture, int x, int y);

#endif
