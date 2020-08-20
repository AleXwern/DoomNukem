# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/07 12:41:01 by anystrom          #+#    #+#              #
#    Updated: 2020/08/20 12:07:40 by tbergkul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME =		doom-nukem
OEXT = 		.o
LEXT = 		.a
FLG = 		-O2
SRCFILE =	doom.c gfx.c loop.c render.c draw.c move.c \
			interact.c util.c menu.c gfx_draw.c posteff.c defaults.c \
			main_menu.c gravity.c sprite.c
KEYFILE =	key_editor.c key_game.c key_menu.c key_state.c
LOADDRAW =	gun.c gunextra.c loadextra.c
FILESYS =	fileformat.c save_level.c
EDTFILE =	editor.c render_editor.c
ANMFILE =	staireff.c
RNDFILE =	plane_z.c plane_y.c plane_x.c \
			slope_z.c \
			part_dda.c
SRC =		$(addprefix ./src/,$(SRCFILE)) \
			$(addprefix ./src/load_draw/,$(LOADDRAW)) \
			$(addprefix ./src/key/,$(SRCFILE)) \
			$(addprefix ./src/editor/,$(EDTFILE)) \
			$(addprefix ./src/fs/,$(FILESYS)) \
			$(addprefix ./src/animation/,$(ANMFILE)) \
			$(addprefix ./src/render/,$(RNDFILE))
LIBFT =		$(addprefix ./obj/libft,$(LEXT))
OBJS =		$(SRC:.c=$(OEXT))
OBJ =		$(addprefix ./obj/,$(SRCFILE:.c=$(OEXT))) \
			$(addprefix ./obj/key/,$(KEYFILE:.c=$(OEXT))) \
			$(addprefix ./obj/load_draw/,$(LOADDRAW:.c=$(OEXT))) \
			$(addprefix ./obj/editor/,$(EDTFILE:.c=$(OEXT))) \
			$(addprefix ./obj/fs/,$(FILESYS:.c=$(OEXT))) \
			$(addprefix ./obj/animation/,$(ANMFILE:.c=$(OEXT))) \
			$(addprefix ./obj/render/,$(RNDFILE:.c=$(OEXT)))
DEPNS =		$(OBJ:.c=.d)
OBJDIR =	./obj/
SRCDIR =	./src/
INCL =		-I ./SDL2 -I ./libft -I ./includes
MLXLIB =	-L /usr/local/lib
WININC =	-I "C:\Program Files (x86)Windows Kits\10\Include\10.0.18362.0\ucrt" -I /libft/ -I /includes/
CLINC =		/I "C:\Program Files (x86)Windows Kits\10\Include\10.0.18362.0\ucrt" /I /libft/ /I /includes/
WINLIB =	-L "C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\ucrt\x64"
PWD =		$(shell pwd)
OBJFRAME =	-F ./frameworks
FRAMEWORK =	-F $(PWD)/frameworks -framework SDL2 -framework SDL2_image -framework SDL2_mixer -Wl,-rpath $(PWD)/frameworks
WINSDLI =	-I C:/SDL/SDL2-2.0.12/include/ \
			-I C:/SDL/SDL2_mixer-2.0.4/include/ \
			-I C:/SDL/SDL2_image-2.0.5/include/
DUMMY2 =	-L C:/SDL/SDL2-2.0.12/lib/x64 SDL2.lib SDL2main.lib\
			-L C:/SDL/SDL2_mixer-2.0.4/lib/x64 SDL2_mixer.lib \
			-L C:/SDL/SDL2_image-2.0.5/lib/x64 SDL2_image.lib
WINSDLL =	-L C:/SDL/SDL2-2.0.12/lib/x64 \
			-L C:/SDL/SDL2_mixer-2.0.4/lib/x64 \
			-L C:/SDL/SDL2_image-2.0.5/lib/x64
RED =		\033[0;31m
STOP =		\033[0m

.PHONY: all clean fclean re obj

all: $(NAME)

$(LIBFT):
	@echo Compiling Libft libraries.
	@make -C ./libft

#-include $(DEPNS)

$(OBJDIR)%.o:$(SRCDIR)%.c
	@echo "Compiling Wolf3D -> $(RED)$@$(STOP)"
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
	@echo "Removing Wolf3D libraries."
	@/bin/rm -f $(OBJ)
	@echo Removing Libft libraries.
	@make -C ./libft fclean

fclean: clean
	@echo Removing binaries.
	@/bin/rm -f $(NAME)

merge:
	@git checkout master
	@git pull https://github.com/AleXwern/DoomNukem.git master

winup:
	@rm -r ../../../../source/repos/DoomNukem/x64/Debug/gfx
	@rm -r ../../../../source/repos/DoomNukem/x64/Debug/Audio
	@cp -r gfx ../../../../source/repos/DoomNukem/x64/Debug/
	@cp -r Audio ../../../../source/repos/DoomNukem/x64/Debug/

re: fclean all
