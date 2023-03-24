//
// Created by qdes on 20/03/23.
//

#include <criterion/criterion.h>
#include <dlfcn.h>
#include <stdio.h>
#include "map.h"
#include "libmyteams.h"

int (*server_event_team_created)() = NULL;
int (*server_event_channel_created)() = NULL;
int (*server_event_thread_created)() = NULL;
int (*server_event_reply_created)() = NULL;
int (*server_event_user_subscribed)() = NULL;
int (*server_event_user_unsubscribed)() = NULL;
int (*server_event_user_created)() = NULL;
int (*server_event_user_loaded)() = NULL;
int (*server_event_user_logged_in)() = NULL;
int (*server_event_user_logged_out)() = NULL;
int (*server_event_private_message_sended)() = NULL;

void *handle = NULL;

void setup()
{
    handle = dlopen("./libmyteams.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "%s\n", dlerror());
        exit(84);
    }
    server_event_team_created = dlsym(handle, "server_event_team_created");
    server_event_channel_created = dlsym(handle, "server_event_channel_created");
    server_event_thread_created = dlsym(handle, "server_event_thread_created");
    server_event_reply_created = dlsym(handle, "server_event_reply_created");
    server_event_user_subscribed = dlsym(handle, "server_event_user_subscribed");
    server_event_user_unsubscribed = dlsym(handle, "server_event_user_unsubscribed");
    server_event_user_created = dlsym(handle, "server_event_user_created");
    server_event_user_loaded = dlsym(handle, "server_event_user_loaded");
    server_event_user_logged_in = dlsym(handle, "server_event_user_logged_in");
    server_event_user_logged_out = dlsym(handle, "server_event_user_logged_out");
    server_event_private_message_sended = dlsym(handle, "server_event_private_message_sended");
}

void teardown()
{
    dlclose(handle);
}

Test(myteams, test, .init = setup, .fini = teardown)
{
    map_t *m = map_create((compare_key_t)strcmp, free);

    cr_assert(m->size == 0);
    cr_assert(m->capacity == 10);

    map_add(m, "key", strdup("value"));
    cr_assert(m->size == 1);
    cr_assert(m->capacity == 10);

    map_add(m, "key2", strdup("value2"));
    cr_assert(m->size == 2);

    map_add(m, "key3", strdup("value3"));
    cr_assert(m->size == 3);

    map_add(m, "key4", strdup("value4"));
    cr_assert(m->size == 4);

    map_add(m, "key5", strdup("value5"));
    cr_assert(m->size == 5);

    map_add(m, "key6", strdup("value6"));
    cr_assert(m->size == 6);

    map_add(m, "key7", strdup("value7"));
    cr_assert(m->size == 7);

    map_add(m, "key8", strdup("value8"));
    cr_assert(m->size == 8);

    map_add(m, "key9", strdup("value9"));
    cr_assert(m->size == 9);

    map_add(m, "key10", strdup("value10"));
    cr_assert(m->size == 10);

    map_add(m, "key11", strdup("value11"));
    cr_assert(m->size == 11);
    cr_assert(m->capacity == 20);

    cr_assert(strcmp(map_get(m, "key"), "value") == 0);
    cr_assert(strcmp(map_get(m, "key2"), "value2") == 0);
    cr_assert(strcmp(map_get(m, "key3"), "value3") == 0);
    cr_assert(strcmp(map_get(m, "key4"), "value4") == 0);
    cr_assert(strcmp(map_get(m, "key5"), "value5") == 0);
    cr_assert(strcmp(map_get(m, "key6"), "value6") == 0);
    cr_assert(strcmp(map_get(m, "key7"), "value7") == 0);
    cr_assert(strcmp(map_get(m, "key8"), "value8") == 0);
    cr_assert(strcmp(map_get(m, "key9"), "value9") == 0);
    cr_assert(strcmp(map_get(m, "key10"), "value10") == 0);
    cr_assert(strcmp(map_get(m, "key11"), "value11") == 0);

    cr_assert(map_get(m, "key12") == NULL);

    map_remove(m, "key");
    cr_assert(m->size == 10);
    cr_assert(map_get(m, "key") == NULL);

    map_remove(m, "key7");
    cr_assert(m->size == 9);
    cr_assert(map_get(m, "key7") == NULL);


    cr_assert(strcmp(map_get(m, "key2"), "value2") == 0);
    cr_assert(strcmp(map_get(m, "key3"), "value3") == 0);
    cr_assert(strcmp(map_get(m, "key4"), "value4") == 0);
    cr_assert(strcmp(map_get(m, "key5"), "value5") == 0);
    cr_assert(strcmp(map_get(m, "key6"), "value6") == 0);
    cr_assert(strcmp(map_get(m, "key8"), "value8") == 0);
    cr_assert(strcmp(map_get(m, "key9"), "value9") == 0);
    cr_assert(strcmp(map_get(m, "key10"), "value10") == 0);
    cr_assert(strcmp(map_get(m, "key11"), "value11") == 0);

    map_add(m, "key2", strdup("valueee"));
    cr_assert(m->size == 9);
    cr_assert(strcmp(map_get(m, "key2"), "valueee") == 0);

    map_remove(m, "key2");
    map_remove(m, "key3");
    map_remove(m, "key4");
    map_remove(m, "key5");
    map_remove(m, "key6");
    map_remove(m, "key8");
    map_remove(m, "key9");
    map_remove(m, "key10");
    map_remove(m, "key11");

    cr_assert(m->size == 0);
    cr_assert(m->capacity == 20);


    map_add(m, "key", strdup("value"));
    cr_assert(m->size == 1);
    cr_assert(m->capacity == 20);
    cr_assert(strcmp(map_get(m, "key"), "value") == 0);

    map_destroy(m);
    map_destroy(NULL);
}

//TEST_CASE("test")
//{
//    map_t *m = map_create(strcmp, free);
//
//    REQUIRE(m->size == 0);
//    REQUIRE(m->capacity == 10);
//
//    map_add(m, "key", strdup("value"));
//    REQUIRE(m->size == 1);
//    REQUIRE(m->capacity == 10);
//
//    map_add(m, "key2", strdup("value2"));
//    REQUIRE(m->size == 2);
//
//    map_add(m, "key3", strdup("value3"));
//    REQUIRE(m->size == 3);
//
//    map_add(m, "key4", strdup("value4"));
//    REQUIRE(m->size == 4);
//
//    map_add(m, "key5", strdup("value5"));
//    REQUIRE(m->size == 5);
//
//    map_add(m, "key6", strdup("value6"));
//    REQUIRE(m->size == 6);
//
//    map_add(m, "key7", strdup("value7"));
//    REQUIRE(m->size == 7);
//
//    map_add(m, "key8", strdup("value8"));
//    REQUIRE(m->size == 8);
//
//    map_add(m, "key9", strdup("value9"));
//    REQUIRE(m->size == 9);
//
//    map_add(m, "key10", strdup("value10"));
//    REQUIRE(m->size == 10);
//
//    map_add(m, "key11", strdup("value11"));
//    REQUIRE(m->size == 11);
//    REQUIRE(m->capacity == 20);
//
//    REQUIRE(strcmp(map_get(m, "key"), "value") == 0);
//    REQUIRE(strcmp(map_get(m, "key2"), "value2") == 0);
//    REQUIRE(strcmp(map_get(m, "key3"), "value3") == 0);
//    REQUIRE(strcmp(map_get(m, "key4"), "value4") == 0);
//    REQUIRE(strcmp(map_get(m, "key5"), "value5") == 0);
//    REQUIRE(strcmp(map_get(m, "key6"), "value6") == 0);
//    REQUIRE(strcmp(map_get(m, "key7"), "value7") == 0);
//    REQUIRE(strcmp(map_get(m, "key8"), "value8") == 0);
//    REQUIRE(strcmp(map_get(m, "key9"), "value9") == 0);
//    REQUIRE(strcmp(map_get(m, "key10"), "value10") == 0);
//    REQUIRE(strcmp(map_get(m, "key11"), "value11") == 0);
//
//    REQUIRE(map_get(m, "key12") == nullptr);
//
//    map_remove(m, "key");
//    REQUIRE(m->size == 10);
//    REQUIRE(map_get(m, "key") == nullptr);
//
//    map_remove(m, "key7");
//    REQUIRE(m->size == 9);
//    REQUIRE(map_get(m, "key7") == nullptr);
//
//
//    REQUIRE(strcmp(map_get(m, "key2"), "value2") == 0);
//    REQUIRE(strcmp(map_get(m, "key3"), "value3") == 0);
//    REQUIRE(strcmp(map_get(m, "key4"), "value4") == 0);
//    REQUIRE(strcmp(map_get(m, "key5"), "value5") == 0);
//    REQUIRE(strcmp(map_get(m, "key6"), "value6") == 0);
//    REQUIRE(strcmp(map_get(m, "key8"), "value8") == 0);
//    REQUIRE(strcmp(map_get(m, "key9"), "value9") == 0);
//    REQUIRE(strcmp(map_get(m, "key10"), "value10") == 0);
//    REQUIRE(strcmp(map_get(m, "key11"), "value11") == 0);
//
//    map_add(m, "key2", strdup("valueee"));
//    REQUIRE(m->size == 9);
//    REQUIRE(strcmp(map_get(m, "key2"), "valueee") == 0);
//
//    map_remove(m, "key2");
//    map_remove(m, "key3");
//    map_remove(m, "key4");
//    map_remove(m, "key5");
//    map_remove(m, "key6");
//    map_remove(m, "key8");
//    map_remove(m, "key9");
//    map_remove(m, "key10");
//    map_remove(m, "key11");
//
//    REQUIRE(m->size == 0);
//    REQUIRE(m->capacity == 20);
//
//
//    map_add(m, "key", strdup("value"));
//    REQUIRE(m->size == 1);
//    REQUIRE(m->capacity == 20);
//    REQUIRE(strcmp(map_get(m, "key"), "value") == 0);
//
//    map_destroy(m);
//}
//
//TEST_CASE("linkedlist")
//{
//
//}
