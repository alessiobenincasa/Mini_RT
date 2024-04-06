/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:55:10 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 11:35:46 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "all.h"

//*---------------------- 🖥️ Graphics 🖥️ ----------------------*//

// todo               ~~~    MLX Utils    ~~~                  *//
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
	t_scene_data	*scene;
}					t_vars;

void				my_mlx_pixel_put(t_vars *vars, int x, int y, int color);

#endif
