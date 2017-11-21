#fields ************************** DEFINING COLORS ************************************** #

COLOR_CLEAR		= \033[2K
COLOR_UP		= \033[A
COLOR_NOCOLOR	= \033[0m
COLOR_BOLD		= \033[1m
COLOR_UNDERLINE	= \033[4m
COLOR_BLINKING	= \033[5m
COLOR_BLACK		= \033[1;30m
COLOR_RED		= \033[1;31m
COLOR_GREEN		= \033[1;32m
COLOR_YELLOW	= \033[1;33m
COLOR_BLUE		= \033[1;34m
COLOR_VIOLET	= \033[1;35m
COLOR_CYAN		= \033[1;36m
COLOR_WHITE		= \033[1;37m

# **************************************************************************** #

SRC = \
	fatal.c \
	str/string.c \
	ft_digit_count.c \
	ft_is_1.c \
	ft_is_2.c \
	ft_is_3.c \
	get_next_line.c \
	array/ft_arraychr.c \
	array/ft_arrayjoin.c \
	array/ft_arraydel.c \
	array/ft_arraydup.c \
	array/ft_arraylen.c \
	array/ft_arraymax_f.c \
	btree/btree_add.c \
	btree/btree_new.c \
	btree/btree_print.c \
	io/ft_putchar.c \
	io/ft_putnbr.c \
	io/ft_putnbr_fd.c \
	io/ft_putnstr.c \
	io/ft_putstr.c \
	lst/ft_lst_add.c \
	lst/ft_lstint.c \
	lst/ft_lst_pop.c \
	lst/ft_lst_create.c \
	lst/ft_lst_del_one.c \
	lst/ft_lst_dup.c \
	lst/ft_lst_for_n.c \
	lst/ft_lst_foreach.c \
	lst/ft_lst_get_n.c \
	lst/ft_lst_iteri.c \
	lst/ft_lst_last.c \
	lst/ft_lst_len.c \
	lst/ft_lst_pushback.c \
	lst/ft_lst_remove.c \
	lst/ft_lst_return_if.c \
	lst/ft_lst_rev.c \
	lst/ft_lst_sort_insert.c \
	lst/ft_simple_lst_del_one.c \
	math/ft_abs.c \
	math/ft_power.c \
	math/ft_sort_int_tab.c \
	math/ft_sqrt.c \
	mem/free.c \
	mem/ft_bzero.c \
	mem/ft_calloc.c \
	mem/ft_memalloc.c \
	mem/ft_memccpy.c \
	mem/ft_memchr.c \
	mem/ft_memcmp.c \
	mem/ft_memcpy.c \
	mem/ft_memdel.c \
	mem/ft_memmove.c \
	mem/ft_memset.c \
	mem/ft_realloc.c \
	mem/palloc.c \
	str/ft_str_isdigit.c \
	str/ft_is_backslash.c \
	str/charcmp.c \
	str/ft_atoi.c \
	str/ft_buff_wchar.c \
	str/ft_chartostr.c \
	str/ft_itoa.c \
	str/ft_str_is_clr.c \
	str/ft_strcat.c \
	str/ft_strchange.c \
	str/ft_strchr.c \
	str/ft_strclr.c \
	str/ft_strcmp.c \
	str/ft_strcpy.c \
	str/ft_strdel.c \
	str/ft_strdup.c \
	str/ft_strequ.c \
	str/ft_strichr.c \
	str/ft_striter.c \
	str/ft_striteri.c \
	str/ft_strjoin.c \
	str/ft_strjoin3_free.c \
	str/ft_strlcat.c \
	str/ft_strlen.c \
	str/ft_strmap.c \
	str/ft_strmapi.c \
	str/ft_strmatch.c \
	str/ft_strncat.c \
	str/ft_strncmp.c \
	str/ft_strncpy.c \
	str/ft_strnequ.c \
	str/ft_strnew.c \
	str/ft_strnreplace.c \
	str/ft_strnstr.c \
	str/ft_strrchr.c \
	str/ft_strrcmp.c \
	str/ft_strrequ.c \
	str/ft_strrev.c \
	str/ft_strrstr.c \
	str/ft_strsplit.c \
	str/ft_strsplit_keep.c \
	str/ft_strstr.c \
	str/ft_strsub.c \
	str/ft_strsurround.c \
	str/ft_strtrim.c \
	str/ft_strtrunc.c \
	str/ft_tolower.c \
	str/ft_toupper.c \
	str/ft_strpush.c \
	str/ft_strspush.c \
	system/ft_is_executable.c \
	system/get_home.c \
	system/size_term.c \
	system/put_termcap.c \
	system/pfork.c \
	system/ppipe.c \
	parr/ft_parrlen.c \
	parr/ft_parrnew.c \
	parr/ft_parrpush.c \
	parr/ft_strarrstrn.c \
	get_opt/get_opt.c \
	get_opt/get_opt_display.c \

NAME ?= libft.a


# Defining those variables allows auto completion to occure.
APPEND=
ASAN=
TEST_FILE=

OPTIMIZATION ?= -O0

ifeq ($(ASAN),yes)
	SANITIZER ?= -fsanitize=address -fno-omit-frame-pointer
endif

SRC_DIR = srcs
OBJ_DIR = objs
LOCAL_INC = includes
CFLAGS ?= -g -Wall -Wextra -Werror
CC = gcc
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))


all: Hello_word $(OBJ_DIR) $(NAME)
	@printf "$(COLOR_CLEAR)$(COLOR_GREEN)Successfully created $(COLOR_BLUE)$(NAME) !!!$(COLOR_NOCOLOR)\n"

Hello_word:
	@printf "$(COLOR_VIOLET)$(COLOR_UNDERLINE)Compiling$(COLOR_NOCOLOR) $(COLOR_BLUE)$(NAME) ...$(COLOR_NOCOLOR)\n"

$(NAME): $(OBJ)
	@printf "$(COLOR_GREEN)Successfully created objects files for library $(COLOR_BLUE)$(NAME) !!!$(COLOR_NOCOLOR)\n"
	@printf "$(COLOR_VIOLET)Creating $(NAME) ... $(COLOR_NOCOLOR)\n"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "$(COLOR_UP)$(COLOR_CLEAR)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "$(COLOR_VIOLET)Creating objects files for library $(COLOR_BLUE)$(NAME) ... \n$(COLOR_CYAN)"
	$(CC) $(OPTIMIZATION) $(CFLAGS) -I$(LOCAL_INC) $(SANITIZER) $(APPEND) -c -o $@ $^ 
	@printf "\n$(COLOR_NOCOLOR)$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_UP)$(COLOR_CLEAR)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/printf
	@mkdir -p $(OBJ_DIR)/array
	@mkdir -p $(OBJ_DIR)/btree
	@mkdir -p $(OBJ_DIR)/io
	@mkdir -p $(OBJ_DIR)/lst
	@mkdir -p $(OBJ_DIR)/math
	@mkdir -p $(OBJ_DIR)/mem
	@mkdir -p $(OBJ_DIR)/str
	@mkdir -p $(OBJ_DIR)/system
	@mkdir -p $(OBJ_DIR)/parr
	@mkdir -p $(OBJ_DIR)/get_opt

clean:
	@printf "$(COLOR_RED)Removing object files ...$(COLOR_NOCOLOR)\n"
	@rm -rf $(OBJ_DIR)
	@printf "$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_GREEN)Removed object files !!!$(COLOR_NOCOLOR)\n"

fclean: clean
	@printf "$(COLOR_RED)Removing library $(COLOR_BLUE)$(NAME) ...$(COLOR_NOCOLOR)\n"
	@rm -rf $(NAME)
	@printf "$(COLOR_UP)$(COLOR_CLEAR)$(COLOR_GREEN)Removed library $(COLOR_BLUE)$(NAME) !!!$(COLOR_NOCOLOR)\n"

re: fclean all

test: all 
	@printf "$(COLOR_VIOLET)Compiling test $(TEST_FILE) ... $(COLOR_RESET)\n"
	@$(CC) -g $(TEST_FILE) -I$(LOCAL_INC) -L. -lft $(SANITIZER) $(APPEND)
	@printf "$(COLOR_GREEN)Done !!! Launching $(TEST_FILE) now !!!\n$(COLOR_NOCOLOR)"
	@./a.out

.PHONY: all clean fclean re
