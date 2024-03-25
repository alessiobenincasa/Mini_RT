/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_interact.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 11:01:51 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/25 11:55:46 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_tuple							add_tuples(t_tuple a, t_tuple b);
t_tuple							subtract_tuples(t_tuple a, t_tuple b);
t_tuple							negate_tuple(t_tuple t);
t_tuple							reflect(t_tuple incident, t_tuple normal);
int								tuple_equals(t_tuple a, t_tuple b);

t_tuple add_tuples(t_tuple a, t_tuple b)
{
    t_tuple result = {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
    return result;
}

t_tuple subtract_tuples(t_tuple a, t_tuple b)
{
    t_tuple result = {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
    return result;
}
t_tuple negate_tuple(t_tuple t)
{
    t_tuple result = {-t.x, -t.y, -t.z, -t.w};
    return (result);
}

t_tuple reflect(t_tuple incident, t_tuple normal)
{
    t_tuple result;
    float dot_product = dot(incident, normal);
    result.x = incident.x - 2 * dot_product * normal.x;
    result.y = incident.y - 2 * dot_product * normal.y;
    result.z = incident.z - 2 * dot_product * normal.z;
    result.w  = 0;
    return result;
}

int tuple_equals(t_tuple a, t_tuple b)
{
    return equal(a.x, b.x) && equal(a.y, b.y) && equal(a.z, b.z) && equal(a.w, b.w);
}
