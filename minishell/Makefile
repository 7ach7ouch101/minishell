# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmeziani <mmeziani@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/19 15:18:51 by ahel-bah          #+#    #+#              #
#    Updated: 2023/01/10 21:07:04 by mmeziani         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft/libft.a
NAME = minishell
RM = rm -rf
CC = gcc
SRC = minishell.c \
\
	  include/cmd_include.c include/dubstr_include.c include/env_include.c\
	  include/ft_dellst.c include/ft_error.c include/ft_is_opp.c\
	  include/ft_lstinsert.c include/ft_strcmp.c include/ft_substr_lex.c\
	  include/in_between_include.c include/red_include.c\
\
	  lexing/clean_line.c lexing/collect_args.c lexing/concatenate.c\
	  lexing/define_opp.c lexing/double_quoting.c lexing/single_quoting.c\
	  lexing/ft_herdoc.c lexing/lex.c lexing/spaces.c\
\
	  parsing/ft_errors.c parsing/redirections_parser.c parsing/split_pipe.c execution/builtins/ft_exit.c\
	  parsing/wildcard.c execution/execution_base.c execution/check_builtins.c execution/builtins/ft_echo.c\
	  execution/builtins/ft_cd.c fill_env.c execution/builtins/ft_env.c execution/builtins/ft_pwd.c\
	  execution/builtins/ft_unset.c execution/builtins/ft_export.c execution/redirections.c execution/ft_strcmpp.c\
	  execution/exit_st_nd_signls.c execution/builtins/ft_export2.c

OBJ = $(SRC:.c=.o)
	
%.o:%.c
	$(CC) -I $(shell brew --prefix readline)/include -c $< -o $@
	
all: $(LIBFT) $(NAME)

$(NAME): minishell.h $(OBJ)
	$(CC) $(OBJ) -L $(shell brew --prefix readline)/lib -lreadline -o \
	$(NAME) $(LIBFT)

$(LIBFT):
	make bonus -C libft

update:
	$(shell cd ~/goinfre && brew update)

install:
	$(shell cd ~/goinfre && brew install readline)

clean:
	$(RM) $(OBJ)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all
