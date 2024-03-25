/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/25 11:10:05 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_ray	transform(t_ray ray, t_matrix m);
t_ray	ray(t_tuple origin, t_tuple direction);
t_tuple	position(t_ray r, double t);