/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_interact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/25 11:14:18 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_tuple							add_tuples(t_tuple a, t_tuple b);
t_tuple							subtract_tuples(t_tuple a, t_tuple b);
t_tuple							negate_tuple(t_tuple t);
t_tuple							reflect(t_tuple incident, t_tuple normal);
int								tuple_equals(t_tuple a, t_tuple b);
