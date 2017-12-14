/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/10 00:38:06 by vcombey           #+#    #+#             */
/*   Updated: 2016/12/12 20:47:55 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_count_words(char const *s, char c)
{
	unsigned int	i;
	unsigned int	nb_words;

	i = 0;
	nb_words = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			nb_words++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (nb_words);
}

static char			**ft_malloc_t(char const *s, char **t, char c)
{
	unsigned int	i;
	unsigned int	no_words;
	unsigned int	nb_letters;

	i = 0;
	no_words = -1;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			no_words++;
		nb_letters = 0;
		while (s[i] && s[i] != c)
		{
			i++;
			nb_letters++;
		}
		if (nb_letters != 0)
		{
			if (!(t[no_words] = ft_strnew(nb_letters)))
				return (NULL);
		}
	}
	return (t);
}

static void			ft_fill_t(char const *s, char **t, char c)
{
	unsigned int	i;
	unsigned int	no_words;
	unsigned int	no_letters;

	i = 0;
	no_words = -1;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			no_words++;
		no_letters = 0;
		while (s[i] && s[i] != c)
		{
			t[no_words][no_letters] = s[i];
			i++;
			no_letters++;
		}
	}
}

char				**ft_strsplit(char const *s, char c)
{
	unsigned int	nb_words;
	unsigned int	i;
	char			**t;

	if (!s)
		return (NULL);
	i = 0;
	nb_words = ft_count_words(s, c);
	t = NULL;
	if (!(t = (char **)malloc(sizeof(char *) * (nb_words + 1))))
		return (NULL);
	t[nb_words] = NULL;
	if (ft_malloc_t(s, t, c) == NULL)
		return (NULL);
	ft_fill_t(s, t, c);
	return (t);
}
