# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anystrom <anystrom@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/30 16:09:13 by anystrom          #+#    #+#              #
#    Updated: 2020/10/19 15:46:04 by anystrom         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(OS),Windows_NT)
OEXT = .obj
LEXT = .lib
else
OEXT = .o
LEXT = .a
endif
NAME = $(addprefix libft,$(LEXT))
SRCS = ft_memalloc.c ft_putendl.c ft_strcpy.c ft_strmapi.c ft_strsub.c \
	ft_memccpy.c ft_putendl_fd.c ft_strdel.c ft_strncat.c ft_strtrim.c \
	ft_atoi.c ft_memchr.c ft_putnbr.c ft_strdup.c ft_strncmp.c \
	ft_tolower.c ft_bzero.c ft_memcmp.c ft_putnbr_fd.c ft_strequ.c \
	ft_strncpy.c ft_toupper.c ft_isalnum.c ft_memcpy.c ft_putstr.c \
	ft_striter.c ft_strnequ.c ft_isalpha.c ft_memdel.c ft_putstr_fd.c \
	ft_striteri.c ft_strnew.c ft_isascii.c ft_memmove.c ft_strcat.c \
	ft_strjoin.c ft_strnstr.c ft_isdigit.c ft_memset.c ft_strchr.c \
	ft_strlcat.c ft_strrchr.c ft_isprint.c ft_putchar.c ft_strclr.c \
	ft_strlen.c ft_strsplit.c ft_itoa.c ft_putchar_fd.c ft_strcmp.c \
	ft_strmap.c ft_strstr.c ft_wordlen.c ft_isblank.c ft_isnegative.c \
	ft_intsize.c ft_isextascii.c get_next_line.c ft_puthex.c ft_lcm.c \
	ft_abs.c ft_fabs.c ft_putnbrln.c ft_sleep.c ft_quadjoin.c \
	ft_strfjoin.c
OBJS = $(SRCS:.c=$(OEXT))
INCLS = ./
OBJFLD = ../obj/
GREEN = \033[0;32m
PURPLE = \033[0;35m
STOP = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

%$(OEXT):%.c
ifeq ($(OS),Windows_NT)
	@clang -Wall -Wextra -Werror $(FLG) -I $(INCLS) -o $@ -c $<
	@echo "Compiling Libft -> $@"
else
	@gcc -Wall -Wextra -Werror $(FLG) -I $(INCLS) -o $@ -c $<
	@echo "Compiling Libft -> $(GREEN)$@$(STOP)"
endif

$(NAME): $(OBJS)
ifeq ($(OS),Windows_NT)
	lib /OUT:libft.lib $(OBJS)
else
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "Compiled $(PURPLE)$(NAME)$(STOP)"
endif
	@mv $(OBJS) ../obj
	@mv $(NAME) ../obj

clean:
	@/bin/rm -f $(addprefix $(OBJFLD),$(OBJS))
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(addprefix $(OBJFLD),$(NAME))
	@/bin/rm -f $(NAME)

re: fclean all
