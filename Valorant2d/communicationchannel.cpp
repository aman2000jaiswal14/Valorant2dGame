#include "communicationchannel.h"
#include "websocketclient.h"
#include <iostream>
#include <stdio.h>

void CommunicationChannel::updateCurrentPlayerPosition(STRUCT_PLAYER_POSITION_INFO pos_info)
{
    P_S_POSITION_MESSAGE msg;
    msg.player_header.player_id = 1;  // Example player ID
    msg.player_header.message_id = P_S_POSITION_MESSAGE_ID;
    msg.player_header.v1 = 1;
    msg.player_header.v2 = 0;
    msg.player_header.v3 = 0;

    qDebug()<<pos_info.x<<" "<<pos_info.y;
    msg.pos_info = pos_info;
    char buffer[sizeof(msg)];
    memcpy(&buffer,&msg,sizeof(msg));
    QByteArray data(buffer,sizeof(msg));

    webSocketClient->sendByteDataToServer(data);

}

CommunicationChannel::CommunicationChannel() {
    webSocketClient = new WebSocketClient(QUrl("ws://127.0.0.1:7000"));
    webSocketClient->openClientSocket();
    connect(webSocketClient,&WebSocketClient::updatePlayersPositionSignal,this,&CommunicationChannel::updatePlayerPositionSlot);
}

void CommunicationChannel::updatePlayerPositionSlot(STRUCT_ALL_PLAYER_POSITION_INFO players_pos_info)
{
    allPlayerPosition = players_pos_info;
}
