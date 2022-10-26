# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brunomartin <brunomartin@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/07 14:27:46 by pitriche          #+#    #+#              #
#    Updated: 2021/04/21 12:49:58 by brunomartin      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREY    = \033[030m
RED     = \033[031m
GREEN   = \033[032m
YELLOW  = \033[033m
BLUE    = \033[034m
MAGENTA = \033[035m
CYAN	= \033[036m
RESET   = \033[0m

# **************************************************************************** #

CC = gcc

FL_OPTI = -O3 -flto
FLAGS = -Wall -Wextra -Wconversion -Wuninitialized $(FL_OPTI)
CFLAGS = -c $(FLAGS)
CINCLUDE = -I include

NAME = libft.a

SRC = \
ft_bzero.c			\
ft_memmove.c		\
ft_putstr_fd.c		\
ft_putstr.c			\
ft_putnbr_base_fd.c	\
ft_putnbr.c			\
ft_putchar_fd.c		\
ft_strdup.c			\

OBJ_DIR = obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

.PHONY: all clean fclean re

all: $(OBJ_DIR) $(NAME)
	@echo "$(CYAN)$(NAME) ready sir !$(RESET)"

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(addprefix $(OBJ_DIR), %.o) : %.c
	@$(CC) $(CINCLUDE) $(CFLAGS) -o $@ $<
	@echo -n '.'

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LINK_NAME)

re: fclean all

.PHONY: all, clean, fclean, re
