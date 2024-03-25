/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/25 11:42:01 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_intersections	intersect_world(t_world *world, t_ray r);
t_comps			prepare_computations(t_intersection i, t_ray r);
t_color			shade_hit(t_world world, t_comps comps);
t_color			color_at(t_world w, t_ray r);
t_matrix		view_transform(t_tuple from, t_tuple to, t_tuple up);
