# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acaes <acaes@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/13 18:33:33 by acaes             #+#    #+#              #
#    Updated: 2025/04/13 18:33:33 by acaes            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
MAKEFLAGS = --no-print-directory

INC = ./inc
SRC = ./src
OBJ = ./obj

LIBFT = $(wildcard $(SRC)/libft/base/*.c) \
        $(wildcard $(SRC)/libft/isas/*.c) \
        $(wildcard $(SRC)/libft/list/*.c) \
        $(wildcard $(SRC)/libft/memo/*.c) \
        $(wildcard $(SRC)/libft/str/*.c)

PRINTF = $(wildcard $(SRC)/printf/*.c)
GNL = $(wildcard $(SRC)/gnl/*.c)

SOURCE = $(LIBFT) $(PRINTF) $(GNL)
OBJET = $(SOURCE:$(SRC)/%.c=$(OBJ)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I $(INC)
RM = @rm -rf
AR = ar -rcs

all: $(NAME)

$(NAME): $(OBJET)
	@$(AR) $(NAME) $(OBJET)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
