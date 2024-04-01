/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_maping.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 01:50:33 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/01 15:31:41 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// int main(void)
// {
//     void        *mlx_ptr;
//     void        *win_ptr;
//     t_texture   *earth_texture;
//     int         win_width = 800;
//     int         win_height = 600;

//     mlx_ptr = mlx_init();
//     if (!mlx_ptr)
//     {
//         fprintf(stderr, "Failed to initialize MLX\n");
//         return (EXIT_FAILURE);
//     }

//     earth_texture = load_texture(mlx_ptr, "earth.xpm");
//     if (!earth_texture)
//     {
//         fprintf(stderr, "Failed to load texture\n");
//         return (EXIT_FAILURE);
//     }

//     win_ptr = mlx_new_window(mlx_ptr, win_width, win_height, "Earth Texture");
//     if (!win_ptr)
//     {
//         fprintf(stderr, "Failed to create a window\n");
//         return (EXIT_FAILURE);
//     }

//     mlx_put_image_to_window(mlx_ptr, win_ptr, earth_texture->img, 0, 0);

//     mlx_loop(mlx_ptr);

//     mlx_destroy_image(mlx_ptr, earth_texture->img);
//     free(earth_texture);

//     return (EXIT_SUCCESS);
// }

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
    {
        fprintf(stderr, "Failed to allocate memory for texture\n");
        return (NULL);
    }

    texture->img = mlx_xpm_file_to_image(mlx_ptr, filepath, &texture->width, &texture->height);
    if (!texture->img)
    {
        fprintf(stderr, "Failed to load image from %s\n", filepath);
        free(texture);
        return (NULL);
    }

    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->line_length, &texture->endian);
    if (!texture->addr)
    {
        fprintf(stderr, "Failed to access image data\n");
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