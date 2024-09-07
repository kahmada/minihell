# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chourri <chourri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 15:51:05 by chourri           #+#    #+#              #
#    Updated: 2024/09/07 11:40:07 by chourri          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME   = minishell
HEADER = minishell.h
CC     = cc
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g\
#  -I $(shell brew --prefix readline)/include

CFLAGS = -Wall -Wextra -Werror \
 -I $(shell brew --prefix readline)/include

LDFLAGS = -lreadline \
-L $(shell brew --prefix readline)/lib
RM     = rm -f

SRC = main.c \
 parsing/add_npc.c \
 parsing/split_cmd.c \
 parsing/split_cmd_quote.c \
 parsing/split_tokens.c \
 parsing/build_token_list.c \
 parsing/parsing.c \
 parsing/expanding.c \
 execution/ex_cmd.c\
 execution/paths.c\
 execution/split_lib.c\
 execution/redirect.c\
 execution/herdoc_ex.c\
 execution/herdoc_utils.c\
 execution/handle_redirections.c\
 bultin/bult.c\
 bultin/env.c\
 bultin/echo.c\
 bultin/utils_bult.c\
 bultin/export.c\
 bultin/export_utils.c\
 bultin/exit.c\
 bultin/cd.c\
 bultin/unset_pwd.c \
 signals/Ctrl_c.c \
 libft_tools/tools1.c \
 libft_tools/tools2.c \
 libft_tools/tools3.c \
 libft_tools/tools4.c \
 libft_tools/tools5.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

