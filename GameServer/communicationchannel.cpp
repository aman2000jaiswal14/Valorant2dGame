#include "communicationchannel.h"
#include "websocketserver.h"
#include <QHostAddress>
#include "datastore.h"
CommunicationChannel::CommunicationChannel()
{
    webSocketServer =  new WebSocketServer(7000);
    webSocketServer->startListening();

    processMessagesTimer = new QTimer;
    processMessagesTimer->setInterval(1000);
    connect(processMessagesTimer,QTimer::timeout,this,CommunicationChannel::processMessageTimeOutSlot);
    processMessagesTimer->start();

    positionTimer = new QTimer;
    positionTimer->setInterval(100);
    connect(positionTimer,QTimer::timeout,this,CommunicationChannel::positionTimeOutSlot);
    positionTimer->start();
}

void CommunicationChannel::processMessagesSlot(QByteArray message)
{
    STRUCT_PLAYER_HEADER playerHeader;

    memcpy(&playerHeader,message.data(),sizeof(STRUCT_PLAYER_HEADER));

    if(playerHeader.message_id == P_S_CONNECTION_MESSAGE_ID)
    {

        qDebug()<<"Player connected : "<<playerHeader.player_id;
        qDebug()<<"version : "<<QString("%1.%2.%3").arg(playerHeader.v1).arg(playerHeader.v2).arg(playerHeader.v3);
    }
    else if(playerHeader.message_id == P_S_POSITION_MESSAGE_ID )
    {
        STRUCT_PLAYER_POSITION_INFO pos_info;
        memcpy(&pos_info,message.data()+sizeof(STRUCT_PLAYER_HEADER),sizeof(STRUCT_PLAYER_POSITION_INFO));
\
        DataStore::instance().allPlayerPosition.players[playerHeader.player_id-1].player_id = playerHeader.player_id;
        DataStore::instance().allPlayerPosition.players[playerHeader.player_id-1].pos_info = pos_info;
    }
}

void CommunicationChannel::positionTimeOutSlot()
{
    S_P_POSITION_MESSAGE msg;
    msg.server_header.server_id = 1;
    msg.server_header.message_id = S_P_POSITION_MESSAGE_ID;
    msg.players_pos_info = DataStore::instance().allPlayerPosition;
    webSocketServer->sendPositionToAllClients(msg);
}

void CommunicationChannel::processMessageTimeOutSlot()
{

    DataStore::instance().serverMutex.lock();
    recvByteArrayListCopy = DataStore::instance().recvByteArrayList;
    DataStore::instance().recvByteArrayList.clear();
    DataStore::instance().serverMutex.unlock();

    for(QByteArray message : recvByteArrayListCopy){
        processMessagesSlot(message);
    }

}
CommunicationChannel::~CommunicationChannel()
{

    delete webSocketServer;
}
