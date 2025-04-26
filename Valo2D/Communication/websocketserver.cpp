#include "websocketserver.h"

WebSocketServer::WebSocketServer(quint16 port)
{
    _port = port;
    _server = new QWebSocketServer("PASS_DCCC_SERVER",QWebSocketServer::NonSecureMode);


}

void WebSocketServer::startListening()
{
    if(!_server->listen(QHostAddress::Any,_port))
    {
        qDebug()<<"SERVER  SIDE : - Server Failed to Listen";

    }
    else
    {
        qDebug()<<"SERVER  SIDE : - Server is Listening...";
        connect(_server,&QWebSocketServer::newConnection,this,&WebSocketServer::onNewConnection);
    }

}

void WebSocketServer::sendMessageToAllClient(const QByteArray &message)
{
    foreach(QWebSocket *client_socket,client_list)
    {
        client_socket->sendBinaryMessage(message);
    }

}

void WebSocketServer::sendTextMessageToAllClient(const QString message)
{
    foreach(QWebSocket *client_socket,client_list)
    {
        client_socket->sendTextMessage(message);
    }
}

void WebSocketServer::onNewConnection()
{

    QWebSocket* socket = _server->nextPendingConnection();
    if(socket && client_list.size()<MAX_NO_OF_CLIENT)
    {
        qDebug()<< "SERVER  SIDE : - New Client connected : "<<socket->peerAddress().toString();
        client_list.append(socket);
        ServerHandler *serverHandler = new ServerHandler(socket);
        connect(serverHandler,&ServerHandler::disconnected,this,&WebSocketServer::onClientDisconnect);

        QThread *newThread = new QThread;

        serverHandler->moveToThread(newThread);

         connect(serverHandler,&ServerHandler::finished,this,&WebSocketServer::onClientFinish);

        newThread->start();
    }
    else
    {
        qDebug()<< "SERVER  SIDE : - UNABLE TO CONNECT (MAX NO OF CLIENT CONNECTION EXCEED) : "<<socket->peerAddress().toString() ;
        // TODO check wether client disconnected by server or not.
    }
}

void ServerHandler::onTextMessageReceivedOnServer(const QString message)
{
    qDebug()<<"SERVER  SIDE : - Message Recvd from client to server: "<<message;

}




void WebSocketServer::onClientDisconnect(ServerHandler *serverHandler)
{
    serverHandler->deleteLater();
}

void WebSocketServer::onClientFinish(QThread *thread,QWebSocket *m_webSocket)
{

    client_list.removeOne(m_webSocket);

    thread->quit();
    thread->wait();
    thread->deleteLater();
}


void ServerHandler::printMessageHeader(STRUCT_MESSAGE_HEADER msg_header)
{
    qDebug()<<"SERVER  SIDE : - message header recved...";
    qDebug()<<QDateTime::currentDateTime().toString()<<" | source : "<<msg_header.source_id<<" | dest: "<<msg_header.destination_id<<" | msg id : "<<msg_header.message_id<<" | Corp : "<<msg_header.ws_index<<" | div : "<<msg_header.sucomt_index<<" | pktsqNo : "<<msg_header.packet_seq_no<<" | totalpkt : "<<msg_header.no_of_packets;

    qDebug()<<"SERVER  SIDE : - message header completed.../";
}

void WebSocketServer::printExampleData(const QByteArray &data)
{
    STRUCT_TEST_DATA test_data;
    memcpy(&test_data,data,sizeof(test_data));

    qDebug()<<"SERVER  SIDE : - Test data recved...";
    qDebug()<<test_data.data_id;
    qDebug()<<test_data.data_code;

    qDebug()<<"SERVER  SIDE : - Test data completed.../";
}


void ServerHandler::onBinaryMessageReceivedOnServer(const QByteArray &message)
{
    STRUCT_MESSAGE msgrecv;
    STRUCT_MESSAGE_HEADER msg_header;
    memcpy(&msg_header,message,sizeof(msg_header));
//    printMessageHeader(msg_header);
//    printExampleData(message.mid(sizeof(msg_header)));

    // forwarding msg to all by modifying field

    char buffer[3000];
    int offset=0;

    memcpy(buffer+offset,&msg_header,sizeof(msg_header));
    offset+=sizeof(msg_header);

    memcpy(buffer+offset,message.mid(sizeof(msg_header)).data(),message.mid(sizeof(msg_header)).size());
    offset+=message.mid(sizeof(msg_header)).size();

    QByteArray sendbyteArray(buffer,offset);

    DataStore::getInstance().serverMutex.lock();
    DataStore::getInstance().recvByteArrayList.append(sendbyteArray);
    DataStore::getInstance().serverMutex.unlock();


}

void ServerHandler::onDisconnected()
{
    qDebug()<<"SERVER  SIDE : - client disconnected: "<<m_webSocket->peerAddress().toString();
    m_webSocket->close();
    m_webSocket->deleteLater();
    emit finished(this->thread(),m_webSocket);
    emit disconnected(this);
}


