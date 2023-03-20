/*

================================================================================
Structure Team:
    - Nom
    - description
    - uuid
    - Liste d'uuid d'utilisateurs subscribed
    - Liste de Channel
================================================================================



================================================================================
Structure Channel:
    - nom
    - description
    - uuid
    - Liste de Threads
================================================================================



================================================================================
Structure Thread;
    - titre
    - message de base
    - uuid
    - timestamp de création
    - Liste de réponses
================================================================================



================================================================================
Structure Reponse:
    - uuid de l'utilisateur qui l'a envoyé
    - timestamp d'envoi
    - contenu
================================================================================



================================================================================
Structure Message:
    - uuid de l'utilisateur qui l'a envoyé
    - uuid de l'utilisateur destiné
    - timestamp d'envoi
    - contenu
================================================================================



================================================================================
Structure Server:
    - Liste de teams
    - tableau de fd connecté
    - map de int(fd) -> utilisateurs
    - socket fd
On utilise une map pour faire une recherche plus rapide des utilisateurs
================================================================================



================================================================================
Structure Utilisateur:
    - socket fd
    - uuid (NULL si non connecté)
    - name (NULL si non connecté)
    - context (structure): {Team_uuid, channel_uuid, thread_uuid}
    - input_buffer
    - input_buffer_size
================================================================================



================================================================================
Requete:
    - uint64: taille totale du paquet
    - uint8: type de commande (enum, HELP => 0, LOGIN => 1, ...)
    pour chaque arguments (determinés selon le type de commande):
        uint16: argSize
        char*: argument

Exemple, command /use:
+-------------------------------------------------------------------------------------------+
| Taille | ID | ArgSize1 |  Argument1  | ArgSize2 |  Argument2  | ArgSize3 |    Argument3   |
+-------------------------------------------------------------------------------------------+
|   37   | 6  |     8    |  "78631001" |    10    | "5123498001"|    12    | "120978765276" |
+-------------------------------------------------------------------------------------------+

Taille totale = 1 + 3*2 + 8 + 10 + 12 = 37
Psk:
    1 octet pour l'ID
    3 arguments (-> 3*2 octets)
    Les 3 arguments font 8, 10 et 12 octets
================================================================================



================================================================================
Réponse:
    - uint64: taille totale du paquet
    - enum: Code erreur
    - uint16: taille des infos d'erreur (0 si pas d'erreur)
    - char *: message d'erreur (team_uuid si Unknown team, ...)
    - le reste, à voir

enum ErrorCode {
    Success,
    UnknownTeam,
    UnknownChannel,
    UnknownThread,
    UnknownUser,
    Unauthorized,
    AlreadyExist
};
================================================================================

*/

enum ErrorCode {
    Success,
    UnknownTeam,
    UnknownChannel,
    UnknownThread,
    UnknownUser,
    Unauthorized,
    AlreadyExist
};
