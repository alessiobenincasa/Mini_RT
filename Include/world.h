/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:58:32 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/04 10:26:06 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

//*------------------------ 🌍 World 🌍 -----------------------*//
typedef struct s_object
{
	int				id;
	void			*data;
}					t_object;

typedef struct s_world
{
	t_list			*objects;
	int				object_count;
	t_light			light;
	t_list			*extra_lights;
}					t_world;

typedef struct s_comps
{
	double			t;
	t_object_union	object;
	t_id_type		type;
	t_tuple			point;
	t_tuple			eyev;
	t_tuple			normalv;
	t_tuple			over_point;
	int				inside;
}					t_comps;

// todo               ~~~    World Init 	~~~                  *//
t_world				world(void);

// todo               ~~~    World colors 	~~~                  *//
t_intersections		intersect_world(t_world *world, t_ray r);
t_comps				prepare_computations(t_intersection i, t_ray r);
t_color				shade_hit(t_world world, t_comps comps);
t_color				color_at(t_world w, t_ray r);
t_matrix			view_transform(t_tuple from, t_tuple to, t_tuple up);
