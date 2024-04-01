/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_maping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 01:50:33 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/01 11:05:15 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// t_texture	*load_bump_texture(void *mlx_ptr, char *filepath)
// {
// 	t_texture	*texture;

// 	texture = malloc(sizeof(t_texture));
// 	if (!texture)
// 		return (NULL);
// 	texture->img = mlx_xpm_file_to_image(mlx_ptr, filepath, &texture->width,
// 			&texture->height);
// 	if (!texture->img)
// 	{
// 		free(texture);
// 		return (NULL);
// 	}
// 	texture->data = (int *)mlx_get_data_addr(texture->img, &texture->bpp,
// 			&texture->size_line, &texture->endian);
// 	return (texture);
// }

// t_vec3	calculate_bump_normal(t_texture *bumpMap, float u, float v)
// {
// 	int		x;
// 	int		y;
// 	int		colorValue;
// 	float	bumpStrength;
// 	t_vec3	modifiedNormal = {.x = bumpStrength, .y = bumpStrength, .z;

// 	x = (int)(u * (bumpMap->width - 1)) % bumpMap->width;
// 	y = (int)(v * (bumpMap->height - 1)) % bumpMap->height;
// 	colorValue = bumpMap->data[y * bumpMap->size_line / 4 + x];
// 	bumpStrength = (colorValue & 0xFF) / 255.0f;
// 	modifiedNormal = {.x = bumpStrength, .y = bumpStrength, .z = 1.0f};
// 	return (normalize(modifiedNormal));
// }
