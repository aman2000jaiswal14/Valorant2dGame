#ifndef STRUCTURES_H
#define STRUCTURES_H
#include <QtTypes>
#pragma pack(push,1)
struct STRUCT_PLAYER_HEADER {
    quint8 player_id;
    quint8 message_id;
    quint8 v1;
    quint8 v2;
    quint8 v3;
};
struct STRUCT_SERVER_HEADER {
    quint8 server_id;
    quint8 message_id;
};

struct STRUCT_PLAYER_POSITION_INFO{
    qreal x;
    qreal y;
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
#pragma pack(pop)
#endif // STRUCTURES_H
