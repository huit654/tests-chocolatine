##
## Makefile — mysh (Minishell2)
##

NAME	=	mysh

CC	=	clang

CFLAGS	=	-Wall -Wextra -Werror -I./include -I.

SRC	=	main.c		\
		lexer.c		\
		lexer_utils.c	\
		parser.c		\
		parser_cmd.c	\
		parser_argv.c	\
		parser_free.c	\
		exec.c		\
		exec_child.c	\
		exec_pipe.c		\
		builtin.c		\
		builtin_cd.c	\
		builtin_env.c	\
		env.c		\
		env_utils.c		\
		redir.c		\
		redir_heredoc.c	\
		path.c		\
		my_str.c		\
		my_mem.c		\
		my_path.c

OBJ	=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re: fclean all
