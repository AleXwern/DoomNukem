# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/07 12:41:01 by anystrom          #+#    #+#              #
#    Updated: 2020/06/30 16:28:38 by anystrom         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = doomdemo
FLG =
SRCFILE = wolf.c fileformat.c gfx.c key_input.c render.c draw.c move.c \
			interact.c util.c floor.c menu.c gfx_draw.c posteff.c
TESTFILE = testkey.c
SRC = $(addprefix ./src/,$(SRCFILE))
LIBFT = ./obj/libft.a
OBJS = $(SRC:.c=.o)
OBJ = $(addprefix ./obj/,$(SRCFILE:.c=.o))
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
	@echo "Compiling Wolf3D -> $(RED)$@$(STOP)"
	@gcc $(OBJFRAME) $(FLG) $(INCL) -o $@ -c $<

$(NAME): $(OBJ) $(LIBFT)
	gcc $(FRAMEWORK) $(FLG) $(INCL) -o $(NAME) $(OBJ) $(LIBFT) $(MLXLIB)
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
