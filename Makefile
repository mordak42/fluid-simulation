# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmickael <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/18 22:40:01 by bmickael          #+#    #+#              #
#    Updated: 2017/11/19 15:41:25 by bmickael         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mod1
CC = g++

### MAIN FLAGS ###

ifeq ($(DEBUG),yes)
	CFLAGS = -Wall -Wextra -Werror -std=c++11 -g -O0 -fsanitize=address
else
	CFLAGS = -Wall -Wextra -Werror -std=c++11
endif

### SOURCES ###

SRC_CORE = main mod1 pool frameProductor renderer physician userInterface semaphore imgData

SRC_LIST = $(SRC_CORE)

VPATH = srcs \
srcs/utils \
srcs/frameProductor \
srcs/userInterface \
srcs/frameProductor/physician \
srcs/frameProductor/renderer \

## HEADERS

HEADERS_LIST = includes/mod1 \
srcs/pool \
srcs/utils/imgData \
srcs/utils/semaphore \
srcs/utils/fifo \
srcs/frameProductor/physician/physician \
srcs/frameProductor/renderer/renderer \
srcs/frameProductor/frameProductor \
srcs/userInterface/userInterface

### ~~~~~~~~~~ ###

SRC = $(addsuffix .cpp, $(SRC_LIST))
OBJ_DIR = objs
TMP = $(basename $(notdir $(SRC)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(TMP)))
HEADERS = $(addsuffix .hpp, $(HEADERS_LIST))

IFLAGS = -I./includes -I./srcs -I$(HOME)/.brew/Cellar/sdl2/2.0.7/include/
LDFLAGS = -L $(HOME)/.brew/Cellar/sdl2/2.0.7/lib/ -lSDL2

.PHONY: all clean fclean re help

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

help:
	@echo
	@echo "Programm $(NAME)"
	@echo
	@echo "--------------------------------------------------------------------------"
	@echo " Disp rules."
	@echo
	@echo " all     : Compile the program $(NAME) into $(BINDIR) directory."
	@echo " re      : Recompile all objets of the programm."
	@echo " clean   : Remove objects."
	@echo " fclean  : Remove objects and programm."
	@echo " help    : Display this."
	@echo "--------------------------------------------------------------------------"
