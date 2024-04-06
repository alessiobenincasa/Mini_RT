/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 14:00:59 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 10:16:45 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	free_s_motif(t_sphere *s, void *mlx_ptr)
{
	if (s->material.texture)
		mlx_destroy_image(mlx_ptr, s->material.texture->img);
}

void	free_s(t_sphere *s)
{
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
	free(p);
}
void	free_cyl(t_cylinder *c)
{
	free(c);
}

void	free_c(t_cone *c)
{
	free(c);
}
