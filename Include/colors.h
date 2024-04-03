/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:25:27 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/03 14:07:40 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

//*----------------------- 🎨 Colors 🎨 -----------------------*//

typedef struct s_color
{
	float	red;
	float	green;
	float	blue;
}			t_color;

// todo               ~~~      Colors     ~~~					*//
t_color		color(float red, float green, float blue);
int			convert_color_to_int(t_color color);
void		set_color(t_color *color, float red, float green, float blue);

// todo               ~~~ Colors Interact ~~~					*//
t_color		hadarmard_product(t_color c, t_color b);
t_color		multiply_color_scalar(t_color c, float scalar);
t_color		subtract_colors(t_color c1, t_color c2);
t_color		add_colors(t_color c1, t_color c2);
t_color		multiply_colors(t_color color1, t_color color2);

int			is_shadowed(t_world world, t_tuple point, t_tuple light_pos);
