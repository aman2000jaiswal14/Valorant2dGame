#include "communicationchannel.h"
#include <websocketclient.h>

CommunicationChannel &CommunicationChannel::getInstance()
{
    static CommunicationChannel instance;
    return instance;
}

void CommunicationChannel::sendDataToServer(QByteArray data)
{
    webSocketClient->sendByteDataToServer(data);
}

CommunicationChannel::CommunicationChannel() {


    webSocketClient = new WebSocketClient(QUrl(QString("ws://%1:7000").arg(DataStore::getInstance().getServerIp()))); //192.168.1.10
    connect(webSocketClient,&WebSocketClient::serverDisconnectedSignal,this,&CommunicationChannel::serverDisconnectedSlot);
    webSocketClient->openClientSocket();

}

void CommunicationChannel::serverDisconnectedSlot()
{
    emit serverDisconnectedSignal();
}
