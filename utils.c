struct line *create_line(int state) {
	struct line *new_line;
	if (!(new_line = (struct line *)calloc(sizeof(struct line), 1)))
		return NULL;
	new_line->state = state;
	return new_line;
}

/*
**	struct line *add_line(struct line **array, int state, struct item *item_lst) {
**		struct line *new_line = create_line(state);
**		if (!new_line) {
**			printf("BAD ALLOCATION\n");
**			exit(EXIT_FAILURE);
**		}
**		new_line->state = state;
**		new_line->item_list = item_list;
**		return (ft_genlst_add((void **)array, new_line));
**	}
*/

struct item *create_item(struct gramma_rule *rule, int point, enum morpheme token) {
	struct item *item;
	if (!(item = (struct item *)calloc(sizeof(struct item), 1)))
		return NULL;
	item->rule = rule;
	item->point = point;
	item->token = token;
	return item;
}

/*
**	struct item *add_item(struct item **item_lst, struct gramma_rule *rule, int point, enum morpheme token) {
**		struct item *new_item = create_item(rule, point, token);
**		if (!new_item) {
**			printf("BAD ALLOCATION\n");
**			exit(EXIT_FAILURE);
**		}
**		return (ft_genlst_add((void **)item_lst, new_item));
**	}
*/

