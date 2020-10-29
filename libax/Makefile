# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/29 11:06:06 by anystrom          #+#    #+#              #
#    Updated: 2020/10/29 11:14:52 by anystrom         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libax.a
FLAG = -Wall -Wextra
SRCS = ax_init.c ax_open.c ax_resolve.c ax_send.c
OBJS = $(SRCS:.c=$(OEXT))
INCLS = ./
OBJFLD = ../obj/
GREEN = \033[0;32m
PURPLE = \033[0;35m
STOP = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

%$(OEXT):%.c
	@gcc $(FLAG) -I $(INCLS) -o $@ -c $<
	@echo "Compiling Libft -> $(GREEN)$@$(STOP)"

$(NAME): $(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "Compiled $(PURPLE)$(NAME)$(STOP)"
	@mv $(OBJS) ../obj
	@mv $(NAME) ../obj

clean:
	@/bin/rm -f $(addprefix $(OBJFLD),$(OBJS))
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(addprefix $(OBJFLD),$(NAME))
	@/bin/rm -f $(NAME)

re: fclean all
