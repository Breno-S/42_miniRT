/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_spaces.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgomes-d <rgomes-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:33:15 by rgomes-d          #+#    #+#             */
/*   Updated: 2026/04/13 16:44:32 by rgomes-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_words(const char *s)
{
	int	quantity_words;
	int	i;

	quantity_words = 0;
	i = 0;
	while (s[i] != 0)
	{
		if (((s[i] != 0 && !ft_isspace(s[i])))
			&& (ft_isspace(s[i + 1]) || s[i + 1] == 0))
			quantity_words++;
		i++;
	}
	return (quantity_words);
}

static void	*ft_free_array(void **s)
{
	int	i;

	i = 0;
	while (s[i] != ((void *)0))
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (((void *)0));
}

char	**ft_split_spaces(char const *s)
{
	int		begin;
	int		end;
	char	**set_words;
	int		i_arr;

	begin = 0;
	i_arr = 0;
	set_words = (char **)ft_calloc((ft_count_words(s) + 1), sizeof(char *));
	if (!set_words)
		return ((void *)0);
	while (s[begin] != 0)
	{
		end = 0;
		while (!ft_isspace(s[begin + end]) && s[begin + end] != 0)
			end++;
		if (end > 0)
		{
			set_words[i_arr] = ft_substr(s, begin, end);
			if (!set_words[i_arr++])
				return (ft_free_array((void **)set_words));
			begin += end - 1;
		}
		begin++;
	}
	return (set_words);
}
