# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bmickael <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/18 22:40:01 by bmickael          #+#    #+#              #
#    Updated: 2017/12/12 21:00:09 by bmickael         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = mod1
CC = g++

### MAIN FLAGS ###

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
ifeq ($(DEBUG),yes)
	CFLAGS = -Wall -Wextra -Werror -std=c++11 -g -O0 -fsanitize=address -framework OpenCL -Ofast -Wno-unused-command-line-argument -Wno-error-unused-variable
else
	CFLAGS = -Wall -Wextra -Werror -std=c++11 -framework OpenCL -Ofast -Wno-unused-command-line-argument -Wno-error-unused-variable
endif
else
ifeq ($(DEBUG),yes)
	CFLAGS = -Wall -Wextra -Werror -std=c++11 -g -O0 -fsanitize=address -lopencl -Ofast -Wno-unused-command-line-argument -Wno-error-unused-variable
else
	CFLAGS = -Wall -Wextra -Werror -std=c++11 -lopencl -Ofast -Wno-unused-command-line-argument -Wno-error-unused-variable
endif
endif

### SOURCES ###

SRC_CORE = main mod1 frameProductor renderedFrame renderer physician \
userInterface semaphore lagrange polynom graviter physicLaw pressurer physicItems fps idle famine sdlContext
VPATH = srcs

OBJ_DIR = objs
TMP = $(basename $(notdir $(SRC_CORE)))
OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(TMP)))

IFLAGS = -I./srcs
LDFLAGS = -L $(HOME)/.brew/Cellar/sdl2/2.0.7/lib/ -lSDL2 -lpthread -L $(HOME)/.brew/Cellar/sdl2_ttf/2.0.14/lib -lSDL2_ttf

.PHONY: all clean fclean re help

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LDFLAGS)

$(OBJ_DIR)/main.o: main.cpp mod1.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/mod1.o: mod1.cpp \
	frameProductor.hpp \
	userInterface.hpp \
	renderer/renderedFrame.hpp \
	utils/pool.hpp \
	overlay/fps.hpp \
	overlay/idle.hpp \
	overlay/famine.hpp \
	overlay/sdlContext.hpp \
	mod1.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/userInterface.o: userInterface.cpp \
	utils/pool.hpp \
	utils/fifo.hpp \
	utils/semaphore.hpp \
	renderer/renderedFrame.hpp \
	physician/physicItems.hpp \
	overlay/fps.hpp \
	overlay/idle.hpp \
	overlay/famine.hpp \
	overlay/sdlContext.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/frameProductor.o: frameProductor.cpp \
	utils/pool.hpp \
	math/polynom.hpp \
	physician/physician.hpp \
	renderer/renderer.hpp \
	renderer/renderedFrame.hpp \
	physician/physicItems.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/physician.o: physician/physician.cpp \
	physician/physician.hpp \
	physician/physicItems.hpp \
	physician/graviter.hpp \
	physician/physicLaw.hpp \
	physician/pressurer.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/renderedFrame.o: renderer/renderedFrame.cpp \
	renderer/renderedFrame.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/renderer.o: renderer/renderer.cpp \
	renderer/renderer.hpp \
	renderer/renderedFrame.hpp \
	physician/physicItems.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/semaphore.o: utils/semaphore.cpp \
	utils/semaphore.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/lagrange.o: math/lagrange.cpp \
	math/polynom.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/polynom.o: math/polynom.cpp \
	math/polynom.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/graviter.o: physician/graviter.cpp \
	physician/graviter.hpp \
	physician/physicItems.hpp \
	physician/physicLaw.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/physicLaw.o: physician/physicLaw.cpp \
	physician/physicLaw.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/pressurer.o: physician/pressurer.cpp \
	physician/pressurer.hpp \
	physician/physicItems.hpp \
	physician/physicLaw.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/physicItems.o: physician/physicItems.cpp \
	physician/physicItems.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/fps.o: overlay/fps.cpp \
	overlay/fps.hpp \
	overlay/sdlContext.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)
	
$(OBJ_DIR)/idle.o: overlay/idle.cpp \
	overlay/idle.hpp \
	overlay/sdlContext.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/famine.o: overlay/famine.cpp \
	overlay/famine.hpp \
	overlay/sdlContext.hpp
	$(CC) -c $(CFLAGS) -o $@ $< $(IFLAGS)

$(OBJ_DIR)/sdlContext.o: overlay/sdlContext.cpp \
	overlay/sdlContext.hpp
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
