# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 16:15:07 by mkaraden          #+#    #+#              #
#    Updated: 2023/05/26 20:40:13 by mkaraden         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



AR = ar rcs
CFLAGS = -Wall -Wextra -Werror 
RM = rm -f
CC = gcc

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

LIBFT = libft/bin/libft.a

BIN = minishell
NAME = $(BIN_DIR)/$(BIN)

SRC = main/main.c execute/builtins.c parse/ft_strtrim_all.c execute/exec.c			\
	  parse/fill_node.c parse/get_params.c parse/ft_splitcmd.c				\
	  parse/expand.c main/heredoc.c utils/error.c main/env.c 		\
	  gnl/get_next_line.c gnl/get_next_line_utils.c main/prompt.c	\
	  parse/ft_cmdsubsplit.c utils/signal.c parse/parse_args.c execute/get_cmd.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))


all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) | $(BIN_DIR)
	$(CC) -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include $(CFLAGS) $(CDEBUG) $(OBJ) $(LIBFT) -lreadline -o $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -I ~/.brew/opt/readline/include -I /usr/local/opt/readline/include $(CFLAGS) $(CDEBUG) -c $< -o $@


$(LIBFT): $(LIBFT_SRC) | $(LIBFT_DIR) $(BIN_DIR)
	@make all -C libft
	$(AR) $(NAME) $(LIBFT)

run: all
	./$(NAME)

clean: | $(LIBFT_DIR)
	@make clean -C libft

fclean: clean
	$(RM)  $(NAME)
	$(RM) $(LIBFT)
	$(RM) $(OBJ)

re: fclean
	@make all

.PHONY: all clean fclean norminette run re