#ifndef STRUCTURES_H
#define STRUCTURES_H

struct STRUCT_PLAYER_HEADER {
    int player_id;
    int message_id;
    int v1;
    int v2;
    int v3;
};

struct STRUCT_PLAYER_POSITION_INFO{
    double x;
    double y;
};

// Define MESSAGES
struct P_S_CONNECTION_MESSAGE {
    STRUCT_PLAYER_HEADER player_header;
};
struct P_S_POSITION_MESSAGE {
    STRUCT_PLAYER_HEADER player_header;
    STRUCT_PLAYER_POSITION_INFO pos_info;
};


#endif // STRUCTURES_H
