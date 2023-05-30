# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 14:07:50 by kscordel          #+#    #+#              #
#    Updated: 2023/05/30 16:16:19 by kscordel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRC_DIR = src/
OBJ_DIR = obj/

SRC = $(SRC_DIR)minishell.c

OBJ = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRC))

NAME = minishell

LIBPATH = libft/libft.a

all:	$(NAME)

$(NAME):	$(OBJ) | lib
	$(CC) $(CFLAGS) $(OBJ) $(LIBPATH) -lreadline -o $@

lib:
	@make -C ./libft

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)


clean:
	rm -rf $(OBJ_DIR)
	make clean -C ./libft

fclean: clean
		rm -f $(NAME)
		make fclean -C ./libft

re: fclean all

leak:
	valgrind --leak-check=full --show-leak-kinds=all --track-fds=yes ./minishell

.PHONY: all lib clean fclean re
