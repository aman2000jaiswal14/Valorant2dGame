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

void WebSocketServer::sendPositionToAllClients(const S_P_POSITION_MESSAGE &message) {


    // Send the message to all clients
    char buffer[sizeof(message)];
    memcpy(buffer,&message,sizeof(message));
    QByteArray data(buffer,sizeof(message));
    for (QWebSocket *client : client_list) {
        client->sendBinaryMessage(data);
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



void ServerHandler::onBinaryMessageReceivedOnServer(const QByteArray &message)
{


    // forwarding msg to all by modifying field

    // char buffer[message.size()];
    // int offset=0;

    // memcpy(buffer+offset,message.data(),message.size());
    // offset+=message.size();

    // QByteArray sendbyteArray(buffer,offset);

    DataStore::instance().serverMutex.lock();
    DataStore::instance().recvByteArrayList.append(message);
    DataStore::instance().serverMutex.unlock();


}

void ServerHandler::onDisconnected()
{
    qDebug()<<"SERVER  SIDE : - client disconnected: "<<m_webSocket->peerAddress().toString();
    m_webSocket->close();
    m_webSocket->deleteLater();
    emit finished(this->thread(),m_webSocket);
    emit disconnected(this);
}

