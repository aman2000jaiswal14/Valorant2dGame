#include "websocketclient.h"


WebSocketClient::WebSocketClient(const QUrl url)
{
    _url = url;
    _client_socket = new QWebSocket;


    clientToServerReconnectTimer = new QTimer;
    clientToServerReconnectTimer->setInterval(msec_reconnect_to_server);
    connect(clientToServerReconnectTimer,&QTimer::timeout,this,&WebSocketClient::clientToServerReconnectTimerSlot);

    connect(_client_socket,&QWebSocket::connected,this,&WebSocketClient::onConnected);
    connect(_client_socket,&QWebSocket::textMessageReceived,this,&WebSocketClient::onTextMessageReceived);
    connect(_client_socket,&QWebSocket::disconnected,this,&WebSocketClient::disconnected);
    connect(_client_socket,&QWebSocket::binaryMessageReceived,this,&WebSocketClient::onBinaryMessageReceived);

}

void WebSocketClient::openClientSocket()
{
    clientToServerReconnectTimerSlot();  // as slot call after timeout time;
    clientToServerReconnectTimer->start();
}

void WebSocketClient::sendByteDataToServer(QByteArray sendbyteArray)
{
    qint64 no_of_data_byte = _client_socket->sendBinaryMessage(sendbyteArray);
    qDebug()<<"CLIENT SIDE : - Data sent.. no of bytes = "<<no_of_data_byte;
}

void WebSocketClient::onConnected()
{
    //    DataStore::getInstance().tempCounter = 0;
    clientState = true;
    clientToServerReconnectTimer->stop();
    qDebug()<<"CLIENT SIDE : -  Web Socket Connected";
    _client_socket->sendTextMessage("Connected To server successfully...");

    sendPlayerConnectedMessage();



}

void WebSocketClient::onTextMessageReceived(const QString message)
{
    qDebug()<<"CLIENT SIDE : - Message Recvd: "<<message;
}

void WebSocketClient::onBinaryMessageReceived(const QByteArray &message)
{
    // emit processMessagesSignal(message);


    STRUCT_SERVER_HEADER serverHeader;
    memcpy(&serverHeader,message.data(),sizeof(STRUCT_SERVER_HEADER));
    if(serverHeader.message_id == S_P_POSITION_MESSAGE_ID)
    {
        S_P_POSITION_MESSAGE msg;
        memcpy(&msg,message.data(),sizeof(S_P_POSITION_MESSAGE));
        emit updatePlayersPositionSignal(msg.players_pos_info);
    }
}

void WebSocketClient::disconnected()
{
    clientState = false;
    //    qDebug()<<DataStore::getInstance().tempCounter;
    qDebug()<<"CLIENT SIDE : - Web Socket Disconnected (Unable to connect with server)";
    clientToServerReconnectTimer->start();
}

void WebSocketClient::onErrorOccur()
{
    qDebug()<<"CLIENT SIDE : - Web Socket error: "<<_client_socket->errorString();
}

void WebSocketClient::clientToServerReconnectTimerSlot()
{
    qDebug()<<"CLIENT SIDE : - Web Socket try to connect with server";
    _client_socket->open(_url);


}


// void WebSocketClient::sendMessageToServer(QByteArray message) {

//     sendBinaryMessage(message);
// }
