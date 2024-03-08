/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svolodin <svolodin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:44:53 by svolodin          #+#    #+#             */
/*   Updated: 2024/02/21 17:29:46 by svolodin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(const char *str, char charset)
{
	int	words;
	int	in_quote;
	int	i;

	words = 0;
	in_quote = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] == charset && !in_quote)
			i++;
		if (str[i] == '\0')
			break ;
		if (str[i] == '\"')
			in_quote = !in_quote;
		words++;
		while (str[i] && (in_quote || str[i] != charset))
		{
			if (str[i] == '\"')
				in_quote = !in_quote;
			i++;
		}
	}
	return (words);
}

static void	write_word(char *dest, const char *from, char charset)
{
	int	i;
	int	j;
	int	in_quote;

	i = 0;
	j = 0;
	in_quote = 0;
	while (from[i] && (in_quote || from[i] != charset))
	{
		if (from[i] == '\"')
		{
			in_quote = !in_quote;
			i++;
			continue ;
		}
		dest[j++] = from[i++];
	}
	dest[j] = '\0';
}

static int	find_word(const char *str, t_word_parse_state *state, char charset)
{
	int	in_quote;

	in_quote = 0;
	while (str[state->i] == charset && !in_quote)
		state->i++;
	if (str[state->i] == '\0')
		return (0);
	state->start = state->i;
	while (str[state->i] && (in_quote || str[state->i] != charset))
	{
		if (str[state->i] == '\"')
			in_quote = !in_quote;
		state->i++;
	}
	state->word_length = state->i - state->start;
	return (1);
}

static int	write_split(char **split, const char *str, char charset)
{
	t_word_parse_state	state;
	int					word_index;

	word_index = 0;
	state.start = 0;
	state.word_length = 0;
	state.i = 0;
	while (str[state.i])
	{
		if (!find_word(str, &state, charset))
			break ;
		split[word_index] = (char *)malloc(sizeof(char) * (state.word_length
					+ 1));
		if (!split[word_index])
			return (unleah(split, word_index - 1));
		write_word(split[word_index], str + state.start, charset);
		word_index++;
	}
	split[word_index] = NULL;
	return (0);
}

char	**ft_split_quotes(const char *str, char c)
{
	char	**res;
	int		words;

	words = count_words(str, c);
	res = ft_calloc(words + 1, sizeof(char *));
	if (!res)
		return (NULL);
	res[words] = 0;
	if (write_split(res, str, c) == -1)
	{
		free(res);
		return (NULL);
	}
	return (res);
}
