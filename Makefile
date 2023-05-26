# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 16:15:07 by mkaraden          #+#    #+#              #
#    Updated: 2023/05/26 19:15:45 by mkaraden         ###   ########.fr        #
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

SRC = main.c builtins.c ft_strtrim_all.c exec.c			\
	  fill_node.c get_params.c ft_splitcmd.c				\
	  expand.c heredoc.c error.c env.c custom_cmd.c		\
	  get_next_line.c get_next_line_utils.c prompt.c	\
	  ft_cmdsubsplit.c signal.c parse_args.c get_cmd.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJ_LFT = $(addprefix $(OBJ_LFT_DIR)/, $(SRC_LFT:.c=.o))


all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) | $(BIN_DIR)
	$(CC) -L /usr/local/opt/readline/lib -I /usr/local/opt/readline/include -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include $(CFLAGS) $(CDEBUG) $(OBJ) $(LIBFT) -lreadline -o $@


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) -I ~/.brew/opt/readline/include -I /usr/local/opt/readline/include $(CFLAGS) $(CDEBUG) -c $< -o $@


$(LIBFT): $(LIBFT_SRC) | $(LIBFT_DIR) $(BIN_DIR)
	@make all -C libft
	$(AR) $(NAME) $(LIBFT)

run: all
	./$(NAME)

clean: | $(LIBFT_DIR)
	@make clean -C libft
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM)  $(NAME)
	$(RM) $(LIBFT)

re: fclean
	@make all

$(LIBFT_DIR):
	@mkdir -p $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJB_DIR):
	@mkdir -p $(OBJB_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

.PHONY: all clean fclean norminette run re