/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 16:55:21 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/01 17:30:36 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_pattern *stripe_pattern(t_color a, t_color b)
{
    t_pattern *pattern = malloc(sizeof(t_pattern));
    if (!pattern)
        exit(EXIT_FAILURE);
    pattern->a = a;
    pattern->b = b;
    return pattern;
}

t_color stripe_at(t_pattern *pattern, t_tuple point)
{
    if (((int)floor(fabs(point.x * 10.0)) + (int)floor(fabs(point.y * 10.0))) % 2 == 0) {
        return pattern->a;
    } else {
        return pattern->b;
    }
}

t_color texture_img_get_pxl(t_texture *texture, int x, int y)
{
    if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
        return (t_color){0, 0, 0};

    int pixel = y * texture->line_length + x * (texture->bits_per_pixel / 8);
    unsigned int color = *(unsigned int *)(texture->addr + pixel);

    t_color result;
    if (texture->endian == 0)
    {
        result.red = ((color >> 16) & 0xFF) / 255.0;
        result.green = ((color >> 8) & 0xFF) / 255.0;
        result.blue = (color & 0xFF) / 255.0;
    }
    else
    {
        result.red = (color & 0xFF) / 255.0;
        result.green = ((color >> 8) & 0xFF) / 255.0;
        result.blue = ((color >> 16) & 0xFF) / 255.0;
    }

    return result;
}

t_texture    *load_texture(void *mlx_ptr, char *filepath)
{
    t_texture    *texture;

    texture = malloc(sizeof(t_texture));
    if (!texture)
        return (NULL);

    texture->img = mlx_xpm_file_to_image(mlx_ptr, filepath, &texture->width, &texture->height);
    if (!texture->img)
    {
        free(texture);
        return (NULL);
    }

    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
    if (!texture->addr)
    {
        mlx_destroy_image(mlx_ptr, texture->img);
        free(texture);
        return (NULL);
    }

    return (texture);
}

void point_on_sphere_to_uv(t_tuple point, double *u, double *v)
{
    double theta = atan2(point.z, point.x);
    double phi = acos(-point.y);
    *u = 1 - (theta + M_PI) / (2 * M_PI);
    *v = phi / M_PI;
}

