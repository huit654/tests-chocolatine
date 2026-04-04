##
## EPITECH PROJECT, 2026
## MY_TOP
## File description:
## Makefile
##

NAME = robot-factory

TESTNAME = unit_tests

CC = clang

SRC	=	srcs/print_usage.c	\
		srcs/robot_factory.c	\
		srcs/header_prog_name.c	\
		srcs/my_strcpy.c	\
		srcs/my_strcmp.c	\
		srcs/my_strlen.c	\
		srcs/my_strtok.c	\

OBJ = $(SRC:.c=.o)

TMP_FILES = *~\
	*.pch\
	*.log \
	a.out \
	*.gcov\
	*.gcno\
	*.gcda

all : $(NAME)

$(NAME): $(OBJ)
	$(CC)  $(SRC) -o $(NAME) -lc -g3

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(NAME) $(TMP_FILES) $(TESTNAME)
	rm -f srcs/$(TMP_FILES)
	rm -f tests/$(TMP_FILES)
	rm -f tests/test/$(TMP_FILES)

re: fclean all
