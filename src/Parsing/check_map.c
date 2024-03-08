/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 16:21:35 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/08 16:22:26 by albeninc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	init_scene_state(t_scene_state *state)
{
	state->ambient_light_found = 0;
	state->camera_found = 0;
}

int	validate_scene_element(char **words, int nwords, t_scene_state *state)
{
	if (ft_strcmp(words[0], "A") == 0)
	{
		if (state->ambient_light_found)
		{
			printf("Erreur : Plusieurs lumières ambiantes trouvées.\n");
			return (0);
		}
		state->ambient_light_found = 1;
	}
	else if (ft_strcmp(words[0], "C") == 0)
	{
		if (state->camera_found)
		{
			printf("Erreur : Plusieurs caméras trouvées.\n");
			return (0);
		}
		state->camera_found = 1;
	}
	return (1);
}

int	validate_scene(char *filename)
{
	FILE *file = fopen(filename, "r");
	char line[1024];
	char *words;
	int nwords;
	t_scene_state state;
	init_scene_state(&state);

	if (!file)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return (0);
	}

	while (fgets(line, sizeof(line), file))
	{
		split_line_into_words(line, words, &nwords);
		if (!validate_scene_element(words, nwords, &state))
		{
			fclose(file);
			return (0);
		}
	}

	fclose(file);
	if (!state.ambient_light_found || !state.camera_found)
	{
		printf("Erreur : Il manque des éléments essentiels (lumière ambiante, caméra, etc.).\n");
		return (0);
	}
	return (1);
}