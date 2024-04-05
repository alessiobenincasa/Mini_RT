/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:00:59 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/05 14:01:05 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	free_s(t_sphere *s)
{
	free(s->transform.elements);
	if (s->motif)
		free(s->motif);
	if (s->material.pattern)
		free(s->material.pattern);
	if (s->material.texture)
		free(s->material.texture);
	free(s);
}

void	free_p(t_plane *p)
{
	free(p->transform.elements);
	free(p);
}
void	free_cyl(t_cylinder *c)
{
	free(c->transform.elements);
	free(c);
}

void	free_c(t_cone *c)
{
	free(c->transform.elements);
	free(c);
}
