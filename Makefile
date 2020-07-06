# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/07 12:41:01 by anystrom          #+#    #+#              #
#    Updated: 2020/07/06 15:41:28 by anystrom         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = doom-nukem
FLG =
SRCFILE = wolf.c fileformat.c gfx.c loop.c render.c draw.c move.c \
			interact.c util.c floor.c menu.c gfx_draw.c posteff.c \
			defaults.c
KEYFILE = key_editor.c key_game.c key_menu.c key_state.c
TESTFILE = testkey.c
SRC = $(addprefix ./src/,$(SRCFILE)) $(addprefix ./src/key/,$(SRCFILE))
LIBFT = ./obj/libft.a
OBJS = $(SRC:.c=.o)
OBJ = $(addprefix ./obj/,$(SRCFILE:.c=.o)) $(addprefix ./obj/key/,$(KEYFILE:.c=.o))
OBJDIR = ./obj/
SRCDIR = ./src/
INCL = -I ./SDL2 -I ./libft -I ./includes
MLXLIB = -L /usr/local/lib
PWD = $(shell pwd)
OBJFRAME = -F ./frameworks
FRAMEWORK = -F $(PWD)/frameworks -framework SDL2 -framework SDL2_image -framework SDL2_mixer -Wl,-rpath $(PWD)/frameworks
DUMMY = -F $(PWD)/frameworks -framework SDL2 -framework SDL2_image -framework SDL2_mixer -Wl,-rpath $(PWD)/frameworks
RED = \033[0;31m
STOP = \033[0m

.PHONY: all clean fclean re obj

all: $(NAME)

$(LIBFT):
	@echo Compiling Libft libraries.
	@make -C ./libft

$(OBJDIR)%.o:$(SRCDIR)%.c
ifeq ($(OS),Windows_NT)
	echo $@
	clang -I ./includes -I ./libft -I C:\SDL\SDL2_image-2.0.5\include -I C:\SDL\SDL2-2.0.12\include -I C:\SDL\SDL2_mixer-2.0.4\include  -o $@ -c $<
else
	@echo "Compiling Wolf3D -> $(RED)$@$(STOP)"
	@gcc $(OBJFRAME) $(FLG) $(INCL) -o $@ -c $<
endif

$(NAME): $(OBJ) $(LIBFT)
ifeq ($(OS),Windows_NT)
	echo hi
else
	gcc $(FRAMEWORK) $(FLG) $(INCL) -o $(NAME) $(OBJ) $(LIBFT) $(MLXLIB)
endif
	@echo Done.

test: $(LIBFT)
	gcc $(INCL) -o $(NAME) testkey.c $(LIBFT) $(MLXLIB) $(FRAMEWORK)

clean:
	@echo "Removing Wolf3D libraries."
	@/bin/rm -f $(OBJ)
	@echo Removing Libft libraries.
	@make -C ./libft fclean

fclean: clean
	@echo Removing binaries.
	@/bin/rm -f $(NAME)

merge:
	git checkout master
	git pull https://github.com/AleXwern/DoomNukem.git master

re: fclean all
