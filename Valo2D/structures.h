#ifndef STRUCTURES_H
#define STRUCTURES_H

#include<QtGlobal>
#include "GlobalConstant.h"


#pragma pack(push,1)

typedef struct __attribute__ ((packed))
{
    quint8 src = DISPLAY;
    quint8 dest = SERVER;
    quint16 messageId=0;
    quint16 messageLen=0;
    quint8 userId = 0;

}STRUCT_MESSAGE_HEADER;

typedef struct __attribute__ ((packed))
{
    STRUCT_MESSAGE_HEADER msgHeader;
    char name[100];
    char username[100];
    char password[100];
}STRUCT_PLAYER_SINGUP;

typedef struct __attribute__ ((packed))
{
    STRUCT_MESSAGE_HEADER msgHeader;
    char username[100];
    char password[100];
}STRUCT_PLAYER_LOGIN;

typedef struct __attribute__ ((packed))
{
    STRUCT_MESSAGE_HEADER msgHeader;
    int req_val=0;
}STRUCT_REQ;

typedef struct __attribute__ ((packed))
{
    STRUCT_MESSAGE_HEADER msgHeader;
    char name[100];
    char username[100];
    int rankXp;
}STRUCT_PLAYER_INFO;

typedef struct __attribute__ ((packed))
{
    STRUCT_MESSAGE_HEADER msgHeader;
    quint32 status = 0;
    quint32 value = 0;
}STRUCT_ACK;

typedef struct __attribute__ ((packed))
{
    int player_id=0;
    char name[100];
    char username[100];
    int rankXp;
    int agent_id=0;
    int gun_id=0;
    int team = 0;
}STRUCT_PLAYER_AGENT_SERVER;

typedef struct __attribute__ ((packed))
{
    STRUCT_MESSAGE_HEADER msgHeader;
    STRUCT_PLAYER_AGENT_SERVER pas;
}STRUCT_PLAYER_CONNECTED;

typedef struct __attribute__ ((packed))
{
    STRUCT_MESSAGE_HEADER msgHeader;
    int agentid=0;
}STRUCT_AGENT_SELECTED;

typedef struct __attribute__ ((packed))
{
    STRUCT_MESSAGE_HEADER msgHeader;
    int gunId=0;
}STRUCT_GUN_SELECTED;

typedef struct __attribute__ ((packed))
{
    double xpos=0;
    double ypos=0;
}STRUCT_PLAYER_POSITION;

typedef struct __attribute__ ((packed))
{
    STRUCT_MESSAGE_HEADER msgHeader;
    STRUCT_PLAYER_POSITION playerPosition;
}STRUCT_POSITION_MSG;

typedef struct __attribute__ ((packed))
{
    STRUCT_MESSAGE_HEADER msgHeader;
    double rotation;
}STRUCT_HEAD_ROTATION_MSG;

typedef struct __attribute__ ((packed))
{
    int uniqueNo;
    int bulletId;
    double startPosX;
    double startPosY;
    double posX;
    double posY;
    double angle;
    int playerId;
    int gunId;
    bool destroyed = false;
}STRUCT_BULLET_INFO;

typedef struct __attribute__ ((packed))
{
    STRUCT_MESSAGE_HEADER msgHeader;
    STRUCT_BULLET_INFO bullet_info;
}STRUCT_BULLET_INFO_MSG;

typedef struct __attribute__ ((packed))
{
    STRUCT_MESSAGE_HEADER msgHeader;
    int siteNo = 0;
    int team = 0;
}STRUCT_DOMINATION_TEAM_COUNTER_MSG;

typedef struct __attribute__ ((packed))
{
    STRUCT_MESSAGE_HEADER msgHeader;
    int health = 0;
    int shield = 0;
}STRUCT_SET_HEALTH_OF_PLAYER_MSG;

typedef struct __attribute__ ((packed))
{
    STRUCT_MESSAGE_HEADER msgHeader;
    int scoreAA = 0;
    int scoreAB = 0;
    int scoreBA = 0;
    int scoreBB = 0;
}STRUCT_DOMINATION_SCORE_MSG;

typedef struct __attribute__ ((packed))
{
    STRUCT_MESSAGE_HEADER   msg_header;
    char                    my_buf[MAX_MSG_SIZE];
}STRUCT_MQBUF;



#pragma pack(pop)











#endif // STRUCTURES_H
