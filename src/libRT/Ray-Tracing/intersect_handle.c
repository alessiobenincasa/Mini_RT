/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/04/03 14:03:34 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	add_intersection(t_intersections *xs, t_intersection inter);
int		compare_intersections(const void *a, const void *b);
void	sort_intersections(t_intersections *intersections);

void	add_intersection(t_intersections *xs, t_intersection inter)
{
	int	new_capacity;

	if (xs->count == 0)
	{
		xs->intersections = ft_calloc(4, sizeof(t_intersection));
		if (xs->intersections == NULL)
			exit(EXIT_FAILURE);
		xs->capacity = 4;
	}
	else if (xs->count >= xs->capacity)
	{
		new_capacity = xs->capacity * 2;
		xs->intersections = realloc(xs->intersections, new_capacity
				* sizeof(t_intersection));
		if (xs->intersections == NULL)
			exit(EXIT_FAILURE);
		xs->capacity = new_capacity;
	}
	xs->intersections[xs->count] = inter;
	xs->count++;
}

int	compare_intersections(const void *a, const void *b)
{
	t_intersection	*ia;
	t_intersection	*ib;

	ia = (t_intersection *)a;
	ib = (t_intersection *)b;
	if (ia->t < ib->t)
		return (-1);
	else if (ia->t > ib->t)
		return (1);
	else
		return (0);
}

void	sort_intersections(t_intersections *intersections)
{
	qsort(intersections->intersections, intersections->count,
		sizeof(t_intersection), compare_intersections);
}
