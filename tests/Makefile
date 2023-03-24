##
## EPITECH PROJECT, 2023
## myteams
## File description:
## Makefile
##

rwildc = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildc,$d/,$2))

SOURCEDIR = ./
SOURCEDIR_SERVER = ../server
SOURCEDIR_CLIENT = ../client

SRC_TMP = $(call rwildc,$(SOURCEDIR_SERVER),*.c) $(call rwildc,$(SOURCEDIR_CLIENT),*.c) $(call rwildc,../common/,*.c)
SRC = $(filter-out $(call rwildc,..,main.c), $(SRC_TMP)) $(call rwildc,$(SOURCEDIR),*.c)

CC = gcc

OBJ = $(SRC:.c=.o)

NAME = tests

CFLAGS = -I ../include -I ../libs/myteams -luuid --coverage -lcriterion

all: clean
	$(CC) -o $(NAME) $(SRC) $(CFLAGS)

$(NAME):
	$(CC) -o $(NAME) $(SRC) $(CFLAGS)

clean:
	rm -f $(OBJ)
	find . -name "vgcore.*" -delete
	find . -name "*~" -delete
	find . -name "\#*" -delete
	find .. -name "*.gc*" -delete

fclean:    clean
	rm -f $(NAME)

re:        fclean all
