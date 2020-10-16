# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbergkul <tbergkul@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/07 12:41:01 by anystrom          #+#    #+#              #
#    Updated: 2020/10/15 16:28:58 by tbergkul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME	=	doom-nukem
SERVER	=	server-nukem
OEXT	=	.o
LEXT	= 	.a
# Remember -Wall -Wextra -Werror -> -O2 inclusion is debatable since it was a thing back in 90s
FLG		= 	-O2 -Wall -Wextra
SRCFILE =	doom.c gfx.c loop.c camera.c main_menu.c interact.c door.c \
			util.c menu.c menu2.c gfx_draw.c posteff.c defaults.c \
			set_variables.c misc_alloc.c
KEYFILE =	key_editor.c key_editor_more.c key_game_hold.c key_game_more.c \
			key_game_release.c key_in_game_menu.c key_main_menu.c key_state.c
DRAWEXT =	draw_hud.c draw_hud2.c
FILESYS =	fileformat.c fileformat2.c save_level.c
EDTFILE =	editor.c render_editor.c render_editor2.c
ANMFILE =	staireff.c
COLFILE	=	draw.c draw_utils.c window.c draw_more.c
RNDFILE =	plane_z.c plane_y.c plane_x.c render.c render2.c render3.c \
			slope_yz.c part_dda.c
GRAFILE	=	gravity.c move.c move2.c collision.c
BMPFILE =	bmp_reader.c
TXTFILE =	set_string.c
MTHFILE =	vert.c
SPRFILE =	sprites.c begin_sprites.c shooting.c sprite.c \
			foe_ai.c foe_passive.c foe_status.c plr_status.c \
			draw_projectiles.c draw_objects.c
CLIFILE =	client.c
SRVFILE	=	server.c server_more.c
SRC		=	$(addprefix ./src/,$(SRCFILE)) \
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
			$(addprefix ./src/sprite/,$(SPRFILE)) \
			$(addprefix ./src/network/,$(CLIFILE))
SRCSRV	=	$(addprefix ./src/server/,$(SRVFILE))
OBJSRV	=	$(addprefix ./obj/server/,$(SRVFILE:.c=$(OEXT)))
LIBFT	=	$(addprefix ./obj/libft,$(LEXT))
OBJS	=	$(SRC:.c=$(OEXT))
OBJ		=	$(addprefix ./obj/,$(SRCFILE:.c=$(OEXT))) \
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
			$(addprefix ./obj/sprite/,$(SPRFILE:.c=$(OEXT))) \
			$(addprefix ./obj/network/,$(CLIFILE:.c=$(OEXT)))
DEPNS	=	$(OBJ:.o=.d) $(OBJSRV:.o=.d)
OBJDIR	=	./obj/
SRCDIR	=	./src/
INCL	=	-I ./SDL2 -I ./libft -I ./includes
PWD		=	$(shell pwd)
OBJFRAME =	-F ./frameworks
FRAMEWORK =	-F $(PWD)/frameworks -framework SDL2 -framework SDL2_mixer -framework SDL2_net -Wl,-rpath $(PWD)/frameworks
RED		=	\033[0;31m
BLUE	=	\033[0;34m
STOP	=	\033[0m

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
	@gcc $(FRAMEWORK) $(FLG) $(INCL) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "read 'icns' (-16455) \"gfx/icon.icns\";" >> icon.rsrc
	@Rez -a icon.rsrc -o $(NAME)
	@SetFile -a C $(NAME)
	@rm icon.rsrc
	@echo "Executable created successfully."
	@echo "Run the executable as $(BLUE)./$(NAME)$(STOP). No args."

clean:
	@echo "Removing Doom-Nukem libraries and dependancies."
	@/bin/rm -f $(OBJ)
	@/bin/rm -f $(OBJSRV)
	@/bin/rm -f $(DEPNS)
	@echo Removing Libft libraries.
	@make -C ./libft fclean

fclean: clean
	@echo Removing binaries.
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(SERVER)

run: all
	./doom-nukem

$(SERVER): $(OBJSRV) $(LIBFT)
	@gcc $(FRAMEWORK) $(FLG) $(INCL) -o $(SERVER) $(OBJSRV) $(LIBFT)
	@echo "read 'icns' (-16455) \"gfx/icon.icns\";" >> icon.rsrc
	@Rez -a icon.rsrc -o $(SERVER)
	@SetFile -a C $(SERVER)
	@rm icon.rsrc
	@echo "Executable created successfully."
	@echo "Run the executable as $(BLUE)./$(SERVER)$(STOP). No args."

both: $(NAME) $(SERVER)

reboth: fclean both

re: fclean all
