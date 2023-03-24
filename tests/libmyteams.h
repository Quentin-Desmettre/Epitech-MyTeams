/*
** EPITECH PROJECT, 2023
** Epitech_MyTeams
** File description:
** libmyteams
*/

#ifndef EPITECH_MYTEAMS_LIBMYTEAMS_H
    #define EPITECH_MYTEAMS_LIBMYTEAMS_H

extern int (*server_event_team_created)();
extern int (*server_event_channel_created)();
extern int (*server_event_thread_created)();
extern int (*server_event_reply_created)();
extern int (*server_event_user_subscribed)();
extern int (*server_event_user_unsubscribed)();
extern int (*server_event_user_created)();
extern int (*server_event_user_loaded)();
extern int (*server_event_user_logged_in)();
extern int (*server_event_user_logged_out)();
extern int (*server_event_private_message_sended)();
extern void *handle;

void setup();
void teardown();

#endif //EPITECH_MYTEAMS_LIBMYTEAMS_H
