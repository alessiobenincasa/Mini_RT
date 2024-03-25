/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_handle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:28:23 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/25 12:01:29 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"


void	add_intersection(t_intersections *xs, double t, t_sphere *s);
int		compare_intersections(const void *a, const void *b);
void	sort_intersections(t_intersections *intersections);

void	add_intersection(t_intersections *xs, double t, t_sphere *s)
{
	int	new_count;

	new_count = xs->count + 1;
	xs->intersections = realloc(xs->intersections, new_count
			* sizeof(t_intersection));
	if (xs->intersections == NULL)
		exit(EXIT_FAILURE);
	xs->intersections[xs->count].t = t;
	xs->intersections[xs->count].sphere = s;
	xs->count = new_count;
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
