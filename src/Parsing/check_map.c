/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albeninc <albeninc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 20:00:02 by albeninc          #+#    #+#             */
/*   Updated: 2024/03/12 17:18:59 by albeninc         ###   ########.fr       */
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
    (void)nwords;
    
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

char **split_line_into_words(char *line, int *nwords) 
{
    char **words = malloc(1024 * sizeof(char *));
    char word[256];
    int i;
	int j; 
	int count;

	i = 0;
	j = 0;
	count = 0;
    if (!words) {
        perror("Memory allocation failed for words");
        exit(EXIT_FAILURE); 
    }

    while (line[i] != '\0' && count < 1024) {
        while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n') i++;
        j = 0;
        while (line[i] != ' ' && line[i] != '\0' && line[i] != '\n' && j < 255) {
            word[j++] = line[i++];
        }
        word[j] = '\0';
        if (j > 0) {
            words[count] = ft_strdup(word);
            if (!words[count]) {
                perror("Memory allocation failed for a word");
                while (count > 0) { 
                    free(words[--count]);
                }
                free(words); 
                exit(EXIT_FAILURE); 
            }
            count++;
        }
        if (line[i] == '\0') 
			break;
        i++;
    }
    *nwords = count;
    return words;
}


int validate_scene(char *filename) 
{
    int fd = open(filename, O_RDONLY);
    char *line;
    char **words;
    int nwords;
    t_scene_state state;
    int result = 1; 

    init_scene_state(&state);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return (0);
    }

    while ((line = get_next_line(fd)) != NULL) {
        words = split_line_into_words(line, &nwords);
        if (!validate_scene_element(words, nwords, &state)) {
            result = 0; 
            for (int i = 0; i < nwords; i++) { 
                free(words[i]);
            }
            free(words); 
            free(line); 
            break; 
        }
        for (int i = 0; i < nwords; i++) { 
            free(words[i]);
        }
        free(words); 
        free(line); 
    }

    close(fd); 

    if (result && (!state.ambient_light_found || !state.camera_found)) {
        printf("Erreur : Il manque des éléments essentiels (lumière ambiante, caméra, etc.).\n");
        result = 0;
    }

    return result; 
}

