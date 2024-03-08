/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:23:44 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/08 19:24:19 by albeninc         ###   ########.fr       */
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

char	**split_line_into_words(char *line, int *nwords)
{
	char	**words;
	char	word[256];
	int		i;

	i = 0, j;
	i = 0, j = 0, count;
	words = malloc(1024 * sizeof(char *));
	i = 0, j = 0, count = 0;
	if (!words)
	{
		perror("Memory allocation failed for words");
		exit(EXIT_FAILURE);
	}
	while (line[i] != '\0' && count < 1024)
	{
		while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
			i++;
		j = 0;
		while (line[i] != ' ' && line[i] != '\0' && line[i] != '\n' && j < 256
			- 1)
		{
			word[j++] = line[i++];
		}
		word[j] = '\0';
		if (j > 0)
		{
			words[count] = strdup(word);
			if (!words[count])
			{
				perror("Memory allocation failed for a word");
				exit(EXIT_FAILURE);
			}
			count++;
		}
		if (line[i] == '\0')
			break ;
		i++;
	}
	*nwords = count;
	return (words);
}

int	validate_scene(char *filename)
{
	int				fd;
	char			*line;
	char			**words;
	int				nwords;
	t_scene_state	state;

	fd = open(filename, O_RDONLY);
	init_scene_state(&state);
	if (fd == -1)
	{
		perror("Erreur lors de l'ouverture du fichier");
		return (0);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		words = split_line_into_words(line, &nwords);
		if (!validate_scene_element(words, nwords, &state))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
	}
	close(fd);
	if (!state.ambient_light_found || !state.camera_found)
	{
		printf("Erreur : Il manque des éléments essentiels (lumière ambiante, caméra, etc.).\n ");
		return (0);
	}
	return (1);
}
