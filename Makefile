# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/07 14:21:44 by pitriche          #+#    #+#              #
#    Updated: 2021/04/21 12:32:37 by user42           ###   ########.fr        #
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
LFLAGS = $(FLAGS)
CFLAGS = -c $(FLAGS)

LIB_NAME = libft.a
LIB_DIR = libft
LIBFLAGS = -lft
LIB = $(LIB_DIR)/$(LIB_NAME)

HEADERS = libft/include/libft.h include/ft_ping.h
CINCLUDE = -I include -I libft/include

NAME = ft_ping

SRC_FILES = \
ft_ping_messages.c	\
ft_ping_parsing.c	\
ft_ping_utils.c		\
ft_ping.c			\
main.c				\

SRC = $(SRC_FILES)

OBJ_FILES = $(patsubst %.c, %.o, $(SRC_FILES))
OBJ_DIR = obj/
OBJ := $(addprefix $(OBJ_DIR), $(OBJ_FILES))

.PHONY: all clean fclean re

all: $(NAME)
	@echo "$(CYAN)$(NAME) ready sir !$(RESET)"

$(NAME): $(LIB) $(OBJ_DIR) $(OBJ)
	@echo "$(GREEN)objects done sir !$(RESET)"
	@$(CC) -L$(LIB_DIR) $(LFLAGS) -o $(NAME) $(OBJ) $(LIBFLAGS)
	@echo "$(GREEN)$(NAME) compiled sir !$(RESET)"

$(OBJ_DIR)%.o : %.c $(HEADERS)
	@$(CC) $(CINCLUDE) $(CFLAGS) -o $@ $<
	@echo -n '.'

$(LIB) :
	@make -C libft

$(OBJ_DIR) :
	@mkdir $(OBJ_DIR)
	@echo "$(GREEN)Object directory created sir !$(RESET)"

clean:
	@rm -f $(OBJ)
	@echo "$(RED)Objects deleted sir !$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)Object directory deleted sir !$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)$(NAME) deleted sir !$(RESET)"

lclean: fclean
	@make -C libft fclean
	@rm -f $(LIB_NAME)
	@echo "$(RED)libft deleted sir !$(RESET)"

re: fclean all

lre: lclean all
