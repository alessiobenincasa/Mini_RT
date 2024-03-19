/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 23:07:18 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/19 23:24:26 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_world world(void)
{
    t_world w;
    w.objects = NULL;   
    w.object_count = 0; 
    w.light = NULL;    
    return w;
}
