/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/25 11:15:12 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_intersection	intersection(double t, t_sphere *object);
t_intersections	intersections(int count, t_intersection *inter_arr);
t_intersections	intersect(t_sphere *s, t_ray r);
t_intersection	*hit(t_intersections *xs);
