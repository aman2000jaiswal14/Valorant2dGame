#include "middleware.h"

MiddleWare &MiddleWare::getInstance()
{
    static MiddleWare middlewareObj;
    return middlewareObj;
}

MiddleWare::MiddleWare() {}

void MiddleWare::sendPlayerPositionMsg(STRUCT_PLAYER_POSITION pos)
{
    STRUCT_POSITION_MSG msg;
    msg.msgHeader.messageId = D_S_POSITION_UPDATE;
    msg.msgHeader.messageLen = sizeof(msg)-sizeof(msg.msgHeader);
    msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();
    msg.playerPosition = pos;

    QByteArray data;
    data.resize(sizeof(msg));
    memcpy(data.data(),&msg,sizeof(msg));

    // DataStore::getInstance().updatePlayerPosition(msg);
    CommunicationChannel::getInstance().sendDataToServer(data);
}

void MiddleWare::sendHeadRotationMsg(double rotation)
{
    STRUCT_HEAD_ROTATION_MSG msg;
    msg.msgHeader.messageId = D_S_HEAD_ROTATION_UPDATE;
    msg.msgHeader.messageLen = sizeof(msg)-sizeof(msg.msgHeader);
    msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();
    msg.rotation = rotation;

    QByteArray data;
    data.resize(sizeof(msg));
    memcpy(data.data(),&msg,sizeof(msg));
    // DataStore::getInstance().updatePlayerHeadRotation(msg);
    CommunicationChannel::getInstance().sendDataToServer(data);
}

void MiddleWare::sendBulletInfoMsg(STRUCT_BULLET_INFO bullet_info)
{
    STRUCT_BULLET_INFO_MSG msg;
    msg.msgHeader.messageId = D_S_BULLET_INFO;
    msg.msgHeader.messageLen = sizeof(msg)-sizeof(msg.msgHeader);
    msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();
    msg.bullet_info = bullet_info;

    QByteArray data;
    data.resize(sizeof(msg));
    memcpy(data.data(),&msg,sizeof(msg));

    CommunicationChannel::getInstance().sendDataToServer(data);
}

void MiddleWare::sendBulletHitThePlayerMsg(STRUCT_BULLET_INFO bullet_info)
{
    STRUCT_BULLET_INFO_MSG msg;
    msg.msgHeader.messageId = D_S_BULLET_HIT_THE_PLAYER;
    msg.msgHeader.messageLen = sizeof(msg)-sizeof(msg.msgHeader);
    msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();
    msg.bullet_info = bullet_info;

    QByteArray data;
    data.resize(sizeof(msg));
    memcpy(data.data(),&msg,sizeof(msg));

    CommunicationChannel::getInstance().sendDataToServer(data);
}

void MiddleWare::sendGunChangeMsg(int gunId)
{
    STRUCT_GUN_SELECTED msg;
    msg.msgHeader.messageId = D_S_GUN_SELECTED;
    msg.msgHeader.messageLen = sizeof(msg)-sizeof(msg.msgHeader);
    msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();
    msg.gunId = gunId;

    QByteArray data;
    data.resize(sizeof(msg));
    memcpy(data.data(),&msg,sizeof(msg));

    CommunicationChannel::getInstance().sendDataToServer(data);
}

void MiddleWare::sendResetPlayerPositionMsg()
{
    STRUCT_POSITION_MSG msg;
    msg.msgHeader.messageId = D_S_RESET_PLAYER_POSITION;
    msg.msgHeader.messageLen = sizeof(msg)-sizeof(msg.msgHeader);
    msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();

    QByteArray data;
    data.resize(sizeof(msg));
    memcpy(data.data(),&msg,sizeof(msg));
    CommunicationChannel::getInstance().sendDataToServer(data);
}

void MiddleWare::sendSetHealthMsg(STRUCT_SET_HEALTH_OF_PLAYER_MSG healthMsg)
{
    STRUCT_SET_HEALTH_OF_PLAYER_MSG msg;
    msg.msgHeader.messageId = D_S_SET_HEALTH_MSG;
    msg.msgHeader.messageLen = sizeof(msg)-sizeof(msg.msgHeader);
    msg.msgHeader.userId = DataStore::getInstance().getRealPlayer()->getId();
    msg.health = healthMsg.health;
    msg.shield = healthMsg.shield;

    QByteArray data;
    data.resize(sizeof(msg));
    memcpy(data.data(),&msg,sizeof(msg));
    CommunicationChannel::getInstance().sendDataToServer(data);
}

