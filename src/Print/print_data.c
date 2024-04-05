/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:29:59 by svolodin          #+#    #+#             */
/*   Updated: 2024/04/05 13:21:25 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "all.h"

void	print_identifier_type(t_id_type type)
{
	printf("--> Identifier is : ");
	if (type == AMBIENT_LIGHT)
		printf("AMBIENT_LIGHT\n");
	else if (type == CAMERA)
		printf("CAMERA\n");
	else if (type == LIGHT)
		printf("LIGHT\n");
	else if (type == EXTRA_LIGHT)
		printf("EXTRA_LIGHT\n");
	else if (type == SPHERE)
		printf("SPHERE\n");
	else if (type == PLANE)
		printf("PLANE\n");
	else if (type == CYLINDER)
		printf("CYLINDER\n");
	else if (type == CONE)
		printf("CONE\n");
	else
		printf("Unknown type\n");
}

void	print_color(const t_color *c)
{
	printf("Color - Red: %.2f, Green: %.2f, Blue: %.2f\n", c->red, c->green,
		c->blue);
}

void	print_tuple(t_tuple t)
{
	printf("Tuple(x: %f, y: %f, z: %f, w: %f)\n", t.x, t.y, t.z, t.w);
}

void print_data(t_world w, t_scene_data *s)
{
	t_list	*current;

	current = w.extra_lights;
	if (w.object_count)
	{
		printf("Amount of objects: %d\n", w.object_count);
		printf("\nWorlds objects:\n");
    	print_shapes(w.objects);
	}
	if (s->ambient_light)
    {
        printf("\nAmbient Light :\n");
        print_ambient(s->ambient_light);
    }
	if (!no_world_light(w.light))
	{
        printf("\nWorlds Light :\n");
        print_light(&w.light);
	}
	while (current)
	{
		print_light((t_light *)current->content);
		current = current->next;
	}
}

void print_header(void)
{
    printf("+-------------------------------------------------------------------+\n");
    printf("|                                                                   |\n");
    printf("|  ███╗   ███╗██╗███╗   ██╗██╗██████╗ ████████╗       ___           |\n");
    printf("|  ████╗ ████║██║████╗  ██║██║██╔══██╗╚══██╔══╝     [|   |=|{)__    |\n");
    printf("|  ██╔████╔██║██║██╔██╗ ██║██║██████╔╝   ██║         |___| \\/   )   |\n");
    printf("|  ██║╚██╔╝██║██║██║╚██╗██║██║██╔══██╗   ██║          /|\\      /|   |\n");
    printf("|  ██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║   ██║         / | \\     | \\  |\n");
    printf("|  ╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝   ╚═╝                        |\n");
    printf("|                                                                   |\n");
    printf("|   _             _____            _           _ _                  |\n");
    printf("|  | |           /  ___|          | |         | (_)         ___     |\n");
    printf("|  | |__  _   _  \\ `--.__   _____ | | ___   __| |_ _ __    ( _ )    |\n");
    printf("|  | '_ \\| | | |  `--. \\ \\ / / _ \\| |/ _ \\ / _` | | '_ \\   / _ \\/\\  |\n");
    printf("|  | |_) | |_| | /\\__/ /\\ V / (_) | | (_) | (_| | | | | | | (_>  <  |\n");
    printf("|  |_.__/ \\__, | \\____/  \\_/ \\___/|_|\\___/ \\__,_|_|_| |_|  \\___/\\/  |\n");
    printf("|          __/ |                                                    |\n");
    printf("|         |___/                                                     |\n");
    printf("|    ___  _ _                _                                      |\n");
    printf("|   / _ \\| | |              (_)                                     |\n");
    printf("|  / /_\\ \\ | |__   ___ _ __  _ _ __   ___ __ _ ___  __ _            |\n");
    printf("|  |  _  | | '_ \\ / _ \\ '_ \\| | '_ \\ / __/ _` / __|/ _` |           |\n");
    printf("|  | | | | | |_) |  __/ | | | | | | | (_| (_| \\__ \\ (_| |           |\n");
    printf("|  \\_| |_/_|_.__/ \\___|_| |_|_|_| |_|\\___\\__,_|___/\\__,_|           |\n");
    printf("|                                                                   |\n");
    printf("+-------------------------------------------------------------------+\n\n\n");
}