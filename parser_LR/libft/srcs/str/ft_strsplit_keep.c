#include "libft.h"
#include "str.h"
#include "alloc.h"

static unsigned int	count_words(const char *str, const char *split_base)
{
	unsigned int	nb_words;
	size_t			i;

	nb_words = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] && ft_is_one_of(str[i], split_base))
			nb_words++;
		while (str[i] && ft_is_one_of(str[i], split_base))
			i++;
		if (str[i] && !ft_is_one_of(str[i], split_base))
			nb_words++;
		while (str[i] && !ft_is_one_of(str[i], split_base))
			i++;
	}
	return (nb_words);
}

static void			fill_word_tab(const char *str, const char *split_base, \
		char **word_tab)
{
	int i;
	int space_start;
	int word_start;

	i = 0;
	space_start = 0;
	while (str[i])
	{
		if (str[i] && ft_is_one_of(str[i], split_base))
			space_start = i;
		while (str[i] && ft_is_one_of(str[i], split_base))
			i++;
		if (space_start != i && space_start != -1)
			*word_tab++ = ft_strsub((const char*)str, space_start, \
					i - space_start);
		if (str[i] && !ft_is_one_of(str[i], split_base))
			word_start = i;
		while (str[i] && !ft_is_one_of(str[i], split_base))
			i++;
		if (word_start != i && word_start != -1)
			*word_tab++ = ft_strsub((const char*)str, word_start, \
					i - word_start);
		word_start = -1;
		space_start = -1;
	}
}

char				**ft_strsplit_keep(const char *str, const char *split_base)
{
	char			**word_tab;
	unsigned int	nb_words;

	word_tab = NULL;
	if (!str | !split_base)
		return (NULL);
	nb_words = count_words(str, split_base);
	word_tab = palloc(sizeof(char*) * (nb_words + 1));
	word_tab[nb_words] = NULL;
	fill_word_tab(str, split_base, word_tab);
	return (word_tab);
}
