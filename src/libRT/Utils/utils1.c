/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 12:07:00 by svolodin          #+#    #+#             */
/*   Updated: 2024/03/25 12:07:11 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	equal(double a, double b)
{
	return (fabs(a - b) < EPSILON);
}

t_projectile	tick(t_environnement env, t_projectile proj)
{
	t_tuple	position;
	t_tuple	velocity;

	position = add_tuples(proj.position, proj.velocity);
	velocity = add_tuples(add_tuples(proj.velocity, env.gravity), env.wind);
	return ((t_projectile){position, velocity});
}
