##
## EPITECH PROJECT, 2023
## helloworld
## File description:
## Makefile
##

rwildc = $(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildc,$d/,$2))

SRCDIR_SERVER = server
SRCDIR_CLIENT = client
SRC_COM = common

SRC_SERVER = $(call rwildc,$(SRCDIR_SERVER),*.c) $(call rwildc,$(SRC_COM),*.c)
SRC_CLIENT = $(call rwildc,$(SRCDIR_CLIENT),*.c) $(call rwildc,$(SRC_COM),*.c)

CLIENT_NAME = myteams_cli
SERVER_NAME = myteams_server

CC = gcc

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

CFLAGS = -Wall -Wextra -I ./include -I ./libs/myteams -L ./libs/myteams -lmyteams -luuid

all:   $(OBJ_SERVER) $(OBJ_CLIENT)
	$(CC) -o $(CLIENT_NAME) $(OBJ_CLIENT) $(CFLAGS)
	$(CC) -o $(SERVER_NAME) $(OBJ_SERVER) $(CFLAGS)

client: $(OBJ_CLIENT)
	$(CC) -o $(CLIENT_NAME) $(OBJ_CLIENT) $(CFLAGS)

server: $(OBJ_SERVER)
	$(CC) -o $(SERVER_NAME) $(OBJ_SERVER) $(CFLAGS)

tests_run:
	cd tests && make && ./tests

clean-client:
	rm -f $(OBJ_CLIENT)
clean-server:
	rm -f $(OBJ_SERVER)
clean:   clean-client clean-server

fclean-client: clean-client
	rm -f $(CLIENT_NAME)

fclean-server: clean-server
	rm -f $(SERVER_NAME)
fclean:    fclean-client fclean-server


re:        fclean all
re-client: fclean client
re-server: fclean server
