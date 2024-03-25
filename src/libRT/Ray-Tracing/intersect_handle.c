/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/25 11:39:58 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"


void	add_intersection(t_intersections *xs, double t, t_sphere *s);
int		compare_intersections(const void *a, const void *b);
void	sort_intersections(t_intersections *intersections);