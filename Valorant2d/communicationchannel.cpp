#include "communicationchannel.h"
#include "websocketclient.h"


void CommunicationChannel::updatePlayerPosition(STRUCT_PLAYER_POSITION_INFO pos_info)
{
    P_S_POSITION_MESSAGE msg;
    msg.player_header.player_id = 1;  // Example player ID
    msg.player_header.message_id = P_S_POSITION_MESSAGE_ID;
    msg.player_header.v1 = 1;
    msg.player_header.v2 = 0;
    msg.player_header.v3 = 0;

    msg.pos_info = pos_info;
    char buffer[sizeof(msg)];
    memcpy(&buffer,&msg,sizeof(msg));
    QByteArray data(buffer);
    webSocketClient->sendMessageToServer(data);
}

CommunicationChannel::CommunicationChannel() {
    webSocketClient = new WebSocketClient();

    // Connect to the WebSocket server (replace with the actual address)
    webSocketClient->connectToServer("ws://127.0.0.1:7000");
}
