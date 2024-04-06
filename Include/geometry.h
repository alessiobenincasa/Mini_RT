/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:31:38 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/06 11:38:38 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEOMETRY_H
# define GEOMETRY_H

# include "all.h"

//*---------------------- 📐 Geometry 📐 ----------------------*//

// todo              ~~~ Tuple conversion ~~~					*//
t_tuple		tuple(double x, double y, double z, double w);
t_tuple		point(double x, double y, double z);
t_tuple		vector(double x, double y, double z);

// todo              ~~~ Tuples interact ~~~					*//
t_tuple		add_tuples(t_tuple a, t_tuple b);
t_tuple		subtract_tuples(t_tuple a, t_tuple b);
t_tuple		negate_tuple(t_tuple t);
t_tuple		reflect(t_tuple incident, t_tuple normal);
int			tuple_equals(t_tuple a, t_tuple b);

// todo              ~~~ Tuple Operations ~~~					*//
t_tuple		multiply_tuple_scalar(t_tuple a, double scalar);
t_tuple		divide_tuple_scalar(t_tuple a, double scalar);
t_tuple		normalize(t_tuple v);
double		magnitude(t_tuple t);
double		dot(t_tuple a, t_tuple b);

// todo               ~~~     Vectors     ~~~					*//
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

t_vector	cross(t_tuple v, t_tuple w);
t_vector	tuple_to_vector(t_tuple t);

#endif
