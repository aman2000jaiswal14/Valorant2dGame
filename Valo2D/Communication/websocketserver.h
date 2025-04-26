#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QObject>
#include <QWebSocket>
#include <QWebSocketServer>
#include <QDebug>
#include <Structures.h>

#include "udpcommunication.h"

class ServerHandler : public QObject{
    Q_OBJECT
public:

    ServerHandler(QWebSocket *socket, QObject *parent=nullptr) : QObject(parent),m_webSocket(socket){

        connect(m_webSocket,&QWebSocket::binaryMessageReceived,this,&ServerHandler::onBinaryMessageReceivedOnServer);
        connect(m_webSocket,&QWebSocket::textMessageReceived,this,&ServerHandler::onTextMessageReceivedOnServer);
        connect(m_webSocket,&QWebSocket::disconnected,this,&ServerHandler::onDisconnected);
    }

public slots:
    void onTextMessageReceivedOnServer(const QString message);
    void onBinaryMessageReceivedOnServer(const QByteArray &message);
    void onDisconnected();

signals:
    void disconnected(ServerHandler *);
    void finished(QThread *,QWebSocket *);
private:
    QWebSocket *m_webSocket;
    void printMessageHeader(STRUCT_MESSAGE_HEADER msg_header);
};

class WebSocketServer: public QObject
{
    Q_OBJECT
public:
    WebSocketServer(quint16 port);
    void startListening();
    void sendMessageToAllClient(const QByteArray &message);
    void sendTextMessageToAllClient(const QString message);

signals:
    void sendServerDataToMediator(QByteArray);

private slots:
    void onNewConnection();



public slots:
    void onClientDisconnect(ServerHandler *serverHandler);
    void onClientFinish(QThread *thread,QWebSocket *m_webSocket);

private:
    quint16 _port;
    quint8 MAX_NO_OF_CLIENT=100;
    QWebSocketServer *_server;
    QList<QWebSocket *> client_list;


    void printExampleData(const QByteArray &data);

};

#endif // WEBSOCKETSERVER_H
