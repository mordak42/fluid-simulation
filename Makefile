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
MAIN_DIRECTORY = .

### MAIN FLAGS ###

ifeq ($(DEBUG),yes)
	CFLAGS = -Wall -Wextra -Werror -std=c++11 -g -O0 -fsanitize=address
else
	CFLAGS = -Wall -Wextra -Werror -std=c++11
endif

### SOURCES ###

SRC_CORE = main pool imgData

SRC_LIST = $(SRC_CORE)
VPATH = $(MAIN_DIRECTORY)/srcs

## HEADERS

HEADERS = ./includes/mod1.hpp ./srcs/pool.hpp ./srcs/imgData.hpp

### ~~~~~~~~~~ ###

SRC = $(addsuffix .cpp, $(SRC_LIST))
OBJ_DIR = $(MAIN_DIRECTORY)/objs
TMP = $(basename $(notdir $(SRC)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(TMP)))

MLX = minilibx_sierra

IFLAGS = -I$(MAIN_DIRECTORY)/includes -I$(MLX) -I$(HOME)/.brew/Cellar/sdl2/2.0.7/include/
LDFLAGS = -L $(HOME)/.brew/Cellar/sdl2/2.0.7/lib/ -lsdl2

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
