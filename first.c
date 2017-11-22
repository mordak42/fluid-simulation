#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"

struct token_lst	*lr_first_of_symbol(struct s_grammar_rule *grammar_rule, enum e_symbol symbol)
{
}

struct morpheme_lst	*lr_first(struct s_grammar_rule *grammar_rule, struct morpheme_list *rules)
{
	struct morpheme_list *res
	
	while (rules)
	{
		if (rules->morpheme == EPSILON)
			return (NULL);
		else if (IS_TOKEN(rules->morpheme))
			return (rules);//attention au leaks
		else if (IS_SYMBOL(rules->morpheme))
		{
/*
**				rules s'ecrit Aß
*/
			struct morpheme_list *A = rules;
			struct morpheme_list *B = rules->next;
			struct morpheme_list *first_A = lr_first_of_symbol(A->symbol);

			if (derives_epsilon(first_A))
				return (ft_genlst_union(first_A, lr_first(grammar_rule, B)))
			else
				return first_A;
		}
		rules = rules->next;
	}
}
