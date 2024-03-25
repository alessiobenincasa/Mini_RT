/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightning.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/25 12:02:54 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_color	lighting(t_material m, t_light light, t_tuple position, t_tuple eyev,
			t_tuple normalv, int in_shadow);

t_color lighting(t_material m, t_light light, t_tuple position, t_tuple eyev, t_tuple normalv, int in_shadow)
{
    t_color effective_color = multiply_colors(m.color, light.intensity);
    t_color ambient = {
        effective_color.red * m.ambient,
        effective_color.green * m.ambient,
        effective_color.blue * m.ambient
    };
    
    t_color diffuse = {0, 0, 0};
    t_color specular = {0, 0, 0};

    if (!in_shadow) {
        t_tuple lightv = normalize((t_tuple){
            light.position.x - position.x,
            light.position.y - position.y,
            light.position.z - position.z,
            0
        });

        float light_dot_normal = dot(lightv, normalv);
        
        if (light_dot_normal > 0) {
            diffuse.red = effective_color.red * m.diffuse * light_dot_normal;
            diffuse.green = effective_color.green * m.diffuse * light_dot_normal;
            diffuse.blue = effective_color.blue * m.diffuse * light_dot_normal;

            t_tuple reflectv = reflect(vector(-lightv.x, -lightv.y, -lightv.z), normalv);
            float reflect_dot_eye = dot(reflectv, eyev);

            if (reflect_dot_eye > 0) {
                float factor = powf(reflect_dot_eye, m.shininess);
                specular.red = light.intensity.red * m.specular * factor;
                specular.green = light.intensity.green * m.specular * factor;
                specular.blue = light.intensity.blue * m.specular * factor;
            }
        }
    }
    t_color result = {
        ambient.red + diffuse.red + specular.red,
        ambient.green + diffuse.green + specular.green,
        ambient.blue + diffuse.blue + specular.blue
    };

    return result;
}
