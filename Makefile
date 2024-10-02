# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chourri <chourri@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/12 15:51:05 by chourri           #+#    #+#              #
#    Updated: 2024/10/02 12:10:31 by chourri          ###   ########.fr        #
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
 parsing/add_npc1.c \
 parsing/add_npc2.c \
 parsing/add_npc3.c \
 parsing/split_cmd.c \
 parsing/split_cmd_quote.c \
 parsing/split_tokens.c \
 parsing/build_token_list1.c \
 parsing/build_token_list2.c \
 parsing/parse_error_syntax1.c \
 parsing/parse_error_syntax2.c \
 parsing/open_heredoc_errors.c \
 parsing/calculate_expanded_len.c \
 parsing/expand_variable.c \
 parsing/expanding.c \
 parsing/ft_expand.c \
 parsing/build_cmd.c \
 parsing/remove_quotes_before_exec.c \
 execution/ex_cmd.c\
 execution/ex_cmd_utils.c\
 execution/tool_ex.c\
 execution/paths.c\
 execution/split_lib.c\
 execution/redirect.c\
 execution/herdoc_ex.c\
 execution/herdoc_utils.c\
 execution/handle_redirections.c\
 execution/ex_func.c\
 execution/herdoc_3.c\
 execution/herdoc_ex_second.c\
 bultin/bult.c\
 bultin/env.c\
 bultin/echo.c\
 bultin/utils_bult.c\
 bultin/export.c\
 bultin/export_utils.c\
 bultin/exit.c\
 bultin/cd.c\
 bultin/unset_pwd.c \
 bultin/env_to_env.c \
 bultin/exp_handle.c \
 bultin/func_help.c \
 bultin/ex_stat_ch.c \
 signals/Ctrl_c.c \
 libft_tools/tools1.c \
 libft_tools/tools2.c \
 libft_tools/tools3.c \
 libft_tools/tools4.c \
 libft_tools/tools5.c \
 libft_tools/tools6.c \
 libft_tools/tools7.c \
 libft_tools/tools8.c

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

