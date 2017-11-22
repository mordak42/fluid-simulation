#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "parser.h"

/*
s' -> s
s -> c c
c -> E c
c -> F

petite lettre = symbole
grosse lettre = tokens

symbols ∈  0 ... 999
tokens ∈   1000 ... 1990

node -> child 1 child 2 child 3 ... (max 6)
*/

enum morpheme {
	start_symbol = 1,
	s,
	c,
	dollar = 1000,
	E,
	F
};

struct gramma_rule {
	enum morpheme node;
	enum morpheme childs[6];
};

#define NB_RULES 4

static struct gramma_rule rules[NB_RULES] = {
	{start_symbol, {s}},
	{s, {c, c}},
	{c, {E, c}},
	{c, {F}}
};

/*
{[S -> C.C, $]}
*/

struct item;

struct item {
	struct item *next_item;
	struct gramma_rule *rule;
	int point;
	enum morpheme token;
};

/*
{[S' -> .S, $]}	0	{[S' -> .S, $]; [S -> .C C, $]; [C -> .e C, e/f]; [C -> .f, e/f]}
*/

/* Single line of LR transitory array */

struct line;

struct line {
	struct line *next_line;
	int state;
	struct item *items_list;
};

struct line *create_line(int state) {
	struct line *new_line;
	if (!(new_line = (struct line *)calloc(sizeof(struct line), 1)))
		return NULL;
	new_line->state = state;
	return new_line;
}

struct line *add_line(struct line **array, int state) {
	struct line *new_line = create_line(state);
	if (!new_line) {
		printf("BAD ALLOCATION\n");
		exit(EXIT_FAILURE);
	}
	return (ft_genlst_pushback((void **)array, new_line));
}

struct item *create_item(struct gramma_rule *rule, int point, enum morpheme token) {
	struct item *item;
	if (!(item = (struct item *)calloc(sizeof(struct item), 1)))
		return NULL;
	item->rule = rule;
	item->point = point;
	item->token = token;
	return item;
}

struct item *add_item(struct item **item_lst, struct gramma_rule *rule, int point, enum morpheme token) {
	struct item *new_item = create_item(rule, point, token);
	if (!new_item) {
		printf("BAD ALLOCATION\n");
		exit(EXIT_FAILURE);
	}
	return (ft_genlst_pushback((void **)item_lst, new_item));
}

int main(void)
{
	struct line *array = NULL;
	struct line *current_line;

	current_line = add_line(&array, 10);
	add_item(&current_line->items_list, &rules[0], 0, dollar);
	add_item(&current_line->items_list, &rules[1], 4, F);
	add_item(&current_line->items_list, &rules[2], 0, dollar);
	current_line = add_line(&array, 20);
	current_line = add_line(&array, 30);
	add_item(&current_line->items_list, &rules[2], 5, E);
	add_item(&current_line->items_list, &rules[1], 0, dollar);
	add_item(&current_line->items_list, &rules[0], 0, dollar);
	add_item(&current_line->items_list, &rules[1], 4, F);
	add_item(&current_line->items_list, &rules[2], 0, dollar);
	current_line = add_line(&array, 20);
	current_line = add_line(&array, 30);
	add_item(&current_line->items_list, &rules[2], 5, E);
	add_item(&current_line->items_list, &rules[1], 0, dollar);
	add_item(&current_line->items_list, &rules[0], 0, dollar);
	add_item(&current_line->items_list, &rules[1], 4, F);
	add_item(&current_line->items_list, &rules[2], 0, dollar);
	current_line = add_line(&array, 20);
	current_line = add_line(&array, 30);
	add_item(&current_line->items_list, &rules[2], 5, E);
	add_item(&current_line->items_list, &rules[1], 0, dollar);
	add_item(&current_line->items_list, &rules[0], 0, dollar);
	add_item(&current_line->items_list, &rules[1], 4, F);
	add_item(&current_line->items_list, &rules[2], 0, dollar);
	current_line = add_line(&array, 20);
	current_line = add_line(&array, 30);
	add_item(&current_line->items_list, &rules[2], 5, E);
	add_item(&current_line->items_list, &rules[1], 0, dollar);
	add_item(&current_line->items_list, &rules[0], 0, dollar);
	add_item(&current_line->items_list, &rules[1], 4, F);
	add_item(&current_line->items_list, &rules[2], 0, dollar);
	current_line = add_line(&array, 20);
	current_line = add_line(&array, 30);
	add_item(&current_line->items_list, &rules[2], 5, E);
	add_item(&current_line->items_list, &rules[1], 0, dollar);
	add_item(&current_line->items_list, &rules[0], 0, dollar);
	add_item(&current_line->items_list, &rules[1], 4, F);
	add_item(&current_line->items_list, &rules[2], 0, dollar);
	current_line = add_line(&array, 20);
	current_line = add_line(&array, 30);
	add_item(&current_line->items_list, &rules[2], 5, E);
	add_item(&current_line->items_list, &rules[1], 0, dollar);
	add_item(&current_line->items_list, &rules[0], 0, dollar);
	add_item(&current_line->items_list, &rules[1], 4, F);
	add_item(&current_line->items_list, &rules[2], 0, dollar);
	current_line = add_line(&array, 20);
	current_line = add_line(&array, 30);
	add_item(&current_line->items_list, &rules[2], 5, E);
	add_item(&current_line->items_list, &rules[1], 0, dollar);
	add_item(&current_line->items_list, &rules[0], 0, dollar);
	add_item(&current_line->items_list, &rules[1], 4, F);
	add_item(&current_line->items_list, &rules[2], 0, dollar);
	current_line = add_line(&array, 20);
	current_line = add_line(&array, 30);
	add_item(&current_line->items_list, &rules[2], 5, E);
	add_item(&current_line->items_list, &rules[1], 0, dollar);
	return 0;
}
