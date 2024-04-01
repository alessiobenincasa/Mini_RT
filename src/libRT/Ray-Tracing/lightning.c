/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/01 17:33:23 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_color	lighting(t_material m, t_light light, t_tuple position, t_tuple eyev,
			t_tuple normalv, int in_shadow);
t_color lighting(t_material m, t_light light, t_tuple position, t_tuple eyev, t_tuple normalv, int in_shadow)
{
    t_color color_at_point;
    if (m.texture != NULL)
    {
        double u, v;
        point_on_sphere_to_uv(position, &u, &v);

        int tex_x = (int)(u * (m.texture->width - 1));
        int tex_y = (int)(v * (m.texture->height - 1));

        color_at_point = texture_img_get_pxl(m.texture, tex_x, tex_y);
    }
    else if (m.pattern != NULL)
        color_at_point = stripe_at(m.pattern, position);
    else
        color_at_point = m.color;

    t_color effective_color = multiply_colors(color_at_point, light.intensity);
    t_color ambient = multiply_color_scalar(effective_color, m.ambient);
    t_color diffuse = {0, 0, 0};
    t_color specular = {0, 0, 0};

    if (!in_shadow) {
        t_tuple lightv = normalize(subtract_tuples(light.position, position));
        float light_dot_normal = dot(lightv, normalv);

        if (light_dot_normal > 0) {
            diffuse = multiply_color_scalar(effective_color, m.diffuse * light_dot_normal);

            t_tuple reflectv = reflect(negate_tuple(lightv), normalv);
            float reflect_dot_eye = dot(reflectv, eyev);

            if (reflect_dot_eye > 0) {
                float factor = powf(reflect_dot_eye, m.shininess);
                specular = multiply_color_scalar(light.intensity, m.specular * factor);
            }
        }
    }

    t_color result = add_colors(add_colors(ambient, diffuse), specular);
    return result;
}
