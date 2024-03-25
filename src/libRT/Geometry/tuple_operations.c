/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/25 11:14:24 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_tuple							multiply_tuple_scalar(t_tuple a, double scalar);
t_tuple							divide_tuple_scalar(t_tuple a, double scalar);
t_tuple							normalize(t_tuple v);
double							magnitude(t_tuple t);
double							dot(t_tuple a, t_tuple b);
