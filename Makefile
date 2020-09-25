# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/07 12:41:01 by anystrom          #+#    #+#              #
#    Updated: 2020/09/25 13:54:22 by anystrom         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME =		doom-nukem
OEXT = 		.o
LEXT = 		.a
FLG = 		-O2
SRCFILE =	doom.c gfx.c loop.c camera.c main_menu.c interact.c \
			util.c menu.c gfx_draw.c posteff.c defaults.c \
			set_variables.c
KEYFILE =	key_editor.c key_game.c key_menu.c key_state.c
DRAWEXT =	draw_hud.c
FILESYS =	fileformat.c save_level.c
EDTFILE =	editor.c render_editor.c
ANMFILE =	staireff.c
COLFILE	=	draw.c draw_utils.c window.c
RNDFILE =	plane_z.c plane_y.c plane_x.c render.c slope_z.c \
			part_dda.c
GRAFILE	=	gravity.c move.c collision.c
BMPFILE =	bmp_reader.c
TXTFILE =	set_string.c
MTHFILE =	vert.c
SPRFILE =	sprites.c begin_sprites.c shooting.c sprite.c pokemon_ai.c
SRC =		$(addprefix ./src/,$(SRCFILE)) \
			$(addprefix ./src/draw_extra/,$(DRAWEXT)) \
			$(addprefix ./src/key/,$(SRCFILE)) \
			$(addprefix ./src/editor/,$(EDTFILE)) \
			$(addprefix ./src/fs/,$(FILESYS)) \
			$(addprefix ./src/animation/,$(ANMFILE)) \
			$(addprefix ./src/render/,$(RNDFILE)) \
			$(addprefix ./src/draw/,$(COLFILE)) \
			$(addprefix ./src/gravity/,$(GRAFILE)) \
			$(addprefix ./src/randenc/,$(ENCFILE)) \
			$(addprefix ./src/bmp/,$(BMPFILE)) \
			$(addprefix ./src/text/,$(TXTFILE)) \
			$(addprefix ./src/math/,$(MTHFILE)) \
			$(addprefix ./src/sprite/,$(SPRFILE))
LIBFT =		$(addprefix ./obj/libft,$(LEXT))
OBJS =		$(SRC:.c=$(OEXT))
OBJ =		$(addprefix ./obj/,$(SRCFILE:.c=$(OEXT))) \
			$(addprefix ./obj/key/,$(KEYFILE:.c=$(OEXT))) \
			$(addprefix ./obj/draw_extra/,$(DRAWEXT:.c=$(OEXT))) \
			$(addprefix ./obj/editor/,$(EDTFILE:.c=$(OEXT))) \
			$(addprefix ./obj/fs/,$(FILESYS:.c=$(OEXT))) \
			$(addprefix ./obj/animation/,$(ANMFILE:.c=$(OEXT))) \
			$(addprefix ./obj/render/,$(RNDFILE:.c=$(OEXT))) \
			$(addprefix ./obj/draw/,$(COLFILE:.c=$(OEXT))) \
			$(addprefix ./obj/gravity/,$(GRAFILE:.c=$(OEXT))) \
			$(addprefix ./obj/randenc/,$(ENCFILE:.c=$(OEXT))) \
			$(addprefix ./obj/bmp/,$(BMPFILE:.c=$(OEXT))) \
			$(addprefix ./obj/text/,$(TXTFILE:.c=$(OEXT))) \
			$(addprefix ./obj/math/,$(MTHFILE:.c=$(OEXT))) \
			$(addprefix ./obj/sprite/,$(SPRFILE:.c=$(OEXT)))
DEPNS =		$(OBJ:.o=.d)
OBJDIR =	./obj/
SRCDIR =	./src/
INCL =		-I ./SDL2 -I ./libft -I ./includes
MLXLIB =	-L /usr/local/lib
PWD =		$(shell pwd)
OBJFRAME =	-F ./frameworks
FRAMEWORK =	-F $(PWD)/frameworks -framework SDL2 -framework SDL2_mixer -framework SDL2_net -Wl,-rpath $(PWD)/frameworks
RED =		\033[0;31m
STOP =		\033[0m

.PHONY: all clean fclean re obj

all: $(NAME)

$(LIBFT):
	@echo Compiling Libft libraries.
	@make -C ./libft

-include $(DEPNS)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@echo "Compiling DoomNukem -> $(RED)$@$(STOP)"
	@gcc -g $(OBJFRAME) $(FLG) -MMD $(INCL) -o $@ -c $<

$(NAME): $(OBJ) $(LIBFT)
	@gcc $(FRAMEWORK) $(FLG) $(INCL) -o $(NAME) $(OBJ) $(LIBFT) $(MLXLIB)
	@echo "read 'icns' (-16455) \"gfx/icon.icns\";" >> icon.rsrc
	@Rez -a icon.rsrc -o $(NAME)
	@SetFile -a C $(NAME)
	@rm icon.rsrc
	@echo Executable created successfully. Get maps with 'make git'.
	@echo Run the executable as ./doom-nukem. No args.

clean:
	@echo "Removing Doom-Nukem libraries."
	@/bin/rm -f $(OBJ)
	@/bin/rm -f $(DEPNS)
	@echo Removing Libft libraries.
	@make -C ./libft fclean

fclean: clean
	@echo Removing binaries.
	@/bin/rm -f $(NAME)

run: all
	./doom-nukem

winup:
ifeq ($(OS),Windows_NT)
	@rm -r ../../../../source/repos/DoomNukem/x64/Debug/gfx
	@rm -r ../../../../source/repos/DoomNukem/x64/Debug/Audio
	@cp -r gfx ../../../../source/repos/DoomNukem/x64/Debug/
	@cp -r Audio ../../../../source/repos/DoomNukem/x64/Debug/
else
	@echo "Nothing to do."
endif

re: fclean all
