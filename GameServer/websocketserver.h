#ifndef WEBSOCKETSERVER_H
#define WEBSOCKETSERVER_H

#include <QByteArray>
#include <QDataStream>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QDebug>
#include <QList>
#include <QObject>
#include "structures.h"
#include "datastore.h"
#include "MessageId.h"
#include <QThread>
#include <QMutex>

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

};

class WebSocketServer: public QObject
{
    Q_OBJECT
public:
    WebSocketServer(quint16 port);
    void startListening();
    void sendMessageToAllClient(const QByteArray &message);
    void sendTextMessageToAllClient(const QString message);
    void sendPositionToAllClients(const S_P_POSITION_MESSAGE &message);
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

};

/*
class WebSocketServer : public QWebSocketServer {
    Q_OBJECT

public:
    WebSocketServer(const QString &serverName, QObject *parent = nullptr)
        : QWebSocketServer(serverName, QWebSocketServer::NonSecureMode, parent),
        maxClients(6) {
    }

    bool startServer(const QHostAddress &address, quint16 port) {
        if (this->listen(address, port)) {
            qDebug() << "Server started on" << address.toString() << ":" << port;
            // Connect the newConnection signal to our slot
            connect(this, &QWebSocketServer::newConnection, this, &WebSocketServer::onNewConnection);
            return true;
        } else {
            qWarning() << "Failed to start server!";
            return false;
        }
    }

private slots:
    void onNewConnection() {
        if (clients.count() >= maxClients) {
            qWarning() << "Maximum client limit reached, rejecting new connection!";
            return;
        }

        QWebSocket *socket = this->nextPendingConnection();

        if (!socket) {
            qWarning() << "Failed to establish connection!";
            return;
        }

        // Connect necessary signals to slots
        connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketServer::onTextMessageReceived);
        connect(socket, &QWebSocket::binaryMessageReceived, this, &WebSocketServer::onBinaryMessageReceived);
        connect(socket, &QWebSocket::disconnected, this, &WebSocketServer::onClientDisconnected);

        // Add the new client to the list
        clients.append(socket);
        qDebug() << "New client connected, total clients:" << clients.count();
    }

    void onTextMessageReceived(const QString &message) {
        qDebug() << "Message received:" << message;
        // Echo message back to all clients
        for (QWebSocket *client : clients) {
            client->sendTextMessage(message);
        }
    }

    void onBinaryMessageReceived(const QByteArray &message) {
        qDebug()<<"msg recv ";
        emit processMessagesSignal(message);
    }

    void onClientDisconnected() {
        QWebSocket *socket = qobject_cast<QWebSocket *>(sender());
        if (socket) {
            clients.removeAll(socket);
            socket->deleteLater();
            qDebug() << "Client disconnected, total clients:" << clients.count();
        }
    }

public:




private:
    QList<QWebSocket *> clients; // Stores connected clients
    const int maxClients; // Maximum number of clients allowed
};
*/
#endif // WEBSOCKETSERVER_H
