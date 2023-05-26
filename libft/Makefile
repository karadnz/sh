# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaraden <mkaraden@student.42istanbul.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 20:26:57 by mkaraden          #+#    #+#              #
#    Updated: 2023/05/26 20:26:58 by mkaraden         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc 
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f
HEADER = libft.h
SRC_DIR = src
SRCB_DIR = srcb
SRCA_DIR = srca
OBJ_DIR = obj
OBJB_DIR = objb
OBJA_DIR = obja
BIN_DIR = bin
BIN = libft.a
NAME = $(BIN_DIR)/$(BIN)

SRC =	ft_atoi.c ft_bzero.c	\
	ft_calloc.c ft_putendl_fd.c		\
	ft_itoa.c ft_putchar_fd.c		\
	ft_putstr_fd.c ft_memccpy.c		\
	ft_memchr.c ft_memcmp.c			\
	ft_memcpy.c ft_isalnum.c		\
	ft_isalpha.c ft_isascii.c		\
	ft_isdigit.c ft_isprint.c		\
	ft_memmove.c ft_memset.c		\
	ft_split.c ft_strchr.c			\
	ft_strdup.c ft_strjoin.c		\
	ft_strlcat.c ft_strlcpy.c		\
	ft_strlen.c ft_strmapi.c		\
	ft_strncmp.c ft_strnstr.c		\
	ft_strrchr.c ft_strtrim.c		\
	ft_substr.c ft_tolower.c		\
	ft_toupper.c ft_putnbr_fd.c

SRCB = ft_lstadd_back.c	\
	ft_lstadd_front.c	\
	ft_lstclear.c		\
	ft_lstdelone.c		\
	ft_lstiter.c		\
	ft_lstlast.c		\
	ft_lstsize.c		\
	ft_lstnew.c			\
	ft_lstmap.c			\
	ft_lstget_at.c

SRCA = ft_putnbr_base_fd.c ft_putstrn_fd.c		\
	ft_putnchar_fd.c ft_isspace.c ft_uitoa.c	\
	ft_nbrlen.c ft_strrncmp.c ft_countchar.c	\
	ft_strenlarge.c ft_recursive_power.c		\
	ft_chartostr.c ft_sqrt.c ft_newvector.c		\
	ft_euclideandistance.c  ft_atoi2.c			\
	ft_free_matrix.c ft_dup_matrix.c			\
	ft_strchr_i.c ft_putmatrix_fd.c				\
	ft_matrixlen.c ft_strchars_i.c				\
	ft_between_chars.c ft_subsplit.c			\
	ft_extend_matrix.c ft_matrixtolst.c			\
	ft_lsttomatrix.c ft_matrix_replace_in.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

OBJB = $(addprefix $(OBJB_DIR)/, $(SRCB:.c=.o))

OBJA = $(addprefix $(OBJA_DIR)/, $(SRCA:.c=.o))


all: $(NAME)

$(NAME): $(OBJ) $(OBJB) $(OBJA) | $(BIN_DIR)
	$(AR) $(NAME) $^

bonus: $(OBJB) | $(BIN_DIR)
	$(AR) $(NAME) $^

additional: $(OBJA) | $(BIN_DIR)
	$(AR) $(NAME) $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJB_DIR)/%.o: $(SRCB_DIR)/%.c | $(OBJB_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJA_DIR)/%.o: $(SRCA_DIR)/%.c | $(OBJA_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJB_DIR):
	@mkdir -p $(OBJB_DIR)

$(OBJA_DIR):
	@mkdir -p $(OBJA_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	$(RM) -r $(OBJ_DIR)
	$(RM) -r $(OBJB_DIR)
	$(RM) -r $(OBJA_DIR)

fclean: clean
	$(RM) -r $(BIN_DIR)


re: fclean
	@make all


.PHONY: all bonus additional clean fclean re 
