#include "string.h"

void	w_newword (t_word *word)
{
	word->str = NULL;
	word->actlen = 0;
	word->maxlen = 0;
}

void	w_free (t_word *word)
{
	ft_strdel(&word->str);
	word->actlen = 0;
	word->maxlen = 0;
}

char	*w_addchar (t_word *word, char ch)
{
	if (word->actlen == word->maxlen)
	{
		word->maxlen += W_BUFF_SIZE;
		word->str = (char *)cl_realloc (word->actlen, word->str,  1 + word->maxlen);
//	dprintf(2, "realloc\n");
	}
	word->str[word->actlen] = ch;
//	dprintf(2,"{%c}\n",  word->str[word->actlen]);
	word->actlen++;
//	dprintf(2, "word->str {%s}\n", word->str);
	return (word->str);
}

static int	max(int a, int b)
{
	return (a > b ? a: b);
}

char	*w_addmem (t_word *word, const char *str, size_t len)
{
	if (word->actlen + len > word->maxlen)
	{
		word->maxlen += max (2 * len, W_BUFF_SIZE);
		word->str = (char *)cl_realloc (word->actlen, word->str, 1 + word->maxlen);
	}
	ft_memcpy(&word->str[word->actlen], str, len);
	word->actlen += len;
	return (word->str);
}

char	*w_addstr (t_word *word, const char *str)
{
	size_t len;

	len = ft_strlen (str);
	return (w_addmem(word, str, len));
}
