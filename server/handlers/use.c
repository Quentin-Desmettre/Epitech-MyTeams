/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** use
*/

#include "server.h"

const command_handler_t *get_command_handler(client_t *cli)
{
    uint8_t cmd_id = ((uint8_t *)cli->buffer)[8];
    const command_handler_t *handler;

    if (cmd_id >= NB_COMMANDS)
        return clear_client_buffer(cli),
                send_error(cli, UNKNOWN_COMMAND, ""), NULL;
    handler = &COMMANDS[cmd_id];
    if (handler->nb_args != ((uint16_t *)(cli->buffer + 9))[0])
        return clear_client_buffer(cli),
                send_error(cli, UNKNOWN_COMMAND, ""), NULL;
    if (handler->requires_login && !cli->logged_in)
        return clear_client_buffer(cli),
                send_error(cli, UNAUTHORIZED, ""), NULL;
    return handler;
}

bool check_args(char **args, const command_handler_t *handler, client_t *cli)
{
    uint8_t cmd_id = ((uint8_t *)cli->buffer)[8];

    clear_client_buffer(cli);
    if (!args && handler->nb_args != 0)
        return send_error(cli, UNKNOWN_COMMAND, ""), false;
    for (int i = 0; i < 3 && args && args[i]; i++)
        if (MAX_ARG_SIZES_FOR_REQUEST[cmd_id][i] >= 0 &&
            (long int)strlen(args[i]) > MAX_ARG_SIZES_FOR_REQUEST[cmd_id][i])
            return send_error(cli, UNKNOWN_COMMAND, ""), false;
    return true;
}

int handle_context(server_t *server, client_t *client)
{
    user_context_t *ctx = &client->context;
    team_t *t = ctx->team ? map_get(server->teams, ctx->team) : NULL;
    channel_t *c = t && ctx->channel ? map_get(t->channels, ctx->channel) : 0;
    thread_t *th = c && ctx->thread ? map_get(c->threads, ctx->thread) : NULL;

    if (client->context.team && !t)
        return send_error(client, UNKNOWN_TEAM, client->context.team), 1;
    if (client->context.channel && !c)
        return send_error(client, UNKNOWN_CHANNEL, client->context.channel), 1;
    if (client->context.thread && !th)
        return send_error(client, UNKNOWN_THREAD, client->context.thread), 1;
    return 0;
}

void use_handler(UNUSED server_t *server, client_t *client, char **args)
{
    client->context.team = strlen(args[0]) ? strdup(args[0]) : NULL;
    client->context.channel = strlen(args[1]) ? strdup(args[1]) : NULL;
    client->context.thread = strlen(args[2]) ? strdup(args[2]) : NULL;
}
