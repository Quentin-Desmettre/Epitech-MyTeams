##
## EPITECH PROJECT, 2023
## helloworld
## File description:
## Makefile
##

SRCDIR_SERVER = server
SRCDIR_CLIENT = client
SRCDIR_COMMON = common

SRCS_COM = 	compare.c                 \
          	strings.c                 \
          	packet.c                  \
          	read_packet.c             \
          	linked_list/linked_list.c \
          	map/map.c                 \
          	my_write.c                \

SRC_COM = $(addprefix $(SRCDIR_COMMON)/, $(SRCS_COM))

SRCS_SERVER = server_run.c              \
             	server_init.c             \
             	fd_data.c                 \
             	responses/errors.c        \
             	send_to_user.c            \
             	main.c                    \
             	free.c                    \
             	save/restore_server.c     \
             	save/save_server.c        \
             	handlers/login_out.c      \
             	handlers/list.c           \
             	handlers/subscribe.c      \
             	handlers/send.c           \
             	handlers/subscribed.c     \
             	handlers/user.c           \
             	handlers/info.c           \
             	handlers/create.c         \
             	handlers/use.c            \
             	handlers/create_utility.c \
             	handlers/create_notify.c  \
             	handlers/help.c           \
             	handlers/messages.c       \

SRCS_CLIENT = 	client_input.c                    \
             	client_init.c                     \
             	responses/team_channel_interact.c \
             	responses/responses_misc.c        \
             	responses/thread_list.c           \
             	responses/connection_receiver.c   \
             	responses/responses_list.c        \
             	responses/reply.c                 \
             	responses/responses_unknown.c     \
             	responses/responses_info.c        \
             	responses/client_handle_server.c  \
             	main.c                            \
             	client_run.c                      \
             	Command/infos.c                   \
             	Command/connection.c              \
             	Command/jai_pas_trouver_de_nom.c  \
             	Command/interraction.c            \

SRC_SERVER = $(addprefix $(SRCDIR_SERVER)/, $(SRCS_SERVER))
SRC_CLIENT = $(addprefix $(SRCDIR_CLIENT)/, $(SRCS_CLIENT))

SRC_SERVER += $(SRC_COM)
SRC_CLIENT += $(SRC_COM)

CLIENT_NAME = myteams_cli
SERVER_NAME = myteams_server

CC = gcc

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

CFLAGS = -Wall -Wextra -I ./include -I ./libs/myteams \
			-L ./libs/myteams -lmyteams -luuid -g

all:   $(OBJ_SERVER) $(OBJ_CLIENT)
	$(CC) -o $(CLIENT_NAME) $(OBJ_CLIENT) $(CFLAGS)
	$(CC) -o $(SERVER_NAME) $(OBJ_SERVER) $(CFLAGS)

client: $(OBJ_CLIENT)
	$(CC) -o $(CLIENT_NAME) $(OBJ_CLIENT) $(CFLAGS)

server: $(OBJ_SERVER)
	$(CC) -o $(SERVER_NAME) $(OBJ_SERVER) $(CFLAGS)

tests_run:
	rm -f ./tests/libmyteams.so && cp ./libs/myteams/libmyteams.so ./tests/
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
