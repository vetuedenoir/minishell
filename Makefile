# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kscordel <kscordel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/30 14:07:50 by kscordel          #+#    #+#              #
#    Updated: 2023/10/26 15:19:27 by kscordel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f

SRC_DIR = src/
OBJ_DIR = obj/

SRC = $(SRC_DIR)minishell.c $(SRC_DIR)lexer.c  $(SRC_DIR)utils.c $(SRC_DIR)utils2.c \
		$(SRC_DIR)parser.c $(SRC_DIR)path.c $(SRC_DIR)garbage_collector.c \
		$(SRC_DIR)decoup.c $(SRC_DIR)utils_m.c $(SRC_DIR)expand.c \
		$(SRC_DIR)handle_quote.c $(SRC_DIR)handle_redirection.c \
		$(SRC_DIR)builtin1.c $(SRC_DIR)builtin2.c $(SRC_DIR)herdoc_expand.c \
		$(SRC_DIR)initshell.c $(SRC_DIR)signal.c $(SRC_DIR)expand_lex.c \
		$(SRC_DIR)exec.c $(SRC_DIR)heredoc.c $(SRC_DIR)redirection.c \
		$(SRC_DIR)builtin3.c $(SRC_DIR)handle_quote2.c $(SRC_DIR)builtin4.c \
		$(SRC_DIR)heredoc2.c $(SRC_DIR)exec2.c

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
