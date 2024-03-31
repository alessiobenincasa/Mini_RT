/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 17:31:30 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/31 18:48:42 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_pattern	stripe_pattern(t_color a, t_color b)
{
	t_pattern	pattern;

	pattern.a = a;
	pattern.b = b;
	return (pattern);
}

t_color	stripe_at(t_pattern pattern, t_tuple point)
{
	if ((int)floor(point.x) % 2 == 0)
		return (pattern.a);
	else
		return (pattern.b);
}