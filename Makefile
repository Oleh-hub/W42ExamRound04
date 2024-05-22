SRC = microshell.c
all : *.c
	cc -Wall -Wextra -Werror $(SRC) -o microshell