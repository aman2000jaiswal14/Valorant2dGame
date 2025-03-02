#ifndef STRUCTURES_H
#define STRUCTURES_H

struct STRUCT_PLAYER_HEADER {
    int player_id;
    int message_id;
    int v1;
    int v2;
    int v3;
};

struct STRUCT_SERVER_HEADER {
    int server_id;
    int message_id;
};

struct STRUCT_PLAYER_POSITION_INFO{
    double x;
    double y;
};

struct STRUCT_ONE_PLAYER_POSITION_INFO{
    int player_id=0;
    STRUCT_PLAYER_POSITION_INFO pos_info;
};

struct STRUCT_ALL_PLAYER_POSITION_INFO{
    STRUCT_ONE_PLAYER_POSITION_INFO players[6];
};

// Define MESSAGES
struct P_S_CONNECTION_MESSAGE {
    STRUCT_PLAYER_HEADER player_header;
};
struct P_S_POSITION_MESSAGE {
    STRUCT_PLAYER_HEADER player_header;
    STRUCT_PLAYER_POSITION_INFO pos_info;
};

struct S_P_POSITION_MESSAGE {
    STRUCT_SERVER_HEADER server_header;
    STRUCT_ALL_PLAYER_POSITION_INFO players_pos_info;
};


#endif // STRUCTURES_H
