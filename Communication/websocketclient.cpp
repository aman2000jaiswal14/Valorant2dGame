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

    // For Testing
#if 0
    STRUCT_MESSAGE_HEADER msg_header;
    msg_header.source_id=12;
    msg_header.destination_id=21;
    msg_header.message_id = 1;
    msg_header.message_len=8;
    msg_header.checksum=255;

    STRUCT_TEST_DATA test_data;
    test_data.data_id=2011;
    test_data.data_code=1234;

    char buffer[1000];
    int offset=0;

    memcpy(buffer+offset,&msg_header,sizeof(msg_header));
    offset+=sizeof(msg_header);

    memcpy(buffer+offset,&test_data,sizeof(test_data));
    offset+=sizeof(test_data);

    QByteArray sendbyteArray(buffer,offset);
    sendByteDataToServer(sendbyteArray);
#endif


}

void WebSocketClient::onTextMessageReceived(const QString message)
{
    qDebug()<<"CLIENT SIDE : - Message Recvd: "<<message;
}

void WebSocketClient::onBinaryMessageReceived(const QByteArray &message)
{
    STRUCT_MESSAGE msgrecv;
    STRUCT_MESSAGE_HEADER msg_header;
    memcpy(&msg_header,message,sizeof(msg_header));
    printMessageHeader(msg_header);
//    printExampleData(message.mid(sizeof(msg_header)));
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
void WebSocketClient::printMessageHeader(STRUCT_MESSAGE_HEADER msg_header)
{
    qDebug()<<"CLIENT SIDE : - message header recved...";
    qDebug()<<QDateTime::currentDateTime().toString()<<" | source : "<<msg_header.source_id<<" | dest: "<<msg_header.destination_id<<" | msg id : "<<msg_header.message_id<<" | Corp : "<<msg_header.ws_index<<" | div : "<<msg_header.sucomt_index<<" | pktsqNo : "<<msg_header.packet_seq_no<<" | totalpkt : "<<msg_header.no_of_packets;

    qDebug()<<"CLIENT SIDE : - message header completed.../";

}

void WebSocketClient::printExampleData(const QByteArray &data)
{
    STRUCT_TEST_DATA test_data;
    memcpy(&test_data,data,sizeof(test_data));

    qDebug()<<"CLIENT SIDE : - Test data recved...";
    qDebug()<<test_data.data_id;
    qDebug()<<test_data.data_code;

    qDebug()<<"CLIENT SIDE : - Test data completed.../";
}

