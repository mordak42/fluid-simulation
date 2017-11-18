# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saubenne <saubenne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/23 15:41:46 by saubenne          #+#    #+#              #
#    Updated: 2017/11/17 04:35:33 by bmickael         ###   ########.fr        #
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

SRC_CORE = main

SRC_LIST = $(SRC_CORE)
VPATH = $(MAIN_DIRECTORY)/srcs

## HEADERS

HEADERS = $(MAIN_DIRECTORY)/includes/mod1.hpp

### ~~~~~~~~~~ ###

SRC = $(addsuffix .cpp, $(SRC_LIST))
OBJ_DIR = $(MAIN_DIRECTORY)/objs
TMP = $(basename $(notdir $(SRC)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(TMP)))

MLX = minilibx_sierra

IFLAGS = -I$(MAIN_DIRECTORY)/includes -I$(MLX)
LDFLAGS =  -framework openGL -framework AppKit -L ./$(MLX) -lmlx

.PHONY: all clean fclean re help

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.cpp $(HEADERS)
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	make -C $(MLX)/ clean
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
