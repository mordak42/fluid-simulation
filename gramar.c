#include "parser_lr.h"
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"

static struct static_grammar_rule rules[NB_RULES] = {
	{start_symbol, {s}},
	{s, {c, c}},
	{c, {E, c}},
	{c, {F}}
};

void	init_grammar_rules(struct s_parser_lr *parser_lr)
{
	int	i = 0;

	while (i < NB_RULES)
	{
		parser_lr->rules[i].node = rules[i].node;
		parser_lr->rules[i].node = rules[i].node;
		int	j = 0;
		parser_lr->rules[i].child = NULL;
		while (rules[i].child[j] > 0 && j < 7)
		{
			ft_genlst_pushback(&parser_lr->rules[i].child, new_morpheme_lst(rules[i].child[j]));
			j++;
		}
		i++;
	}
}

int		get_first_grammar_rule(struct s_grammar_rule *grammar_rule, enum e_symbol symbol) 
{
	int		i;

	i = 0;
	while (grammar_rule[i])
	{
		if (grammar_rule[i].node == symbol)
			return (i);
		i++;
	}
	return (-1);
}
